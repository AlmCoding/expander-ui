#include "utility.h"
#include <QDebug>

Utility::Utility(QObject* parent) : QObject{ parent } {}

QString Utility::convertHexToAscii(const QString& hex_string) {
    QStringList hex_list = hex_string.split(' ', Qt::SkipEmptyParts);
    QString result;

    for (const QString& hex : hex_list) {
        bool ok;
        // Convert each hex string to an integer
        int value = hex.toInt(&ok, 16);

        if (ok) {
            if (value == 0x0a) {  // Newline (LF)
                result += "\\n";
            } else if (value == 0x0d) {  // Carriage return (CR)
                result += "\\r";
            } else if (value >= 32 && value <= 126) {  // Printable ASCII range
                result += QChar(value);
            } else {
                // Non-printable characters are represented as \xx
                result += '\\';
                result += QString::asprintf("%02X", value);  // Convert to two-digit hex
            }
        } else {
            qWarning() << "Invalid hex value:" << hex;
        }
    }

    return result;
}

QString Utility::convertAsciiToHex(const QString& ascii_string) {
    QStringList hex_list;
    int i = 0;
    int n = ascii_string.length();

    while (i < n) {
        if (ascii_string[i] == '\\') {
            // Handle escape sequences
            if (i + 1 >= n) {
                // Wait for the next character
                break;
            }

            QChar next_char = ascii_string[i + 1];
            QChar next_char2 = '\0';
            if (i + 2 < n) {
                next_char2 = ascii_string[i + 2];
            }

            if (next_char == 'n') {
                // \n sequence
                hex_list << "0a";
                i += 2;
            } else if (next_char == 'r') {
                // \r sequence
                hex_list << "0d";
                i += 2;
            } else if (next_char == '\\') {
                // \\ sequence
                hex_list << "5c";
                i += 2;
            } else if (i + 2 < n &&
                       ((next_char.isDigit() || (next_char.toLower() >= 'a' && next_char.toLower() <= 'f')) &&
                        (next_char2.isDigit() || (next_char2.toLower() >= 'a' && next_char2.toLower() <= 'f')))) {
                // Two-digit hex number
                hex_list << QString("%1%2").arg(next_char).arg(next_char2);
                i += 3;
            } else if (next_char.isDigit() || (next_char.toLower() >= 'a' && next_char.toLower() <= 'f')) {
                // Single-digit hex number
                hex_list << QString("0%1").arg(next_char);
                i += 2;
            } else {
                // Invalid escape sequence, treat as normal character
                hex_list << QString("%1").arg(ascii_string[i].unicode(), 2, 16, QChar('0'));
                i += 2;
            }
        } else {
            // Normal character
            hex_list << QString("%1").arg(ascii_string[i].unicode(), 2, 16, QChar('0'));
            i++;
        }
    }

    return hex_list.join(' ');
}
