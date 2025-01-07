import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material 

import "../panels"

Rectangle {
    // Layout.preferredWidth: layout.width + 10
    Layout.preferredHeight: layout.height + 20
    radius: 5
    color: "white"

    GridLayout {
        id: layout
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            topMargin: 10
            leftMargin: 10
        }
        columns: 2
        rowSpacing: 10

        // Label {
        //     // Layout.preferredWidth: labelWidth
        //     text: "Port:"
        //     font.pixelSize: 12
        //     font.bold: true
        // }

        ComboBox {
            Layout.preferredWidth: 160
            Layout.preferredHeight: 40
            model: rootStore.comPortModel
            textRole: "display"
            currentIndex: rootStore.comPortModel.selectedPortIdx
            onCurrentIndexChanged: {
                rootStore.comPortModel.selectedPortIdx = currentIndex;
            }
        }

        Button {
            id: connectionButton
            Layout.preferredWidth: 160
            text: rootStore.interfaceExpander.isConnected === false ? "Connect" : "Disconnect"
            enabled: rootStore.comPortModel.portCount > 0
            onClicked: function() {
                if (rootStore.interfaceExpander.isConnected === false) {
                    rootStore.interfaceExpander.sendOpenPort(rootStore.comPortModel.getSelectedPort());
                }else {
                    rootStore.interfaceExpander.sendClosePort();
                }
            }
        }
    }
}
