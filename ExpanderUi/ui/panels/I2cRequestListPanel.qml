import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"

ColumnLayout {
    id: root
    spacing: 0

    // Define action enum
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

            DelegateModel {
                id: visualModel
                model: rootStore.i2cStore.i2cRequestModel
                delegate: I2cRequestListComponent {}
            }

            ListView {
                id: requestList
                anchors.fill: parent
                model: visualModel
                highlight: Rectangle { color: "#00BCD4"; radius: 0 }
                highlightMoveDuration: constants.listViewHighlightMoveDuration
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

        Button {
            id: fileButton
            Layout.leftMargin: 10
            Layout.preferredWidth: 90
            text: "&File"
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
