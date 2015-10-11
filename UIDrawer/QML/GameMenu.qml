import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import ColonyControl 1.0

Rectangle
{
    id: root

    property bool gameIsStarted: false
    anchors.centerIn: parent;

    z: 5
    width: (parent.width * 50) / 100;
    height: (parent.height * 70) / 100;
    color: "#1A237E";

    radius: 6
    border.width: 3
    border.color: "#1565C0"

    Button
    {
        //start new game
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.margins: (parent.height * 10) / 100;
        width: (parent.width * 50) / 100;
        height: (parent.height * 15) / 100;


        style: ButtonStyle
        {
            background: Rectangle
            {
                implicitWidth: parent.width
                implicitHeight: parent.height
                border.width: control.activeFocus ? 3 : 2
                border.color: "#1E88E5"
                radius: 4
                gradient: Gradient
                {
                    GradientStop { position: 1 ; color: control.pressed ? "#283593" : "#1A237E" }
                    GradientStop { position: 0 ; color: control.pressed ? "#283593" : "#1A237E" }
                }
            }

            label: Text {
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Helvetica"
                    font.pointSize: 16
                    color: "#1E88E5"
                    text: "Start new Game!"
                  }
            }

        onClicked:
        {
            MenuController.startGame();

            root.gameIsStarted = true;
            root.visible = false;
        }

    }

    Button
    {
        //exit
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        anchors.margins: (parent.height * 10) / 100;
        width: (parent.width * 50) / 100;
        height: (parent.height * 15) / 100;


        style: ButtonStyle
        {
            background: Rectangle
            {
                implicitWidth: parent.width
                implicitHeight: parent.height
                border.width: control.activeFocus ? 3 : 2
                border.color: "#1E88E5"
                radius: 4
                gradient: Gradient
                {
                    GradientStop { position: 1 ; color: control.pressed ? "#283593" : "#1A237E" }
                    GradientStop { position: 0 ; color: control.pressed ? "#283593" : "#1A237E" }
                }
            }

        label: Text {
                renderType: Text.NativeRendering
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.family: "Helvetica"
                font.pointSize: 16
                color: "#1E88E5"
                text: "Exit"
              }
        }

        onClicked:
        {
            Qt.quit();
        }

    }
}
