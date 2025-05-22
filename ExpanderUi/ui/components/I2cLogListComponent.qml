import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
    id: root
    width: logList.width
    height: 120

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
                Layout.preferredWidth: 120 // secondRow.width
                spacing: 0

                RowLayout {
                    id: firstRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 4
                    spacing: 0

                    Rectangle {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.margins: 3
                        radius: rootRectangle.radius
                        color: "lightgray"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            leftPadding: 5
                            text: "<b>" + model.name + "</b>"
                        }
                    }
                }

                RowLayout {
                    id: secondRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 4
                    spacing: 0

                    Rectangle {
                        id: interfaceNum
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        //Layout.preferredWidth: 40
                        //Layout.alignment: Qt.AlignLeft
                        Layout.margins: 3
                        radius: rootRectangle.radius
                        color: (model.interface === "I2c0") ? constants.i2c0Color : constants.i2c1Color
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: (model.interface === "I2c0") ? "<b>I2c1</b>" :  "<b>I2c2</b>"
                        }
                    }

                    Rectangle {
                        id: logType
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        //Layout.preferredWidth: 40
                        //Layout.alignment: Qt.AlignLeft
                        Layout.margins: 3
                        radius: rootRectangle.radius
                        color: (model.type === "MR") ? constants.masterColor : constants.slaveColor
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "<b>" + model.type + "</b>"
                        }
                    }
                }

                RowLayout {
                    id: thirdRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 4
                    spacing: 0

                    Rectangle {
                        id: slaveAddr
                        Layout.fillHeight: true
                        Layout.preferredWidth: 80
                        Layout.alignment: Qt.AlignLeft
                        Layout.margins: 3
                        color: "white"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            leftPadding: 5
                            text: (model.type === "MR") ? ("<b>Slave:</b> " + model.slaveAddr) : ""
                        }
                    }

                }

                RowLayout {
                    id: fourthRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 4
                    spacing: 0

                    Rectangle {
                        id: timeStamp
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        //Layout.preferredWidth: 140
                        Layout.alignment: Qt.AlignLeft
                        Layout.margins: 3
                        radius: rootRectangle.radius
                        color: "white"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            leftPadding: 5
                            text: model.time
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
                    Layout.preferredHeight: parent.height / 4
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
                    id: writeRowAscii
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 4
                    spacing: 0

                    Rectangle {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "white"

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: "<b>Write (" + writeSize + "):</b> " + model.writeDataAscii
                        }
                    }
                }

                RowLayout {
                    id: readRow
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 4
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

                RowLayout {
                    id: readRowAscii
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height / 4
                    spacing: 0

                    Rectangle {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "white"

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: "<b>Read (" + readSize + "):</b> " + model.readDataAscii
                        }
                    }
                }
            }

            Rectangle {
                id: statusField
                Layout.fillHeight: true
                Layout.preferredWidth: 90
                Layout.alignment: Qt.AlignLeft
                radius: rootRectangle.radius
                color: (model.status === "Success") ? constants.statusFieldSuccess : constants.statusFieldWarning
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
