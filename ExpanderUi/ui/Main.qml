import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "views"
import "stores"
import "panels"

Window {
    id: root
    Material.theme: Material.Light
    Material.accent: Material.Cyan

    width: 1920 / 2
    height: 1080 * 3 / 4
    visible: true
    title: qsTr("Interface Expander - ") + Qt.application.version

    Constants {
        id: constants
    }

    RootStore {
        id: rootStore
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton {
                text: qsTr("I2C")
            }
            // TabButton {
            //     text: qsTr("SPI")
            // }
            TabButton {
                text: qsTr("Settings")
            }
        }

        Rectangle {
            id: background
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - tabBar.height - footer.height
            color: "#00BCD4"
            // color: "black"

            StackLayout {
                anchors.fill: parent
                currentIndex: tabBar.currentIndex

                Item {
                    id: i2cTab
                    I2cView {
                        anchors.fill: parent
                    }
                }
                // Item {
                //     id: spiTab
                //     SpiView {
                //         anchors.fill: parent
                //     }
                // }
                Item {
                    id: settingsTab
                    SettingsView {
                        anchors.fill: parent
                    }
                }
            }
        }

        FooterPanel {
            id: footer
            Layout.fillWidth: true
            Layout.preferredHeight: 30
        }
    }

    Dialog {
        id: updateDialog
        anchors.centerIn: Overlay.overlay
        title: "Update Available"
        modal: true
        closePolicy: Popup.NoAutoClose
        standardButtons: Dialog.Ok

        ColumnLayout {
            spacing: 10
            anchors.fill: parent

            Text {
                Layout.topMargin: 10
                text: "A newer version of the software is available."
                font.pixelSize: 12
            }

            Button {
                text: "Open Download Page"
                onClicked: {
                    Qt.openUrlExternally("https://github.com/AlmCoding/expander-ui/releases");
                    updateDialog.close();
                }
            }
        }

        onAccepted: {
            updateDialog.close()
        }

        Connections {
            target: rootStore.updateManager
            function onUpdateAvailableChanged() {
                updateDialog.open();
            }
        }
    }
}
