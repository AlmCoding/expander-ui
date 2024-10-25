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
    CubeProgrammer::cubeProgrammerError result =
        static_cast<CubeProgrammer::cubeProgrammerError>(CubeProgrammer::connectDfuBootloader(dfu_list[0].usbIndex));
    result = CubeProgrammer::CUBEPROGRAMMER_NO_ERROR;  // CubeProgrammer bug workaround (connectDfuBootloader always
                                                       // returns -5)

    if (result == CubeProgrammer::CUBEPROGRAMMER_NO_ERROR) {
        qDebug() << "Connected to DFU device!";
        state_ = InstallerTypes::State::Download;

    } else {
        qDebug() << "Failed to connect to DFU device!";
        state_ = InstallerTypes::State::Error;
        disconnect();
    }

    CubeProgrammer::deleteInterfaceList();
}

void FirmwareInstaller::downloadFirmware() {
    qDebug() << "Downloading firmware...";

    CubeProgrammer::cubeProgrammerError result =
        static_cast<CubeProgrammer::cubeProgrammerError>(CubeProgrammer::massErase());

    if (result != CubeProgrammer::CUBEPROGRAMMER_NO_ERROR) {
        qDebug() << "Mass erase error: " << result;
        state_ = InstallerTypes::State::Error;
        CubeProgrammer::disconnect();
        return;
    }

    unsigned int verify = 1;      // verify download
    unsigned int skip_erase = 1;  // skip erase
    result = static_cast<CubeProgrammer::cubeProgrammerError>(
        CubeProgrammer::downloadFile(file_.toStdWString().c_str(), FirmwareStartAddress, skip_erase, verify, L""));

    if (result != CubeProgrammer::CUBEPROGRAMMER_NO_ERROR) {
        qDebug() << "Download firmware error: " << result;
        state_ = InstallerTypes::State::Error;
        CubeProgrammer::disconnect();
        return;
    }
    qDebug() << "Firmware successfully downloaded!";

    // result = static_cast<CubeProgrammer::cubeProgrammerError>(CubeProgrammer::execute(FirmwareStartAddress));

    // if (result != CubeProgrammer::CUBEPROGRAMMER_NO_ERROR) {
    //     qDebug() << "Execute firmware error: " << result;
    //     state_ = InstallerTypes::State::Error;
    //     CubeProgrammer::disconnect();
    //     return;
    // }
    // qDebug() << "Firmware successfully started!";

    state_ = InstallerTypes::State::Success;
    CubeProgrammer::disconnect();
}
