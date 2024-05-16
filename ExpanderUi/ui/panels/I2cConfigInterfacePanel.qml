import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Rectangle {
    color: "white"

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        StackLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - tabBar.height
            currentIndex: tabBar.currentIndex

            Item {
                id: i2c1Tab
                I2cConfigInterfacePanelTab {
                }
            }
            Item {
                id: i2c2Tab
                I2cConfigInterfacePanelTab {
                }
            }
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton {
                text: qsTr("I2C (1)")
            }
            TabButton {
                text: qsTr("I2C (2)")
            }
        }
    }
}
