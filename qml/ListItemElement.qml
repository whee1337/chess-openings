import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2


Item
{
    property int index;
    property string nameElement : "";
    signal customClicked()

    property bool highlighted: false;

    Text {
        anchors.fill: parent

//color: (index == highlightIndex) ? "red" : "blue";
    text: parent.nameElement
    color: "red";
    }

    MouseArea {
         anchors.fill: parent
           onClicked: parent.customClicked();
       }
}
