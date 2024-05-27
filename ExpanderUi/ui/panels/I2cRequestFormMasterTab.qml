import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


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
            text: rootStore.i2cRequestForm.name
            onTextChanged: function() {
                if (rootStore.i2cRequestForm.externalUpdate === false) {
                    rootStore.i2cRequestForm.name = text;
                }
            }
        }

        TextField {
            Layout.preferredWidth: 100
            Layout.preferredHeight: 40
            text: rootStore.i2cRequestForm.slaveAddress
            placeholderText: "HEX (0x001)"
            validator: RegularExpressionValidator {
                regularExpression: constants.regExpSlaveAddress
            }
            onTextChanged: function() {
                if (rootStore.i2cRequestForm.externalUpdate === false) {
                    rootStore.i2cRequestForm.slaveAddress = text
                }
            }
        }

        Label {
            text: "Slave Address"
            font.pixelSize: 12
            font.bold: true
        }

        Label {
            text: "Write Data"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            text: rootStore.i2cRequestForm.writeData
            placeholderText: "HEX (aa bb cc)"
            validator: RegularExpressionValidator {
                // Allow only hex numbers
                regularExpression: constants.regExpWriteData
            }
            onTextChanged: function() {
                if (rootStore.i2cRequestForm.externalUpdate === false) {
                    rootStore.i2cRequestForm.writeData = text
                }
            }
        }

        TextField {
            Layout.preferredWidth: 100
            Layout.preferredHeight: 40
            text: rootStore.i2cRequestForm.writeSize
            enabled: false
        }

        Label {
            text: "Bytes"
            font.pixelSize: 12
            font.bold: true
        }

        Label {
            text: "Read Size"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.preferredWidth: 80
            Layout.preferredHeight: 40
            text: rootStore.i2cRequestForm.readSize
            placeholderText: "DEC (42)"
            validator: RegularExpressionValidator {
                // Allow only hex numbers no larger than 10 bits
                regularExpression: constants.regExpReadSize
            }
            onTextChanged: function() {
                if (rootStore.i2cRequestForm.externalUpdate === false) {
                    rootStore.i2cRequestForm.readSize = text
                }
            }
        }
    }
}
