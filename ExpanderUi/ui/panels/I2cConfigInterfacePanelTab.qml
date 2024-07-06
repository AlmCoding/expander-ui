import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import expander.forms
import expander.containers.types


ColumnLayout {
    spacing: 5
    property var i2cConfigForm
    readonly property int labelWidth: 130

    GridLayout {
        Layout.fillWidth: true
        Layout.leftMargin: 10
        columns: 2

        Label {
            Layout.preferredWidth: labelWidth
            text: "Memory Address Width"
            font.pixelSize: 12
            font.bold: true
        }

        RowLayout {
            RadioButton {
                checked: i2cConfigForm.memAddrWidth === I2cTypes.OneByte
                text: "1 Byte"
                onClicked: function() {
                    i2cConfigForm.memAddrWidth = I2cTypes.OneByte;
                    rootStore.applyI2cConfig();
                }
            }
            RadioButton {
                checked: i2cConfigForm.memAddrWidth === I2cTypes.TwoByte
                text: "2 Bytes"
                onClicked: function() {
                    i2cConfigForm.memAddrWidth = I2cTypes.TwoByte;
                    rootStore.applyI2cConfig();
                }
            }
        }

        Label {
            Layout.preferredWidth: labelWidth
            text: "Slave Address Width"
            font.pixelSize: 12
            font.bold: true
        }

        RowLayout {
            RadioButton {
                checked: i2cConfigForm.slaveAddrWidth === I2cTypes.SevenBit
                text: "7 Bit"
                onClicked: function() {
                    i2cConfigForm.slaveAddrWidth = I2cTypes.SevenBit;
                    rootStore.applyI2cConfig();
                }
            }
            RadioButton {
                checked: i2cConfigForm.slaveAddrWidth === I2cTypes.TenBit
                text: "10 Bit"
                onClicked: function() {
                    i2cConfigForm.slaveAddrWidth = I2cTypes.TenBit;
                    rootStore.applyI2cConfig();
                }
            }
        }

        Label {
            Layout.preferredWidth: labelWidth
            text: "Slave Address"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.preferredWidth: 150
            Layout.preferredHeight: 40
            text: i2cConfigForm.slaveAddr
            placeholderText: "HEX (0x001)"
            validator: RegularExpressionValidator {
                regularExpression: constants.regExpSlaveAddress
            }
            onTextChanged: function() {
                i2cConfigForm.slaveAddr = text
            }
            onFocusChanged: function() {
                if (focus === false) {
                    rootStore.applyI2cConfig();
                }
            }
        }

        Label {
            Layout.preferredWidth: labelWidth
            text: "Clock Frequency"
            font.pixelSize: 12
            font.bold: true
        }

        ComboBox {
            Layout.preferredWidth: 150
            Layout.preferredHeight: 40
            model: ["1 MHz", "400 kHz", "100 kHz", "10 kHz"]
            onCurrentIndexChanged: function() {
                switch (currentIndex) {
                case 0: i2cConfigForm.clockFreq = I2cTypes.KHz1000;
                    break;
                case 1: i2cConfigForm.clockFreq = I2cTypes.KHz400;
                    break;
                case 2: i2cConfigForm.clockFreq = I2cTypes.KHz100;
                    break;
                case 3: i2cConfigForm.clockFreq = I2cTypes.KHz10;
                    break;
                }
                rootStore.applyI2cConfig();
            }
        }
    }
}



