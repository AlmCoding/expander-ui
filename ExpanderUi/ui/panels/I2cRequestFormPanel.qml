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

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            currentIndex: (rootStore.i2cStore.i2cRequestForm.type === I2cTypes.MasterAction) ? 0 : 1;
            onCurrentIndexChanged: {
                if (rootStore.i2cStore.i2cRequestForm.externalUpdate === false) {
                    if (currentIndex === 0) {
                        rootStore.i2cStore.i2cRequestForm.type = I2cTypes.MasterAction;
                    } else {
                        rootStore.i2cStore.i2cRequestForm.type = I2cTypes.SlaveConfig;
                    }
                }
            }

            TabButton {
                //font.bold: true
                font.pointSize: constants.tabButtonTextSize
                text: qsTr("Master Request")
            }
            TabButton {
                //font.bold: true
                font.pointSize: constants.tabButtonTextSize
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
                I2cRequestFormSlaveTab {
                }
            }
        }

        Rectangle {
            Layout.fillWidth: true
            // Layout.leftMargin: buttonRow.spacing
            Layout.preferredHeight: buttonRow.height
            Layout.alignment: Qt.AlignBottom
            color: "white"

            RowLayout {
                id: buttonRow
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10

                Button {
                    text: "Done"
                    onClicked: {
                        rootStore.i2cStore.i2cRequestForm.visible = false;
                    }
                }
                Button {
                    text: "Clear"
                    onClicked: {
                        rootStore.i2cStore.clearRequest();
                    }
                }
                Button {
                    text: "Delete"
                    onClicked: {
                        rootStore.i2cStore.deleteRequest();
                    }
                }
            }
        }
    }
}

