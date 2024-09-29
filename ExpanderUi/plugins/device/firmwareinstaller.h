#ifndef FIRMWAREINSTALLER_H
#define FIRMWAREINSTALLER_H

#include <QObject>
#include <QTimer>

constexpr int SearchForDfuIntervalMs = 500;
constexpr int SearchForDfuTimeoutMs = 5000;

class FirmwareInstaller : public QObject {
    Q_OBJECT
   public:
    explicit FirmwareInstaller(QObject* parent = nullptr);
    ~FirmwareInstaller() = default;

    void installFirmware(QString file);

   signals:

   private:
    enum class State {
        Idle = 0,
        Connect,
        Download,
        Error,
    };

    void process();
    void connect_device();
    void download_firmware();

    QTimer timer_;
    int remaining_attempts_ = 0;
    State state_ = State::Idle;
    QString file_;
};

#endif  // FIRMWAREINSTALLER_H
