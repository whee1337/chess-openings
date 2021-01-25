import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2


Item
{
    id: root;
    property string movesetName: "";
    property bool highlighted: false;

    implicitHeight: 25;
    implicitWidth: 70;

    signal customClick();

    MouseArea {
    anchors.fill: root
    onClicked:root.customClick()
   }

    Rectangle
    {
        anchors.fill: root;
        border.width: 1;
        border.color: "black";

        color: root.highlighted ? "grey" : "white";

        Text {
            text: root.movesetName
            color: root.highlighted ? "white" : "black";
            anchors.fill: parent;
        }
    }
}
