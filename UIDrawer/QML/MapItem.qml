import QtQuick 2.3
import ColonyControl 1.0

Rectangle {

    property int mapID: -1;
    property CControl control: MapController.getCCntr();
    property int cellID: control.id;

    width: 100;
    height: 100;
    z: 0;


    Image {
        id: ground;
        source: control.backgroundSrc;
        anchors.fill: parent;
        z: 1;
    }

    Image {
        id: playerMarker;
        source: control.markerSrc;
        anchors.fill: parent;
        z: 1;
    }


    AnimatedSprite {

        property int rowNumber: parent.control.rowInFrame;

        id: sprite
        width: 128
        height: 128
        anchors.centerIn: parent
        z: 3;

        source: parent.control.animMainSrc;
        frameCount: parent.control.animFrameCnt;
        frameWidth: 128
        frameHeight: 128
        frameRate: parent.control.animFrameRate;
        running: parent.control.objIsActive;
        visible: parent.control.objIsvisible;

        onRowNumberChanged:
        {
            frameY = frameHeight * rowNumber;
            restart();
        }

    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onEntered:
        {
            MapController.setFocus(parent.cellID);
        }

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
    }


}
