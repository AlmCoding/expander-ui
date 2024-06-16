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
            Layout.preferredHeight: parent.height - tabBar.height - applyButton.height
            currentIndex: tabBar.currentIndex

            Item {
                id: i2c1Tab
                I2cConfigInterfacePanelTab {
                    i2cConfigForm: rootStore.i2cStore.i2cConfigForm0
                }
            }
            Item {
                id: i2c2Tab
                I2cConfigInterfacePanelTab {
                    i2cConfigForm: rootStore.i2cStore.i2cConfigForm1
                }
            }
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            onCurrentIndexChanged: {
                // TODO: Info needed for where requests shall be send (I2c1 or I2c2)
            }

            TabButton {
                text: "I2C (1)"
            }
            TabButton {
                text: "I2C (2)"
            }
        }

        Button {
            id: applyButton
            Layout.fillWidth: true
            Layout.margins: 10
            text: "Apply"
            onClicked: {
                rootStore.applyI2cConfig();
            }
        }
    }
}
