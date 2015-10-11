import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle
{
    id: root
    property alias resNameText: resName.text
    property int resValText: 0
//    property alias resValText: resValueTxt.text


    radius: 10
    smooth: true

    border.color: "black"
    border.width: 1

    // Name of resources/property
    Rectangle
    {
        color: parent.color;
        opacity: parent.opacity

        height: parent.height
        width: (parent.width - parent.radius) / 2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.leftMargin: parent.border.width + parent.radius
        anchors.bottomMargin: parent.border.width + parent.radius
        anchors.topMargin: parent.border.width + parent.radius

        Label
        {
            id: resName
            anchors.centerIn: parent

            horizontalAlignment: Text.AlignVCenter;
            verticalAlignment: Text.AlignHCenter;
        }

    }

    // Value of resources/property
    Rectangle
    {
        color: parent.color;
        opacity: parent.opacity

        height: parent.height
        width: (parent.width - parent.radius) / 2

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.rightMargin: parent.border.width + parent.radius / 2
        anchors.bottomMargin: parent.border.width + parent.radius / 2
        anchors.topMargin: parent.border.width + parent.radius / 2

        Label
        {
            id: resValueTxt
            anchors.centerIn: parent

            horizontalAlignment: Text.AlignVCenter;
            verticalAlignment: Text.AlignHCenter;
            text: "0";
        }


    }

    onResValTextChanged:
    {
        if(root.resValText > 1000000)
        {
            resValueTxt.text = (root.resValText / 1000000).toFixed(3).toString() + " M";
        }
        else if(root.resValText > 100000)
        {
            resValueTxt.text = (root.resValText / 1000).toFixed(1).toString() + " K";
        }
        else
        {
            resValueTxt.text = root.resValText.toString();
        }
    }
}
