import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Rectangle {
    color: "lightgray"

    ColumnLayout {
        anchors.fill: parent

        StackLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - tabBar.height
            currentIndex: tabBar.currentIndex

            Item {
                id: i2c12Tab

            }
            Item {
                id: i2c1Tab

            }
            Item {
                id: i2c2Tab
            }
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton {
                text: qsTr("I2C (1+2)")
            }
            TabButton {
                text: qsTr("I2C (1)")
            }
            TabButton {
                text: qsTr("I2C (2)")
            }
        }
    }
}
