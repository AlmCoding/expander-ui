import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../panels"


Rectangle {
    Layout.preferredHeight: layout.height + 20
    radius: 5
    color: "white"

    GridLayout {
        id: layout
        // width: parent.width / 2
        // anchors.fill: parent
        // anchors.centerIn: parent
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            topMargin: 10
            leftMargin: 10
        }
        columns: 2
        rowSpacing: 10

        Label {
            text: "Firmware Version:"
            font.pixelSize: 12
            font.bold: true
        }

        Text {
            text: rootStore.interfaceExpander.fwVersion
        }

        Label {
            text: "Hardware Version:"
            font.pixelSize: 12
            font.bold: true
        }

        Text {
            text: rootStore.interfaceExpander.hwVersion
        }

        Button {
            id: installButton
            text: "Install Firmware"
            enabled: true // rootStore.interfaceExpander.isConnected
            onClicked: function() {
                // rootStore.interfaceExpander.sendCtrlStartBootloader();
                rootStore.interfaceExpander.startFirmwareUpdate("C:/projects/expander/expander-mcu/ExpanderFw/Debug/ExpanderFw.hex");
            }
        }

        ComboBox {
            // Layout.preferredWidth: 150
            Layout.preferredHeight: 40
            model: ["V0.0.1", "V0.0.1", "V0.0.2", "V0.0.3"]
        }
    }
}



