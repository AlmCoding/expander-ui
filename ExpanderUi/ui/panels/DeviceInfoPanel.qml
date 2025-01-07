import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import expander.containers.types

import "../panels"

Rectangle {
    Layout.preferredHeight: layout.height + 20
    radius: 5
    color: "white"

    property string resultDialogeTitle: ""
    property string resultDialogeText: ""

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
            text: "Hardware Version:"
            font.pixelSize: 12
            font.bold: true
        }

        Text {
            text: rootStore.interfaceExpander.hwVersion
        }

        Label {
            text: "Firmware Version:"
            font.pixelSize: 12
            font.bold: true
        }

        Text {
            text: rootStore.interfaceExpander.fwVersion
        }

        Label {
            text: "Git Hash:"
            font.pixelSize: 12
            font.bold: true
        }

        Text {
            text: rootStore.interfaceExpander.gitHash
        }

        Button {
            id: installButton
            Layout.preferredWidth: 160
            text: rootStore.firmwareFileModel.newerVersionSelected === true ? "Upgrade Firmware" : "Install Firmware"
            Material.background: rootStore.firmwareFileModel.newerVersionSelected === true ? Material.Pink : Material.Foreground

            enabled: true // rootStore.interfaceExpander.isConnected
            onClicked: function() {
                var firmware_file = rootStore.firmwareFileModel.getSelectedFile();
                console.log("Install firmware file: " + firmware_file);
                dialog.open();
                rootStore.interfaceExpander.sendCtrlStartBootloader();
                rootStore.interfaceExpander.startFirmwareUpdate(firmware_file);
            }
        }

        ComboBox {
            Layout.preferredWidth: 160
            Layout.preferredHeight: 40
            model: rootStore.firmwareFileModel
            textRole: "display"
            currentIndex: rootStore.firmwareFileModel.selectedFileIdx
            onCurrentIndexChanged: {
                rootStore.firmwareFileModel.selectedFileIdx = currentIndex;
            }
        }
    }

    Connections {
        target: rootStore.interfaceExpander
        function onInstallerStateChanged(state) {
            if (state === InstallerTypes.Success) {
                console.log("Install firmware success.")
                dialog.close();
                resultDialogeTitle = "Firmware Update Successful!";
                resultDialogeText = "Please remove and reinsert the device.";
                resultDialog.open();

            } else if (state === InstallerTypes.Error) {
                console.log("Install firmware failed!")
                dialog.close();
                resultDialogeTitle = "Firmware Update Failed!";
                resultDialogeText = "Please check <b>www.intexp.com/confail</b> for more information.";
                resultDialog.open();
            }
        }
    }

    Dialog {
        id: dialog
        anchors.centerIn: Overlay.overlay
        title: "Firmware Update"        
        modal: true
        closePolicy: Popup.NoAutoClose

        ColumnLayout {
            spacing: 10

            Text {
                Layout.topMargin: 10
                text: "Please wait and don't remove the device!"
                font.pixelSize: 12
            }

            ProgressBar {
                Layout.bottomMargin: 10
                Layout.preferredWidth: parent.width
                indeterminate: true
            }
        }

        onRejected: {
            console.log("Rejected!")
            Qt.callLater(dialog.open)
        }
    }

    Dialog {
        id: resultDialog
        anchors.centerIn: Overlay.overlay
        title: resultDialogeTitle
        modal: true
        standardButtons: Dialog.Ok

        ColumnLayout {
            spacing: 10
            anchors.fill: parent

            Text {
                Layout.topMargin: 10
                text: resultDialogeText
                font.pixelSize: 12
            }
        }

        onAccepted: {
            resultDialog.close()
        }
    }
}



