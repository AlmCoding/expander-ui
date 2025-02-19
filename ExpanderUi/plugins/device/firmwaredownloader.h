#ifndef FIRMWAREDOWNLOADER_H
#define FIRMWAREDOWNLOADER_H

#include <QNetworkAccessManager>
#include <QObject>

class FirmwareDownloader : public QObject {
    Q_OBJECT

    Q_PROPERTY(
        QString firmwareDirectory READ getFirmwareDirectory WRITE setFirmwareDirectory NOTIFY firmwareDirectoryChanged)

   public:
    FirmwareDownloader(QObject* parent = nullptr);

    QString getFirmwareDirectory() const { return firmware_directory_; }
    void setFirmwareDirectory(const QString& directory);

   signals:
    void firmwareDirectoryChanged();
    void firmwareDownloaded();

   private slots:
    void releasesFetched();
    void assetDownloaded();

   private:
    void fetchReleases();
    void downloadAsset(const QString& url, const QString& localFilePath);

    QNetworkAccessManager* network_manager_ = nullptr;
    QString firmware_directory_;
};

#endif  // FIRMWAREDOWNLOADER_H
