import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle
{
    anchors.centerIn: parent;
    visible: false;

    z: 5
    width: (parent.width * 50) / 100;
    height: (parent.height * 70) / 100;
    color: "#1A237E";

    radius: 6
    border.width: 3
    border.color: "#1565C0"

    Label
    {
        anchors.centerIn: parent
        text: "Sciense will be here :)"
    }
}
