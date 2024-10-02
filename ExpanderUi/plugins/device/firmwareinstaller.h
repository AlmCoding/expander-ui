#ifndef FIRMWAREINSTALLER_H
#define FIRMWAREINSTALLER_H

#include <QObject>
#include <QTimer>
#include "plugins/containers/com/installertypes.h"

constexpr int SearchForDfuIntervalMs = 1000;
constexpr int SearchForDfuTimeoutMs = 5000;

class FirmwareInstaller : public QObject {
    Q_OBJECT
   public:
    explicit FirmwareInstaller(QObject* parent = nullptr);
    ~FirmwareInstaller() = default;

    void installFirmware(QString file);

   signals:
    void stateChanged(InstallerTypes::State state);

   private:
    void process();
    void connectDevice();
    void downloadFirmware();

    QString file_;
    QTimer timer_;
    int remaining_attempts_ = 0;
    InstallerTypes::State state_ = InstallerTypes::State::Idle;
};

#endif  // FIRMWAREINSTALLER_H
