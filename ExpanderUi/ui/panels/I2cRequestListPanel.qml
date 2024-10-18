import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
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
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 0

        // Button {
        //     id: loadButton
        //     Layout.preferredWidth: 90
        //     text: "Load"
        //     onClicked: function() {
        //         rootStore.i2cStore.i2cRequestModel.loadRequestsFromFile("C:/Users/Alexander/Downloads/requests.txt");
        //     }
        // }
        // Button {
        //     id: saveButton
        //     Layout.preferredWidth: 90
        //     text: "Save"
        //     onClicked: function() {
        //         rootStore.i2cStore.i2cRequestModel.saveRequestsToFile("C:/Users/Alexander/Downloads/requests.txt");
        //     }
        // }

        Button {
            id: fileButton
            text: "&File"
            Layout.leftMargin: 10
            Layout.preferredWidth: 90
            onClicked: menu.open()

            Menu {
                id: menu
                y: fileButton.height

                Action {
                    text: qsTr("&New...")
                    onTriggered: {}
                }
                Action {
                    text: qsTr("&Open...")
                    onTriggered: {
                        fileDialog.open();
                        // rootStore.i2cStore.i2cRequestModel.loadRequestsFromFile("C:/Users/Alexander/Downloads/requests.txt");
                    }
                }
                Action {
                    text: qsTr("&Save")
                    onTriggered: {}
                }
                Action {
                    text: qsTr("Save &As...")
                    onTriggered: {}
                }
            }
        }

        // MenuBar {
        //     Layout.fillHeight: true
        //     // Layout.leftMargin: 10
        //     Menu {
        //         title: qsTr("&File")
        //         Action { text: qsTr("&New...") }
        //         Action { text: qsTr("&Open...") }
        //         Action { text: qsTr("&Save") }
        //         Action { text: qsTr("Save &As...") }
        //     }
        // }

        Item {
            id: spacer
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Button {
            id: newButton
            Layout.preferredWidth: 90
            Layout.rightMargin: 10
            text: "New"
            onClicked: {
                rootStore.i2cStore.addNewRequest();
            }
        }
    }

    // FileDialog for selecting or creating a file
    FileDialog {
        id: fileDialog
        title: "Set File"
        onAccepted: {
            console.log("Selected file:", fileDialog.selectedFile)
            // You can handle the file here, e.g., open or create a new file.
        }
        onRejected: {
            console.log("File dialog canceled.")
        }
        // Set the options for the dialog
        //selectExisting: true // Set to false to allow creating new files
        //folder: "file:///path/to/your/directory" // Specify the initial directory
        nameFilters: ["Text files (*.txt)", "All files (*)"] // Set filters for file types
    }
}
