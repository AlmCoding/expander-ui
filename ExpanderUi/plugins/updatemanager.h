#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QNetworkAccessManager>
#include <QObject>

class UpdateManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool updateAvailable READ getUpdateAvailable NOTIFY updateAvailableChanged)

   public:
    explicit UpdateManager(QObject* parent = nullptr);

    bool getUpdateAvailable() const { return updateAvailable_; }

   signals:
    void updateAvailableChanged();

   private slots:
    void releasesFetched();

   private:
    void fetchReleases();

    QNetworkAccessManager* network_manager_ = nullptr;
    bool updateAvailable_ = false;
};

#endif  // UPDATEMANAGER_H
