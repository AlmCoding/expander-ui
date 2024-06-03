import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"


Rectangle {
    color: "lightgray"

    ListModel {
        id: listModel
        ListElement {
            time: "31d24h22m12s122ms"
            i2cInterface: "I2c1"
            logType: "MR"
            name: "Turn Pump ON"
            slaveAddr: "0x042"
            writeData: "ff 42 ff 12 23 34 45 56 67 78 12"
            readData: "42 34 54 74 76 85 32 53"
            writeSize: "32"
            readSize: "42"
            status: "Status"
        }
        ListElement {
            time: "06d09h43m12s122ms"
            i2cInterface: "I2c2"
            logType: "MR"
            name: "Turn Pump ON"
            slaveAddr: "0x042"
            writeData: "ff 42 ff 12 23 34 45 56 67 78 12"
            readData: "42 34 54 74 76 85 32 53"
            writeSize: "32"
            readSize: "42"
            status: "Status"
        }
    }

    ScrollView {
        anchors.fill: parent
        clip: true

        ListView {
            id: logList
            anchors.fill: parent
            model: listModel
            delegate: I2cLogListComponent {}
            highlight: Rectangle { color: "#00BCD4"; radius: 0 }
            focus: true
            // currentIndex: 0
        }
    }
}
