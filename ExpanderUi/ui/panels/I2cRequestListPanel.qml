import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"


ColumnLayout {
    id: root
    spacing: 0

    // Define Shape enum
    enum ActionType {
        New,
        Open,
        Save,
        SaveAs
    }
    property int currentAction: I2cRequestListPanel.ActionType.New
    property string currentFilePath: ""

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
                    onTriggered: {
                        currentAction = I2cRequestListPanel.ActionType.New;
                        fileDialog.fileMode = FileDialog.SaveFile;
                        fileDialog.open();
                    }
                }
                Action {
                    text: qsTr("&Open...")
                    onTriggered: {
                        currentAction = I2cRequestListPanel.ActionType.Open;
                        fileDialog.fileMode = FileDialog.OpenFile;
                        fileDialog.open();
                    }
                }
                Action {
                    text: qsTr("&Save")
                    onTriggered: {
                        currentAction = I2cRequestListPanel.ActionType.Save;
                        if (currentFilePath === "") {
                            fileDialog.fileMode = FileDialog.SaveFile;
                            fileDialog.open();
                        } else {
                            rootStore.i2cStore.i2cRequestModel.saveRequestsToFile(currentFilePath);
                        }
                    }
                }
                Action {
                    text: qsTr("Save &As...")
                    onTriggered: {
                        currentAction = I2cRequestListPanel.ActionType.SaveAs;
                        fileDialog.fileMode = FileDialog.SaveFile;
                        fileDialog.open();
                    }
                }
            }
        }

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
            // Get the local file path as a string
            currentFilePath = Qt.resolvedUrl(selectedFile);
            if (currentFilePath.startsWith("file:///")) {
                currentFilePath = currentFilePath.replace("file:///", "");
            }
            console.log("Selected file:", currentFilePath);

            switch (currentAction) {
            case I2cRequestListPanel.ActionType.New:
                // clear model and save it (empty)
                rootStore.i2cStore.i2cRequestModel.clear();
                rootStore.i2cStore.i2cRequestModel.saveRequestsToFile(currentFilePath);
                break;
            case I2cRequestListPanel.ActionType.Open:
                rootStore.i2cStore.i2cRequestModel.loadRequestsFromFile(currentFilePath);
                break;
            case I2cRequestListPanel.ActionType.Save:
            case I2cRequestListPanel.ActionType.SaveAs:
                rootStore.i2cStore.i2cRequestModel.saveRequestsToFile(currentFilePath);
                break;
            }
        }
        onRejected: {
            console.log("File dialog canceled.");
        }
        // Set the options for the dialog
        fileMode: FileDialog.SaveFile
        nameFilters: ["Text files (*.txt)", "All files (*)"] // Set filters for file types
    }
}
