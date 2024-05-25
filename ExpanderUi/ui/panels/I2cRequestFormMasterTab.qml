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
            // Layout.preferredWidth: 40
            text: "Name"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.fillWidth: true
            // Layout.preferredWidth: 250
            // placeholderText: "Name"
        }

        TextField {
            Layout.preferredWidth: 100
            placeholderText: "HEX (0x001)"
        }

        Label {
            // Layout.preferredWidth: 60
            text: "Slave Address"
            font.pixelSize: 12
            font.bold: true
        }

        Label {
            // Layout.preferredWidth: 50
            text: "Write Data"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.fillWidth: true
            // Layout.preferredWidth: 250
            placeholderText: "HEX (aa bb cc)"
            validator: RegularExpressionValidator {
                // Allow only hex numbers
                regularExpression: /\b([0-9A-Fa-f]{2})(\s[0-9A-Fa-f]{2})*\b/
            }
        }

        TextField {
            Layout.preferredWidth: 100
            enabled: false
        }

        Label {
            // Layout.preferredWidth: 85
            text: "Bytes"
            font.pixelSize: 12
            font.bold: true
        }

        Label {
            // Layout.preferredWidth: 85
            text: "Read Size"
            font.pixelSize: 12
            font.bold: true
        }

        TextField {
            Layout.preferredWidth: 80
            placeholderText: "DEC (42)"
            validator: RegularExpressionValidator {
                // Allow only hex numbers no larger than 10 bits
                regularExpression: /^(12[0-8]|1[01][0-9]|[1-9]?[0-9])$/
            }
        }
    }

    RowLayout {
        spacing: 10

        Button {
            text: "Delete"
            onClicked: {
                rootStore.deleteRequest();
            }
        }
        Button {
            text: "Clear"
            onClicked: {
                rootStore.clearRequest();
            }
        }
        Button {
            text: "Done"
            onClicked: {
                // rootStore.saveRequest();
                rootStore.i2cRequestForm.visible = false;
            }
        }
    }
}
