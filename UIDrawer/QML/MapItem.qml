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
        rotation: control.backgroundDir;
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
        id: sprite

        property int rowNumber: parent.control.rowInFrame;
        property bool infinityLoops: parent.control.infinityLoop;
        property string animSrc: parent.control.animMainSrc;
        property int animFrameCnt: parent.control.animFrameCnt;
        property int animFrameRate: parent.control.animFrameRate;


        width: 128
        height: 128
        anchors.centerIn: parent
        z: 3;

        source: "";
        frameCount: 8;
        frameWidth: 128
        frameHeight: 128
        frameRate: 4;
        running: parent.control.objIsvisible;
        visible: parent.control.objIsvisible;

        Connections
        {
            target: control
            onApplyChanges:
            {
                sprite.source = sprite.animSrc;
                if(sprite.infinityLoops)
                {
                    sprite.frameCount = sprite.animFrameCnt;
                }
                else
                {
                    sprite.frameCount = sprite.animFrameCnt + 2;
                }

                sprite.frameRate = sprite.animFrameRate;

                sprite.frameX = 0;
                sprite.frameY = sprite.frameHeight * sprite.rowNumber;

                sprite.start();
            }
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
    }


}
