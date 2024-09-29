#include "firmwareinstaller.h"
#include <QDebug>
#include "CubeProgrammer_API.h"

FirmwareInstaller::FirmwareInstaller(QObject* parent) : QObject{ parent } {
    connect(&timer_, &QTimer::timeout, this, &FirmwareInstaller::process);
}

void FirmwareInstaller::installFirmware(QString file) {
    qDebug() << "Install firmware: " << file;

    file_ = file;
    state_ = State::Connect;
    remaining_attempts_ = SearchForDfuTimeoutMs / SearchForDfuIntervalMs;

    timer_.start(SearchForDfuIntervalMs);
}

void FirmwareInstaller::process() {
    timer_.stop();
    remaining_attempts_--;
    if (remaining_attempts_ <= 0) {
        state_ = State::Error;
    }

    switch (state_) {
        case State::Idle:
            break;
        case State::Connect:
            connect_device();
            break;
        case State::Download:
            download_firmware();
            break;
        case State::Error:
            qDebug() << "Firmware installation failed!";
            break;
        default:
            break;
    }
}

void FirmwareInstaller::connect_device() {
    qDebug() << "Searching for DFU device...";

    dfuDeviceInfo* dfu_list = nullptr;
    int count = getDfuDeviceList(&dfu_list, 0xdf11, 0x0483);

    if (count == 0) {
        qDebug() << "No DFU device found!";
        timer_.start(SearchForDfuIntervalMs);
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
    int connect_result = connectDfuBootloader(dfu_list[0].usbIndex);
    connect_result = 0;  // CubeProgrammer bug workaround (connectDfuBootloader always returns -5)

    if (connect_result != 0) {
        qDebug() << "Failed to connect to DFU device!";
        state_ = State::Error;
        disconnect();

    } else {
        qDebug() << "Connected to DFU device!";
        state_ = State::Download;
        timer_.start(0);
    }

    deleteInterfaceList();
}

void FirmwareInstaller::download_firmware() {
    qDebug() << "Downloading firmware...";

    unsigned int verify = 1;      // verify download
    unsigned int skip_erase = 0;  // do not skip erase

    int download_result =
        downloadFile(reinterpret_cast<const wchar_t*>(file_.utf16()), 0x08000000, skip_erase, verify, L"");
    disconnect();

    if (download_result != 0) {
        qDebug() << "Failed to download firmware!";
        state_ = State::Error;

    } else {
        qDebug() << "Firmware successfully downloaded!";
        state_ = State::Idle;
    }
}
