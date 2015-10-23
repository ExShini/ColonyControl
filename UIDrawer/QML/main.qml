import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.0
import "qrc:/res/UIDrawer/QML/Styles"

ApplicationWindow {

    //visibility: Window.FullScreen;
    visible: true
    width: (Screen.desktopAvailableWidth * 80) / 100;
    height: (Screen.desktopAvailableHeight * 80) / 100;
    title: qsTr("Colony Control " + MenuController.getCCVersion())
    objectName: "MainWindow";

    // key handler
    Item {
        anchors.fill: parent
        focus: true

        Keys.onPressed:
        {
            if(event.key === Qt.Key_Escape)
            {
                if((menuWindow.visible === true) && (menuWindow.gameIsStarted === true))
                {
                    menuWindow.visible = false;
                }
                else if(researchMenu.visible === true)
                {
                    researchMenu.visible = false;
                }
                else
                {
                    menuWindow.visible = true;
                }
            }
        }
    }


    GameMenu
    {
        id: menuWindow
    }

    ResearchMenu
    {
        id: researchMenu
    }


    HeaderBar
    {
        id: headerBar

        GlobalResBar
        {
            id: globResBar
            anchors.centerIn: parent
            width: (parent.width * 60) / 100
        }

        Rectangle
        {
            id: researchButton
            height: (parent.height * 80) / 100;
            width: 2 * height;

            anchors.verticalCenter: parent.verticalCenter
            anchors.left: globResBar.right
            anchors.leftMargin: 5

            color: Styles.humanWindows.windowColor;
            opacity: Styles.humanWindows.windowOpacity;

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    if(researchMenu.visible === true)
                    {
                        researchMenu.visible = false;
                    }
                    else
                    {
                        researchMenu.visible = true;
                    }
                }
            }
        }

    }

    Flickable {
        id: mapArea
        z:0
        width: (parent.width * 80) / 100;
        anchors.fill: parent

        objectName: "mapArea";
        boundsBehavior: Flickable.StopAtBounds;
    }

    BuildPanel
    {
        objectName: "buildPanel";
        width: 300
        height: 300

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
    }

    MonitorPanel
    {
        z:1
        anchors.horizontalCenter: parent.horizontalCenter;


        width: (parent.width * 50) / 100;
        height: (parent.height * 20) / 100;             // 15%
        anchors.bottom: parent.bottom;

        color: Styles.humanWindows.windowColor;
        opacity: Styles.humanWindows.windowOpacity;
    }


    MediaPlayer {
        id: playMusic
        source: AudioController.getNextTrack();
        autoPlay: true
        volume: 0.5

        onStopped:
        {
            playMusic.source = AudioController.getNextTrack();
            playMusic.play();
        }
    }

}
