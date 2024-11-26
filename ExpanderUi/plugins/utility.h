#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>
#include <QStandardPaths>

class Utility : public QObject {
    Q_OBJECT
   public:
    explicit Utility(QObject* parent = nullptr);

    Q_INVOKABLE QString appDataPath() const {
        return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    }

   signals:
};

#endif  // UTILITY_H
