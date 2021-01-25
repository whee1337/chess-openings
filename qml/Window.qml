import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import com.znocpmp.chess 1.0

ApplicationWindow {
    title: "Title"
    width: 640
    height: 480
    visible: true

    ColumnLayout {
        id: columnLayout1
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

      //  state: "init"

        RowLayout {
            id: rowLayout1
            x: 311
            y: 56
            width: 100
            height: 100
            Layout.fillHeight: true
            Layout.fillWidth: true

            Button {
                id: button1
                x: 145
                y: 93
                text: "Start"
                onClicked: {
                    if(debug) {
                        console.debug("Setup board figures ")
                    }
                    GameEngine.setupBoard()
                    columnLayout1.state = "game"
                }
            }

            RowLayout {
                RadioButton {
                    checked: true
                    text: qsTr("Playing as White")
                    onCheckedChanged: GameEngine.setPlayingAsWhite(checked);
                }
            }

            MoveController
            {
                id: turnShower;
                width: 100;
                height: 100;
                anchors.right:columnLayout1.right;
            }

            Connections {
            target: GameEngine
                onTurnDone: {
                    console.log("connction to game engine: " + value);

                 turnShower.itemVisibility=true;
                 turnShower.showRight = value;
                }
            }
        }

        RowLayout {
            id: rowLayout2
//            x: 333
//            y: 222
//              width: 100
//              height: parent.height;
            Layout.fillHeight: true
            Layout.fillWidth: true

            Board {
                id: board1
                implicitHeight: 100;
                implicitWidth: 100;
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.column: 0;
                onFigureClicked: GameEngine.itemClicked(x, y)
            }

            ListView {
                id:list
                Layout.fillHeight: true
                Layout.fillWidth: true
                implicitWidth: 40;
                anchors.left: board1.right;
                anchors.right: parent.right;

                model: DemoModel
                Component.onCompleted:{
                        DemoModel.onClickedModel(currentIndex);
                }

                delegate: ListItemMoveset{
                    movesetName: name;
                    highlighted: list.currentIndex == index ? true : false;
                    width: list.width;

                    onCustomClick: {
                        list.currentIndex = index;
                        DemoModel.onClickedModel(index)
                    }
                }



     /*               Text {
                    property int indexOfThisDelegate: index
                     text: name
                     MouseArea {
                     anchors.fill: parent
                      onClicked: DemoModel.onClickedModel(index)
                    }
                 }*/




            }
        }

        Component.onCompleted: {
             if(debug) {
                 console.debug("Loaded")
             }
             board1.figures = GameEngine.figures()
             //history1.model = GameEngine.history()
         }
    }
}

/*


        states: [
            State {
                name: "init"
                PropertyChanges {
                    target: button1

                    text: "Start"
                    onClicked: {
                        if(debug) {
                            console.debug("Setup board figures ")
                        }
                        GameEngine.setupBoard()
                        columnLayout1.state = "game"
                    }
                }
            }
        ]

                PropertyChanges {
                    target: button2
                    text: "Load"

                    onClicked: {
                        if(debug) {
                            console.debug("Clicked load button")
                        }
                        dialog.visible = true
                    }
                }
            },
            State {
                name: "game"

                PropertyChanges {
                    target: button1

                    text: "Stop"
                    onClicked: {
                        if(debug) {
                            console.debug("Stop game")
                        }
                        GameEngine.clean()
                        columnLayout1.state = "init"
                    }
                }
                PropertyChanges {
                    target: button2
                    text: "Save"

                    onClicked: {
                        if(debug) {
                            console.debug("save button")
                        }
                        GameEngine.save("")
                        saveDialog.visible = true
                    }
                }
                PropertyChanges {
                    target: button3
                    enabled: false
                }
                PropertyChanges {
                    target: button4
                    enabled: false
                }
            },
            State {
                name: "watch"
                PropertyChanges {
                    target: button3
                    enabled: true
                }
                PropertyChanges {
                    target: button4
                    enabled: true
                }
            }


            Button {
                id: button2
                x: 243
                y: 93

               GameFDialog {
                   id: dialog
               }

               GameFDialog {
                   id: saveDialog
                   title: "Save as"
               }
            }

            Button {
                id: button3
                text: "prev"
                enabled: false
            }

            Button {
                id: button4
                text: "next"
                enabled: false
            }

            Button {
                id: button5
                text: "exit"
                onClicked: Qt.quit()
            }*/
