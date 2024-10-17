#include "firmwaredownloader.h"

FirmwareDownloader::FirmwareDownloader(QObject* parent) : QObject{ parent } {
    network_manager_ = new QNetworkAccessManager(this);
}

void FirmwareDownloader::setFirmwareDirectory(const QString &directory) {
    if (firmware_directory_ == directory) {
        return;
    }

    firmware_directory_ = directory;
    QDir dir(firmware_directory_);
    if (dir.exists() == false) {
        dir.mkpath(".");
    }

    emit firmwareDirectoryChanged();
    fetchReleases();
}

void FirmwareDownloader::releasesFetched() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply == nullptr) {
        qDebug() << "Fetch reply is null!";
        return;
    }

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray releases = doc.array();
        for (const QJsonValue& value : releases) {
            QJsonObject release = value.toObject();
            QString tag_name = release["tag_name"].toString();
            QJsonArray assets = release["assets"].toArray();

            qDebug() << "Release:" << tag_name;

            for (const QJsonValue& assetValue : assets) {
                QJsonObject asset = assetValue.toObject();
                QString file_name = asset["name"].toString();
                QString download_url = asset["url"].toString();

                if (file_name.endsWith(".hex") == false) {
                    continue;
                }
                QString file_path = firmware_directory_ + "/" + tag_name + ".hex";

                // Check if the asset is already downloaded
                if (QFile::exists(file_path) == false) {
                    downloadAsset(download_url, file_path);
                } else {
                    qDebug() << "Already downloaded:" << file_path;
                }
            }
        }
    } else {
        qDebug() << "Error fetching releases:" << reply->errorString();
    }
    reply->deleteLater();
}

void FirmwareDownloader::assetDownloaded() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply == nullptr) {
        qDebug() << "Download reply is null!";
        return;
    }

    if (reply->error() == QNetworkReply::NoError) {
        QString localFilePath = reply->property("localFilePath").toString();
        QFile file(localFilePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
            qDebug() << "Downloaded:" << localFilePath;
            emit firmwareDownloaded();
        } else {
            qDebug() << "Failed to save file:" << localFilePath;
        }
    } else {
        qDebug() << "Error downloading asset:" << reply->errorString();
    }
    reply->deleteLater();
}

void FirmwareDownloader::fetchReleases() {
    QString url = "https://api.github.com/repos/AlmCoding/expander-mcu/releases";
    QNetworkRequest request{ QUrl(url) };
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply* reply = network_manager_->get(request);
    connect(reply, &QNetworkReply::finished, this, &FirmwareDownloader::releasesFetched);
}

void FirmwareDownloader::downloadAsset(const QString &url, const QString &localFilePath) {
    QNetworkRequest request{ QUrl(url) };
    request.setRawHeader("Accept", "application/octet-stream");

    QNetworkReply* reply = network_manager_->get(request);
    reply->setProperty("localFilePath", localFilePath);
    connect(reply, &QNetworkReply::finished, this, &FirmwareDownloader::assetDownloaded);
}
