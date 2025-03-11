import QtQuick
import expander.Utility

Item {
    property Utility utility: Utility {
        id: utility
    }

    readonly property color primaryColor: "#607D8B"
    readonly property color footerColor:  "#607D8B"

    readonly property color i2c0Color: "#4CAF50"
    readonly property color i2c1Color: "#CDDC39"
    readonly property color masterColor: "lightgray"
    readonly property color slaveColor: "#FFC107"
    readonly property color statusField: "#B0BEC5"

    // For slave address allow only hex numbers no larger than 10 bits
    readonly property var regExpSlaveAddress: new RegExp(/^0x[0-3][0-9A-Fa-f]{2}$|^0x[0-9A-Fa-f]{2}$/)

    // For write data allow only hex input with spaces are sparator
    readonly property var regExpWriteData: new RegExp(/\b([0-9A-Fa-f]{2})(\s[0-9A-Fa-f]{2})*\b/)

    // For read size allow dec numbers
    readonly property var regExpReadSize: new  RegExp(/^(12[0-8]|1[01][0-9]|[1-9]?[0-9])$/)

    readonly property string firmwareDirectory: utility.appDataPath() + "/firmware"

    readonly property int listViewHighlightMoveDuration: 100
}
