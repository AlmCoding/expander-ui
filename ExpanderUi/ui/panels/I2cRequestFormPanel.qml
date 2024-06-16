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

