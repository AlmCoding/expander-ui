import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import expander.containers.i2c


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
                if (currentIndex === 0) {
                    rootStore.i2cStore.selectedInterface =  I2cConfigTypes.I2c0;
                } else {
                    rootStore.i2cStore.selectedInterface =  I2cConfigTypes.I2c1;
                }
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
