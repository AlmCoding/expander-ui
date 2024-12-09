#include "updatemanager.h"
// #include <QCoreApplication>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include "version.h"

UpdateManager::UpdateManager(QObject* parent) : QObject{ parent } {
    network_manager_ = new QNetworkAccessManager(this);
    fetchReleases();
}

void UpdateManager::fetchReleases() {
    QString url{ "https://api.github.com/repos/AlmCoding/expander-ui/releases" };
    QNetworkRequest request{ QUrl(url) };
    request.setRawHeader("Accept", "application/vnd.github.v3+json");

    QNetworkReply* reply = network_manager_->get(request);
    connect(reply, &QNetworkReply::finished, this, &UpdateManager::releasesFetched);
}

void UpdateManager::releasesFetched() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (reply == nullptr) {
        qDebug() << "Fetch reply is null!";
        return;
    }
    qDebug() << "Software releases fetched";

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray releases = doc.array();
        for (const QJsonValue& value : releases) {
            QJsonObject release = value.toObject();
            QString tag_name = release["tag_name"].toString();

            // Format "Vx.x.x"
            if (tag_name.startsWith("V") == false) {
                continue;
            }

            tag_name.remove(0, 1);
            QStringList parts = tag_name.split(".");

            if (parts.size() != 3) {
                continue;
            }

            int major = parts[0].toInt();
            int minor = parts[1].toInt();
            int patch = parts[2].toInt();

            if (major > PROJECT_VERSION_MAJOR ||                                      //
                (major == PROJECT_VERSION_MAJOR && minor > PROJECT_VERSION_MINOR) ||  //
                (major == PROJECT_VERSION_MAJOR && minor == PROJECT_VERSION_MINOR && patch > PROJECT_VERSION_PATCH)) {
                updateAvailable_ = true;
                emit updateAvailableChanged();
                break;
            }
        }
    } else {
        qDebug() << "Error fetching releases: " << reply->errorString();
    }

    reply->deleteLater();
}
