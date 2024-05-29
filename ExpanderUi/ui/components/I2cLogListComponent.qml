import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Item {
    id: root
    width: logList.width
    height: 60

    Rectangle {
        id: rootRectangle
        anchors.fill: parent
        anchors.leftMargin: 4
        anchors.topMargin: 2
        anchors.bottomMargin: 2
        anchors.rightMargin: 10
        radius: 5
        color: "white"

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 0

            Rectangle {
                id: timeStamp
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                Layout.alignment: Qt.AlignLeft
                color: "lightyellow"
                radius: rootRectangle.radius
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "122m12s122ms"
                }
            }

            Rectangle {
                id: interfaceNum
                Layout.fillHeight: true
                Layout.preferredWidth: 40
                Layout.alignment: Qt.AlignLeft
                color: "lightyellow"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "I2c1"
                }
            }

            Rectangle {
                id: interfaceType
                Layout.fillHeight: true
                Layout.preferredWidth: 40
                Layout.alignment: Qt.AlignLeft
                color: "lightyellow"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "M"
                }
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width - timeStamp.width - interfaceNum.width - interfaceType.width - statusField.width
                Layout.alignment: Qt.AlignLeft
                color: "red"
            }


            Rectangle {
                id: statusField
                Layout.fillHeight: true
                Layout.preferredWidth: 60
                Layout.alignment: Qt.AlignLeft
                color: "lightyellow"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Status"
                }
            }


        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            logList.currentIndex = index;
        }
    }
}
