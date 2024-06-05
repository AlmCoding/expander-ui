#ifndef DEVICECOM_H
#define DEVICECOM_H

#include <QObject>
#include <QThread>

class DeviceCom : public QThread {
    Q_OBJECT

   public:
    explicit DeviceCom(QObject* parent = nullptr);

   signals:

   private:
    void run() override;
};

#endif  // DEVICECOM_H
