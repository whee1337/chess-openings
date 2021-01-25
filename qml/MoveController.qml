import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2


Item
{
    id: root;
    property bool showRight: false;
    property bool itemVisibility: false;

    implicitHeight: 25;
    implicitWidth: 70;

    onItemVisibilityChanged: {
        timer.running = true;
    }

    RowLayout
    {

    Rectangle {
         id:circle
         width: 10
         height: width
         color: showRight ? "green" : "red";
         border.color: "black"
         border.width: 1
         radius: width*0.5
         visible: root.itemVisibility;
         anchors.verticalCenter: parent.verticalCenter;
    }

    Text {
        id: test
        color: showRight ? "green" : "red";
        text: showRight ? "Richtiger Zug" : "Falscher Zug";
        visible: root.itemVisibility;
    }
 }

    Timer {
        id: timer
        interval: 3000
        running: false
        repeat: false
        onTriggered:{
             root.itemVisibility = false;
        }
    }
}
