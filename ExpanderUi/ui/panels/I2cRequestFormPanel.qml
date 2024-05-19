import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Rectangle {
    color: "white"

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton {
                text: qsTr("Master Request")
            }
            TabButton {
                text: qsTr("Slave Config")
            }
        }

        StackLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - tabBar.height
            currentIndex: tabBar.currentIndex

            Item {
                id: masterRequest
                I2cRequestFormMasterTab {
                }
            }
            Item {
                id: slaveConfig
                Rectangle {
                    anchors.fill: parent
                    color: "lightgray"
                }
            }
        }
    }
}

