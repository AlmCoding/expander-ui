import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
    id: root
    width: requestList.width
    height: 60

    MouseArea {
        id: dragArea
        anchors.fill: parent

        property bool held: false
        drag.target: held ? contentRectangle : undefined
        drag.axis: Drag.YAxis

        onPressed: function() {
            console.log("onPressed: " + model.index);
            rootStore.i2cStore.i2cRequestModel.selectedRequestIdx = model.index;
            rootStore.i2cStore.i2cRequestForm.visible = false;
        }
        onPressAndHold: function() {
            held = true;
        }
        onReleased: function() {
            held = false;
        }

        DropArea {
            anchors {
                fill: parent
                margins: 10
            }

            onEntered: function(drag) {
                console.log("move item: " + drag.source.DelegateModel.itemsIndex + " -> " + dragArea.DelegateModel.itemsIndex);
                visualModel.items.move(drag.source.DelegateModel.itemsIndex, dragArea.DelegateModel.itemsIndex);
                // model.moveItNow(drag.source.DelegateModel.itemsIndex, dragArea.DelegateModel.itemsIndex);
            }
        }


        Rectangle {
            id: contentRectangle

            Drag.active: dragArea.held
            Drag.source: dragArea
            Drag.hotSpot.x: width / 2
            Drag.hotSpot.y: height / 2

            anchors {
                fill: dragArea.held ? undefined : parent
                leftMargin: 4
                topMargin: 2
                bottomMargin: 2
                rightMargin: 10
            }
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
                                radius: contentRectangle.radius
                                color: "lightgray"
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    leftPadding: 5
                                    text: "<b>" + model.name + "</b>"
                                }
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: function() {
                                        rootStore.i2cStore.i2cRequestModel.selectedRequestIdx = index;
                                        rootStore.i2cStore.i2cRequestForm.visible = true;
                                    }
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
                                    text: (model.type === "MR") ? ("<b>Slave:</b> " + model.slaveAddr) : ""
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
                                    text: "<b>Write:</b> " + model.writeData
                                    // text: ((model.type === "MR") ? "<b>Write:</b> " : "<b>Write:</b> ") + model.writeData
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
                }

                Rectangle {
                    id: sendButton
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.height
                    radius: contentRectangle.radius
                    color: "white"

                    Image {
                        id: playImage
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        anchors.margins: 4
                        source: "/ExpanderUi/ui/resources/images/play_square_100.png"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: function() {
                            rootStore.i2cStore.i2cRequestModel.selectedRequestIdx = index;
                            rootStore.sendI2cRequest();
                        }
                    }
                }
            }
        }
    }
}
