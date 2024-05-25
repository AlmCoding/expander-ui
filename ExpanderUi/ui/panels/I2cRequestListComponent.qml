import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material


Item {
    id: root
    width: requestList.width
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

            ColumnLayout {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width - sendButton.width
                spacing: 0

                RowLayout {
                    id: firstRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 2
                    spacing: 0

                    Rectangle {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 140
                        Layout.margins: 3
                        radius: 5
                        color: "lightgray"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            leftPadding: 5
                            text: "<b>" + model.name + "</b>"
                        }
                    }
                    Rectangle {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 30
                        // color: "red"
                        Text {
                            anchors.centerIn: parent
                            text: "<b>" + model.rw + "</b>"
                        }
                    }
                    Rectangle {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        // color: "blue"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: "<b>Slave:</b> " + model.slaveAddr
                        }
                    }
                }

                RowLayout {
                    id: secondRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 2
                    spacing: 0

                    Rectangle {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 80
                        radius: 5
                        // color: "red"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            leftPadding: 8
                            text: "<b>Addr:</b> " + model.memAddr
                        }
                    }
                    Rectangle {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 95
                        // color: "red"
                    }
                    Rectangle {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        // color: "blue"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: "<b>Size:</b> " + model.size
                        }
                    }
                }
            }

            Rectangle {
                id: sendButton
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.height
                radius: rootRectangle.radius
                color: "white"

                Image {
                    id: playImage
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    anchors.margins: 4
                    source: "/ExpanderUi/ui/resources/images/play_button.png"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: { print("onClicked state: "+state) }
                    }
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            requestList.currentIndex = index
        }
    }
}
