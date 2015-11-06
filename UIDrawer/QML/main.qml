import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.0
import "qrc:/res/UIDrawer/QML/Styles"

ApplicationWindow {

//    visibility: Window.FullScreen;
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

    Item
    {
        id: mapContainer
        objectName: "mapContainer";
        anchors.fill: parent
        z:0

        MapField
        {
            id: dragged
            areaWidth: parent.width
            areaHeight: parent.height

            objectName: "mapArea";

            onAreaWidthChanged:
            {
                dragMouseArea.drag.minimumX = dragged.areaWidth - dragged.width;
                dragMouseArea.drag.maximumX = 0;

                if(dragged.x < dragMouseArea.minimumX)
                {
                    dragged.x = dragMouseArea.minimumX
                }
                else if(dragged.x > 0)
                {
                    dragged.x = 0
                }
            }

            onAreaHeightChanged:
            {
                dragMouseArea.drag.minimumY = dragged.areaHeight - dragged.height;
                dragMouseArea.drag.maximumY = 0;

                if(dragged.y < dragMouseArea.minimumY)
                {
                    dragged.y = dragMouseArea.minimumY
                }
                else if(dragged.y > 0)
                {
                    dragged.y = 0
                }
            }
        }

        MouseArea
        {
            id: dragMouseArea;
            //acceptedButtons: Qt.LeftButton | Qt.RightButton
            anchors.fill: mapContainer;
            drag.target: dragged;
            drag.axis: Drag.XAndYAxis;
            drag.minimumX: dragged.areaWidth - dragged.width;
            drag.maximumX: 0;

            drag.minimumY: dragged.areaHeight - dragged.height;
            drag.maximumY: 0;

            onReleased:
            {
                if(mouse.button === Qt.LeftButton)
                {
                    AbilityMenuCntr.sectorChoosed();
                    console.log("left button");
                }
                else
                {
                    AbilityMenuCntr.resetMarker();
                    console.log("right button");
                }
            }

            onWheel:
            {
                var oldScaling = dragged.scaleValue;
                if (wheel.angleDelta.y > 0)
                {
                    if(dragged.scaleValue < 2)
                    {
                        dragged.scaleValue += 0.1;
                    }
                }
                else
                {
                    if(dragged.scaleValue > 0.8)
                    {
                        dragged.scaleValue -= 0.1;
                    }
                }

                // calculate new X and Y position
                // calculate real x and y coordinate
                var rx = (dragged.x / oldScaling);
                var ry = (dragged.y / oldScaling);

                // calculate old real width and height coordinate
                var wrOld = dragged.areaWidth / oldScaling;
                var hrOld = dragged.areaWidth / oldScaling;

                // calculate new real width and height coordinate
                var wrNew = dragged.areaWidth / dragged.scaleValue;
                var hrNew = dragged.areaWidth / dragged.scaleValue;

                var shiftX = (wrOld - wrNew) / 2;
                var shiftY = (hrOld - hrNew) / 2;

                dragged.x = (rx - shiftX) * dragged.scaleValue;
                dragged.y = (ry - shiftY) * dragged.scaleValue;


                // calculate new borders for dragging
                drag.minimumX = dragged.areaWidth - (dragged.width * dragged.scaleValue);
                drag.minimumY = dragged.areaHeight - (dragged.height * dragged.scaleValue);

                if(dragged.x < drag.minimumX)
                {
                    dragged.x = drag.minimumX
                }
                else if(dragged.x > 0)
                {
                    dragged.x = 0
                }

                if(dragged.y < drag.minimumY)
                {
                    dragged.y = drag.minimumY
                }
                else if(dragged.y > 0)
                {
                    dragged.y = 0
                }
            }
        }
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
