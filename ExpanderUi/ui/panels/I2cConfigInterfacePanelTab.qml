import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import expander.I2cConfig


ColumnLayout {
    spacing: 5
    readonly property int labelWidth: 130
    property I2cConfig i2cConfig

    GridLayout {
        Layout.fillWidth: true
        Layout.leftMargin: 10
        columns: 2

        Label {
            Layout.preferredWidth: labelWidth
            text: "Memory address width"
            font.pixelSize: 12
            font.bold: true
        }

        RowLayout {
            RadioButton {
                checked: i2cConfig.memAddrWidth == 1
                text: qsTr("1 Byte")
                onClicked: i2cConfig.memAddrWidth = 1
            }
            RadioButton {
                checked: i2cConfig.memAddrWidth == 2
                text: qsTr("2 Bytes")
                onClicked: i2cConfig.memAddrWidth = 2
            }
        }

        Label {
            Layout.preferredWidth: labelWidth
            text: "Slave address width"
            font.pixelSize: 12
            font.bold: true
        }

        RowLayout {
            RadioButton {
                checked: i2cConfig.slaveAddrWidth == 7
                text: qsTr("7 Bit")
                onClicked: i2cConfig.slaveAddrWidth = 7
            }
            RadioButton {
                checked: i2cConfig.slaveAddrWidth == 10
                text: qsTr("10 Bit")
                onClicked: i2cConfig.slaveAddrWidth = 10
            }
        }

        Label {
            Layout.preferredWidth: labelWidth
            text: "Slave address"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.preferredWidth: 150
            Layout.preferredHeight: 40
            text: i2cConfig.slaveAddr
            validator: RegularExpressionValidator {
                // Allow only hex numbers no larger than 10 bits
                regularExpression: /^0x[0-3][0-9A-Fa-f]{2}$|^0x[0-9A-Fa-f]{2}$/
                // regularExpression: /^0x[0-9A-Fa-f]{3}$/
            }
        }

        Label {
            Layout.preferredWidth: labelWidth
            text: "Clock frequency"
            font.pixelSize: 12
            font.bold: true
        }

        ComboBox {
            Layout.preferredWidth: 150
            Layout.preferredHeight: 40
            model: ["1 MHz", "400 kHz", "100 kHz", "10 kHz"]
            onCurrentIndexChanged: {
                switch (currentIndex) {
                case 0: i2cConfig.clockFreq = 1000;
                    break;
                case 0: i2cConfig.clockFreq = 400;
                    break;
                case 0: i2cConfig.clockFreq = 100;
                    break;
                case 0: i2cConfig.clockFreq = 10;
                    break;
                }
            }
        }
    }

    // Button {
    //     Layout.fillWidth: true
    //     Layout.margins: 10
    //     text: "Apply"
    // }
}



