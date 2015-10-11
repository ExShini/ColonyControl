import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle
{
    id: root
    property alias resNameText: resName.text
    property alias resPercent: progBar.value
    property alias resValText: resValueTxt.text


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


        ProgressBar {
            id: progBar
            anchors.fill: parent

            minimumValue: 0
            maximumValue: 100;

            style: ProgressBarStyle {

                background: Rectangle {
                    radius: 10
                    color: "lightgray"
                    border.color: "gray"
                    border.width: 1
                    implicitWidth : parent.width;
                    implicitHeight: parent.height;
                }

                progress: Rectangle {
                    radius: 10
                    color: "lightsteelblue"
                    border.color: "steelblue"
                }
            }


            Label
            {
                id: resValueTxt
                anchors.centerIn: parent
                text: root.resValue.toString();

                horizontalAlignment: Text.AlignVCenter;
                verticalAlignment: Text.AlignHCenter;
            }
        }



    }
}
