import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"


ColumnLayout {
    id: root
    spacing: 0

    Rectangle {
        id: scrollRectangle
        Layout.fillWidth: true
        Layout.preferredHeight: parent.height - buttonRow.height
        color: "lightgray"

        ScrollView {
            anchors.fill: parent
            clip: true

            ListView {
                id: requestList
                anchors.fill: parent
                model: rootStore.i2cStore.i2cRequestModel // RequestModel {}
                delegate: I2cRequestListComponent {}
                highlight: Rectangle { color: "#00BCD4"; radius: 0 }
                focus: true
                currentIndex: rootStore.i2cStore.i2cRequestModel.selectedRequestIdx
            }
        }
    }

    RowLayout {
        id: buttonRow
        Layout.alignment: Qt.AlignHCenter
        // Layout.fillWidth: true
        // Layout.preferredHeight: parent.height / 2
        spacing: 10

        Button {
            id: loadButton
            Layout.preferredWidth: 90
            text: "Load"
            onClicked: function() {
                rootStore.i2cStore.i2cRequestModel.loadRequestsFromFile("C:/Users/Alexander/Downloads/requests.txt");
            }
        }
        Button {
            id: saveButton
            Layout.preferredWidth: 90
            text: "Save"
            onClicked: function() {
                rootStore.i2cStore.i2cRequestModel.saveRequestsToFile("C:/Users/Alexander/Downloads/requests.txt");
            }
        }
        Button {
            id: newButton
            Layout.preferredWidth: 90
            text: "New"
            onClicked: {
                rootStore.i2cStore.addNewRequest();
            }
        }
    }
}
