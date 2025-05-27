import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Dialog {
    id: logDetailsDialog
    anchors.centerIn: Overlay.overlay
    //title: "Request name ..."
    modal: true
    closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape
    standardButtons: Dialog.Ok
    width: 540

    ColumnLayout {
        id: rootColumn
        anchors.fill: parent
        spacing: 0

        RowLayout {
            id: titleRow
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            spacing: 0

            Rectangle {
                id: requestName
                Layout.fillHeight: true
                implicitWidth: nameTextField.implicitWidth + nameTextField.leftPadding
                Layout.margins: 3
                radius: 5
                color: "lightgray"

                Text {
                    id: nameTextField
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 5
                    text: "<b>" + rootStore.i2cStore.i2cLogDetails.name + "</b>"
                }
            }

            Rectangle {
                id: interfaceNum
                Layout.fillHeight: true
                Layout.preferredWidth: 40
                Layout.margins: 3
                radius: 3
                color:  (rootStore.i2cStore.i2cLogDetails.interface === "I2c0") ? constants.i2c0Color : constants.i2c1Color

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: (rootStore.i2cStore.i2cLogDetails.interface === "I2c0") ? "<b>I2c1</b>" :  "<b>I2c2</b>"
                }
            }

            Rectangle {
                id: logType
                Layout.fillHeight: true
                Layout.preferredWidth: 40
                Layout.margins: 3
                radius: 3
                color: (rootStore.i2cStore.i2cLogDetails.type === "MR") ? constants.masterColor : constants.slaveColor

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "<b>" + rootStore.i2cStore.i2cLogDetails.type + "</b>"
                }
            }

            Rectangle {
                id: slaveAddr
                Layout.fillHeight: true
                Layout.preferredWidth: 80
                Layout.margins: 3
                color: "white"

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 5
                    text: (rootStore.i2cStore.i2cLogDetails.type === "MR") ? ("<b>Slave:</b> " + rootStore.i2cStore.i2cLogDetails.slaveAddr) : ""
                }
            }

            Item { Layout.fillWidth: true }

            Rectangle {
                id: statusField
                Layout.fillHeight: true
                implicitWidth: statusTextField.implicitWidth + statusTextField.leftPadding
                Layout.margins: 3
                radius: 3
                color: (rootStore.i2cStore.i2cLogDetails.status === "Success") ? constants.statusFieldSuccess : constants.statusFieldWarning

                Text {
                    id: statusTextField
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 5
                    text: rootStore.i2cStore.i2cLogDetails.status
                }
            }
        }

        RowLayout {
            id: writeSizeRow
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            Layout.topMargin: 15
            spacing: 0

            Rectangle {
                Layout.fillHeight: true
                Layout.preferredWidth: 120
                Layout.margins: 3
                radius: 5

                Text {
                    id: writeSize
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 5
                    text: "<b>Write (" + rootStore.i2cStore.i2cLogDetails.writeSize + "):</b>"
                }
            }
        }

        RowLayout {
            id: writeDataRow
            Layout.fillWidth: true
            Layout.preferredHeight: 90
            spacing: 0

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.margins: 3
                radius: 5
                color: "#f6f6f6"

                TextEdit {
                    id: writeData
                    anchors.fill: parent
                    leftPadding: 5
                    font.family: "Courier"
                    //font.pointSize: 12
                    focus: true
                    wrapMode: TextEdit.WordWrap
                    readOnly: true
                    text: rootStore.i2cStore.i2cLogDetails.writeData
                }
            }
        }

        RowLayout {
            id: writeDataAsciiRow
            Layout.fillWidth: true
            Layout.preferredHeight: 90
            spacing: 0

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.margins: 3
                radius: 5
                color: "#f6f6f6"

                TextEdit {
                    id: writeDataAscii
                    anchors.fill: parent
                    leftPadding: 5
                    font.family: "Courier"
                    //font.pointSize: 12
                    focus: true
                    wrapMode: TextEdit.Wrap
                    readOnly: true
                    text: rootStore.i2cStore.i2cLogDetails.writeDataAscii
                }
            }
        }

        RowLayout {
            id: readSizeRow
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            Layout.topMargin: 15
            spacing: 0

            Rectangle {
                Layout.fillHeight: true
                Layout.preferredWidth: 120
                Layout.margins: 3
                radius: 5

                Text {
                    id: readeSize
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 5
                    text: "<b>Read (" + rootStore.i2cStore.i2cLogDetails.readSize + "):</b>"
                }
            }
        }

        RowLayout {
            id: readDataRow
            Layout.fillWidth: true
            Layout.preferredHeight: 90
            spacing: 0

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.margins: 3
                radius: 5
                color: "#f6f6f6"

                TextEdit {
                    id: readData
                    anchors.fill: parent
                    leftPadding: 5
                    font.family: "Courier"
                    //font.pointSize: 12
                    focus: true
                    wrapMode: TextEdit.WordWrap
                    readOnly: true
                    text: rootStore.i2cStore.i2cLogDetails.readData
                }
            }
        }

        RowLayout {
            id: readDataAsciiRow
            Layout.fillWidth: true
            Layout.preferredHeight: 90
            spacing: 0

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.margins: 3
                radius: 5
                color: "#f6f6f6"

                TextEdit {
                    id: readDataAscii
                    anchors.fill: parent
                    leftPadding: 5
                    font.family: "Courier"
                    //font.pointSize: 12
                    focus: true
                    wrapMode: TextEdit.Wrap
                    readOnly: true
                    text: rootStore.i2cStore.i2cLogDetails.readDataAscii
                }
            }
        }
    }

    onAccepted: {
        logDetailsDialog.close()
    }

    Connections {
        target: rootStore.i2cStore.i2cLogDetails
        function onVisibleChanged(visible) {
            if (visible === true) {
                logDetailsDialog.open();
            }
        }
    }
}
