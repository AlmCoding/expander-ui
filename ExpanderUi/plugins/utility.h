#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>
#include <QStandardPaths>
#include <QString>

class Utility : public QObject {
    Q_OBJECT
   public:
    explicit Utility(QObject* parent = nullptr);

    Q_INVOKABLE QString appDataPath() const {
        return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    }

    static QString convertHexToAscii(const QString& hex_string);
    static QString convertAsciiToHex(const QString& ascii_string);
    static int convertSlaveAddrToInt(const QString& slave_addr);
    static QString countHexBytes(const QString& hex_string);
    static int countHexBytesInt(const QString& hex_string);
};

#endif  // UTILITY_H
