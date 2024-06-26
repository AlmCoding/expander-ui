import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


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
                model: rootStore.i2cRequestModel // RequestModel {}
                delegate: I2cRequestListComponent {}
                highlight: Rectangle { color: "#00BCD4"; radius: 0 }
                focus: true
                currentIndex: rootStore.i2cRequestModel.selectedRequestIdx
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
        }
        Button {
            id: saveButton
            Layout.preferredWidth: 90
            text: "Save"
        }
        Button {
            id: newButton
            Layout.preferredWidth: 90
            text: "New"
            onClicked: {
                rootStore.addNewRequest();
            }
        }
    }
}
