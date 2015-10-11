import QtQuick 2.5
import ColonyControl 1.0

Item {

    id: root
    property UiUnitCntr control: UiUnitController.getUnitCntr();

    width: 100;
    height: 100;
    x: control.xPos;
    y: control.yPos;

    z: 3;

    Behavior on x
    {
        id: behavX
        enabled: false
        NumberAnimation {
            //This specifies how long the animation takes
            duration: 125
        }
    }

    Behavior on y
    {
        id: behavY
        enabled: false
        NumberAnimation {
            //This specifies how long the animation takes
            duration: 125
        }
    }

    AnimatedSprite {
        rotation: root.control.direction

        id: sprite
        width: 128
        height: 128
        anchors.centerIn: parent
        z: 2;

        source: parent.control.animMainSrc;
        frameCount: parent.control.animFrameCnt;
        frameWidth: 128
        frameHeight: 128
        frameRate: parent.control.animFrameRate;
        running: parent.control.objIsActive;
        visible: parent.control.objIsvisible;

        onVisibleChanged:
        {
            behavX.enabled = sprite.visible;
            behavY.enabled = sprite.visible;
            behavRotation.enabled = sprite.visible;
        }

        Behavior on rotation
        {
            id: behavRotation
            enabled: false
            NumberAnimation {
                //This specifies how long the animation takes
                duration: 250
            }
        }

    }
}
