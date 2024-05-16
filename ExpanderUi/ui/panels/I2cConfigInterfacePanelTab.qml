import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


ColumnLayout {
    spacing: 5
    readonly property int labelWidth: 130

    GridLayout {
        Layout.fillWidth: true
        columns: 2

        Label {
            Layout.preferredWidth: labelWidth
            text: "Memory address width"
            font.pixelSize: 12
            font.bold: true
        }

        RowLayout {
            RadioButton {
                checked: true
                text: qsTr("1 Byte")
            }
            RadioButton {
                text: qsTr("2 Bytes")
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
                checked: true
                text: qsTr("7 Bit")
            }
            RadioButton {
                text: qsTr("12 Bit")
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
            text: "0x01"
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
        }
    }

    Button {
        Layout.fillWidth: true
        text: "Apply"
    }
}



