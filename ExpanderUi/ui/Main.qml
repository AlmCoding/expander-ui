import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "views"


Window {
    id: root
    Material.theme: Material.Light
    Material.accent: Material.Cyan

    width: 1920 / 2
    height: 1080 * 3 / 4
    visible: true
    title: qsTr("Interface Expander")

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton {
                text: qsTr("I2C")
            }
            TabButton {
                text: qsTr("SPI")
            }
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
                Item {
                    id: spiTab
                    SpiView {
                        anchors.fill: parent
                    }
                }
                Item {
                    id: settingsTab
                    SettingsView {
                        anchors.fill: parent
                    }
                }
            }
        }

        Rectangle {
            id: footer
            Layout.fillWidth: true
            Layout.preferredHeight: 25
            color: "#00BCD4"
        }
    }
}
