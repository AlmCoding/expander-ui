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
            spacing: 0

            ColumnLayout {
                id: firstColumn
                Layout.fillHeight: true
                Layout.preferredWidth: secondRow.width
                spacing: 0

                RowLayout {
                    id: firstRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 2
                    spacing: 0

                    Rectangle {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 140 - 6
                        Layout.margins: 3
                        radius: rootRectangle.radius
                        color: "lightgray"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            leftPadding: 5
                            text: "<b>" + model.name + "</b>"
                        }
                    }

                    Rectangle {
                        id: interfaceNum
                        Layout.fillHeight: true
                        Layout.preferredWidth: 40 - 6
                        Layout.alignment: Qt.AlignLeft
                        Layout.margins: 3
                        radius: rootRectangle.radius
                        color: "lightblue"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "<b>" + model.interface + "</b>"
                        }
                    }

                    Rectangle {
                        id: logType
                        Layout.fillHeight: true
                        Layout.preferredWidth: 40 - 6
                        Layout.alignment: Qt.AlignLeft
                        Layout.margins: 3
                        radius: rootRectangle.radius
                        color: "lightyellow"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: model.type
                        }
                    }
                }

                RowLayout {
                    id: secondRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 2
                    spacing: 0

                    Rectangle {
                        id: timeStamp
                        Layout.fillHeight: true
                        Layout.preferredWidth: 140
                        Layout.alignment: Qt.AlignLeft
                        color: "white"
                        radius: rootRectangle.radius
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            leftPadding: 5
                            text: model.time
                        }
                    }

                    Rectangle {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 80
                        color: "white"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            // text: "<b>Slave:</b> " + model.slaveAddr
                            text: (model.type === "MR") ? ("<b>Slave:</b> " + model.slaveAddr) : ""
                        }
                    }
                }
            }

            Rectangle {
                id: sepRectangle
                Layout.fillHeight: true
                Layout.preferredWidth: 5
                color: "lightgray"
            }

            ColumnLayout {
                id: dataColumn
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width - firstColumn.width - sepRectangle.width - statusField.width
                Layout.alignment: Qt.AlignLeft
                Layout.leftMargin: 5
                spacing: 0

                RowLayout {
                    id: writeRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 2
                    spacing: 0

                    Rectangle {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "white"

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: "<b>Write (" + writeSize + "):</b> " + model.writeData
                        }
                    }
                }

                RowLayout {
                    id: readRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 2
                    spacing: 0

                    Rectangle {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "white"

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: "<b>Read (" + readSize + "):</b> " + model.readData
                        }
                    }
                }
            }

            Rectangle {
                id: statusField
                Layout.fillHeight: true
                Layout.preferredWidth: 60
                Layout.alignment: Qt.AlignLeft
                radius: rootRectangle.radius
                color: "lightyellow"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: model.status
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
