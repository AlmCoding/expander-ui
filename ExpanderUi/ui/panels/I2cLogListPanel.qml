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
            name: "Bill Smith"
            number: "555 3264"
        }
        ListElement {
            name: "John Brown"
            number: "555 8426"
        }
        ListElement {
            name: "Sam Wise"
            number: "555 0473"
        }
        ListElement {
            name: "Bill Smith"
            number: "555 3264"
        }
        ListElement {
            name: "John Brown"
            number: "555 8426"
        }
        ListElement {
            name: "Sam Wise"
            number: "555 0473"
        }
        ListElement {
            name: "Bill Smith"
            number: "555 3264"
        }
        ListElement {
            name: "John Brown"
            number: "555 8426"
        }
        ListElement {
            name: "Sam Wise"
            number: "555 0473"
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
