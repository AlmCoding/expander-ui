import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import expander.containers.types


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
                MouseArea {
                    anchors.fill: parent
                    onClicked: tabBar.forceActiveFocus();
                }
                I2cConfigInterfacePanelTab {
                    i2cConfigForm: rootStore.i2cStore.i2cConfigForm0
                }
            }
            Item {
                id: i2c2Tab
                MouseArea {
                    anchors.fill: parent
                    onClicked: tabBar.forceActiveFocus();
                }
                I2cConfigInterfacePanelTab {
                    i2cConfigForm: rootStore.i2cStore.i2cConfigForm1
                }
            }
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            onCurrentIndexChanged: {
                if (currentIndex === 0) {
                    rootStore.i2cStore.selectedInterface =  I2cTypes.I2c0;
                } else {
                    rootStore.i2cStore.selectedInterface =  I2cTypes.I2c1;
                }
            }

            TabButton {
                text: "I2C (1)"
            }
            TabButton {
                text: "I2C (2)"
            }
        }
    }
}
