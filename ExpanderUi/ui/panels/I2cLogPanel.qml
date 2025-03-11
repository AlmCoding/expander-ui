import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Material

Rectangle {
    color: constants.primaryColor
    property int formMargin: 5

    // Define action enum
    enum ActionType {
        Open,
        SaveAs
    }
    property int currentAction: I2cRequestListPanel.ActionType.Open
    property string currentFilePath: ""

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        I2cLogListPanel {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - requestForm.visible * (requestForm.height + formMargin) - (buttonRow.height + parent.spacing)
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: buttonRow.height
            Layout.alignment: Qt.AlignBottom
            color: "white"

            RowLayout {
                id: buttonRow
                anchors.right: parent.right
                spacing: 10

                Button {
                    id: clearButton
                    Layout.preferredWidth: 90
                    text: "Clear"
                    onClicked: function() {
                        rootStore.i2cStore.i2cLogModel.clear();
                    }
                }
                Button {
                    id: fileButton
                    Layout.preferredWidth: 90
                    Layout.rightMargin: parent.spacing
                    text: "&File"
                    onClicked: menu.open()

                    Menu {
                        id: menu
                        y: fileButton.height

                        MenuItem {
                            text: "Save &As..."
                            onTriggered: {
                                currentAction = I2cRequestListPanel.ActionType.SaveAs
                                fileDialog.fileMode = FileDialog.SaveFile;
                                fileDialog.open()
                            }
                        }
                        MenuItem {
                            text: "&Open..."
                            onTriggered: {
                                currentAction = I2cRequestListPanel.ActionType.Open
                                fileDialog.fileMode = FileDialog.OpenFile;
                                fileDialog.open()
                            }
                        }
                    }
                }
            }
        }

        I2cRequestFormPanel {
            id: requestForm
            Layout.fillWidth: true
            Layout.preferredHeight: 270
            Layout.topMargin: formMargin
            visible: rootStore.i2cStore.i2cRequestForm.visible
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
                case I2cRequestListPanel.ActionType.Open:
                    rootStore.i2cStore.i2cLogModel.loadLogsFromFile(currentFilePath);
                    break;
                case I2cRequestListPanel.ActionType.SaveAs:
                    rootStore.i2cStore.i2cLogModel.saveLogsToFile(currentFilePath);
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
