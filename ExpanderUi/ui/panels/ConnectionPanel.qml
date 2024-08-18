import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 

import "../panels"


Rectangle {
    // Layout.preferredWidth: layout.width + 10
    Layout.preferredHeight: layout.height + 10
    radius: 5
    color: "white"

    RowLayout {
        id: layout
        anchors.centerIn: parent
        spacing: 10

        Label {
            // Layout.preferredWidth: labelWidth
            text: "Port:"
            font.pixelSize: 12
            font.bold: true
        }

        ComboBox {
            // Layout.preferredWidth: 150
            Layout.preferredHeight: 40
            model: rootStore.comPortModel
            textRole: "display"
            currentIndex: rootStore.comPortModel.selectedPortIdx
            onCurrentIndexChanged: {
                rootStore.comPortModel.selectedPortIdx = currentIndex;
            }
        }

        Button {
            id: connectButton
            text: "Connect"
            enabled: rootStore.comPortModel.portCount > 0 && rootStore.interfaceExpander.isConnected == false
            onClicked: function() {
                rootStore.interfaceExpander.sendOpenPort(rootStore.comPortModel.getSelectedPort());
            }
        }

        Button {
            id: disconnectButton
            text: "Disconnect"
            enabled: rootStore.interfaceExpander.isConnected
            onClicked: function() {
                rootStore.interfaceExpander.sendClosePort();
            }
        }
    }
}
