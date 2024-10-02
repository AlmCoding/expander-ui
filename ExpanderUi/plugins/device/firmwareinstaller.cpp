#include "firmwareinstaller.h"
#include <QDebug>
#include "magic_enum.hpp"

namespace CubeProgrammer {
#include "CubeProgrammer_API.h"
}

FirmwareInstaller::FirmwareInstaller(QObject* parent) : QObject{ parent } {
    connect(&timer_, &QTimer::timeout, this, &FirmwareInstaller::process);
}

void FirmwareInstaller::installFirmware(QString file) {
    qDebug() << "Install firmware: " << file;

    file_ = file;
    state_ = InstallerTypes::State::Connect;
    remaining_attempts_ = SearchForDfuTimeoutMs / SearchForDfuIntervalMs;
    timer_.start(SearchForDfuIntervalMs);
}

void FirmwareInstaller::process() {
    timer_.stop();

    switch (state_) {
        case InstallerTypes::State::Idle:
            break;
        case InstallerTypes::State::Connect:
            connectDevice();
            break;
        case InstallerTypes::State::Download:
            downloadFirmware();
            break;
        case InstallerTypes::State::Success:
            state_ = InstallerTypes::State::Idle;
            break;
        case InstallerTypes::State::Error:
            state_ = InstallerTypes::State::Idle;
            break;
        default:
            break;
    }

    static InstallerTypes::State last_state = InstallerTypes::State::Idle;
    if (state_ != last_state) {
        qDebug() << "Publish installer state: " << magic_enum::enum_name(state_);
        last_state = state_;
        emit stateChanged(state_);
    }

    if (state_ != InstallerTypes::State::Idle) {
        timer_.start(SearchForDfuIntervalMs);
    }
}

void FirmwareInstaller::connectDevice() {
    qDebug() << "Searching for DFU device...";
    remaining_attempts_--;
    if (remaining_attempts_ <= 0) {
        state_ = InstallerTypes::State::Error;
        return;
    }

    CubeProgrammer::dfuDeviceInfo* dfu_list = nullptr;
    int count = CubeProgrammer::getDfuDeviceList(&dfu_list, 0xdf11, 0x0483);

    if (count == 0) {
        qDebug() << "No DFU device found!";
        return;
    }

    qDebug("------------- USB DFU Device List -------------");
    for (int i = 0; i < count; i++) {
        qDebug() << "USB Port : " << i;
        qDebug() << "  USB idx: " << dfu_list[i].usbIndex;
        qDebug() << "  USB SN : " << dfu_list[i].serialNumber;
    }
    qDebug("-----------------------------------------------");

    // Connect to the first device in the list
    int connect_result = CubeProgrammer::connectDfuBootloader(dfu_list[0].usbIndex);
    connect_result = 0;  // CubeProgrammer bug workaround (connectDfuBootloader always returns -5)

    if (connect_result != 0) {
        qDebug() << "Failed to connect to DFU device!";
        state_ = InstallerTypes::State::Error;
        disconnect();

    } else {
        qDebug() << "Connected to DFU device!";
        state_ = InstallerTypes::State::Download;
    }
    CubeProgrammer::deleteInterfaceList();
}

void FirmwareInstaller::downloadFirmware() {
    qDebug() << "Downloading firmware...";

    unsigned int verify = 1;      // verify download
    unsigned int skip_erase = 0;  // do not skip erase

    int download_result = CubeProgrammer::downloadFile(reinterpret_cast<const wchar_t*>(file_.utf16()), 0x08000000,
                                                       skip_erase, verify, L"");
    CubeProgrammer::disconnect();

    if (download_result != 0) {
        qDebug() << "Failed to download firmware!";
        state_ = InstallerTypes::State::Error;

    } else {
        qDebug() << "Firmware successfully downloaded!";
        state_ = InstallerTypes::State::Success;
    }
}
