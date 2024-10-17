#ifndef FIRMWAREDOWNLOADER_H
#define FIRMWAREDOWNLOADER_H

#include <QObject>

class FirmwareDownloader : public QObject {
    Q_OBJECT
   public:
    explicit FirmwareDownloader(QObject* parent = nullptr);

   signals:
};

#endif  // FIRMWAREDOWNLOADER_H
