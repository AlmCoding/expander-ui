import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import expander.containers.types

ColumnLayout {
    spacing: 0
    anchors.fill: parent
    anchors.leftMargin: 10

    GridLayout {
        Layout.fillWidth: true
        Layout.rightMargin: 10
        columns: 4
        columnSpacing: 15
        rowSpacing: 10

        Label {
            text: "Name"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            text: rootStore.i2cStore.i2cRequestForm.name
            onTextChanged: function() {
                if (rootStore.i2cStore.i2cRequestForm.externalUpdate === false &&
                        rootStore.i2cStore.i2cRequestForm.type === I2cTypes.SlaveConfig) {
                    rootStore.i2cStore.i2cRequestForm.name = text;
                }
            }
        }

        TextField {
            Layout.preferredWidth: 100
            Layout.preferredHeight: 40
            text: ""
            enabled: false
            Rectangle {
                anchors.fill: parent
                color: "white"
            }
        }

        Label {
            text: "Slave Address"
            font.pixelSize: 12
            font.bold: true
            Rectangle {
                anchors.fill: parent
                color: "white"
            }
        }

        Label {
            text: "Write Data"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            font.family: "Courier"
            text: rootStore.i2cStore.i2cRequestForm.writeData
            placeholderText: "HEX (aa bb cc)"
            validator: RegularExpressionValidator {
                // Allow only hex numbers
                regularExpression: constants.regExpWriteData
            }
            onTextChanged: function() {
                if (rootStore.i2cStore.i2cRequestForm.externalUpdate === false &&
                        rootStore.i2cStore.i2cRequestForm.asciiUpdate === false &&
                        rootStore.i2cStore.i2cRequestForm.type === I2cTypes.SlaveConfig) {
                    rootStore.i2cStore.i2cRequestForm.writeData = text
                }
            }
        }

        TextField {
            Layout.preferredWidth: 100
            Layout.preferredHeight: 40
            text: rootStore.i2cStore.i2cRequestForm.writeSize
            placeholderText: "DEC"
            enabled: false
        }

        Label {
            text: "Bytes"
            font.pixelSize: 12
            font.bold: true
        }

        Rectangle {
        }

        TextField {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            font.family: "Courier"
            text: rootStore.i2cStore.i2cRequestForm.writeDataAscii
            placeholderText: "ASCII (xYz)"
            //validator: RegularExpressionValidator {
            //    // Allow only hex numbers
            //    regularExpression: constants.regExpWriteData
            //}
            onTextChanged: function() {
                if (rootStore.i2cStore.i2cRequestForm.externalUpdate === false &&
                        rootStore.i2cStore.i2cRequestForm.hexUpdate === false &&
                        rootStore.i2cStore.i2cRequestForm.type === I2cTypes.SlaveConfig) {
                    rootStore.i2cStore.i2cRequestForm.writeDataAscii = text
                }
            }
        }

        Rectangle {
        }

        Rectangle {
        }

        Label {
            text: "Read Size"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.preferredWidth: 80
            Layout.preferredHeight: 40
            text: rootStore.i2cStore.i2cRequestForm.readSize
            placeholderText: "DEC"
            validator: RegularExpressionValidator {
                // Allow only hex numbers no larger than 10 bits
                regularExpression: constants.regExpReadSize
            }
            onTextChanged: function() {
                if (rootStore.i2cStore.i2cRequestForm.externalUpdate === false &&
                        rootStore.i2cStore.i2cRequestForm.type === I2cTypes.SlaveConfig) {
                    rootStore.i2cStore.i2cRequestForm.readSize = text
                }
            }
        }
    }
}
