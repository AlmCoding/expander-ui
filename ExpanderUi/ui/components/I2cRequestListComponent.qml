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

            Item {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.width - sendButton.width

                ColumnLayout {
                    anchors.fill: parent
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
                            radius: rootRectangle.radius
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
                                text: "<b>" + model.type + "</b>"
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
                            Layout.preferredWidth: 176 // 80
                            radius: 5
                            // color: "red"
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                leftPadding: 8
                                text: ((model.type === "MA") ? "<b>Write:</b> " : "<b>Addr:</b> ") + model.writeData
                            }
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

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        rootStore.i2cStore.i2cRequestModel.selectedRequestIdx = index;
                        rootStore.i2cStore.i2cRequestForm.visible = true;
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
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        rootStore.i2cStore.i2cRequestModel.selectedRequestIdx = index;
                        rootStore.sendI2cRequest();
                    }
                }
            }
        }
    }
}
