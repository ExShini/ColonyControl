import QtQuick 2.3
import ColonyControl 1.0
import "qrc:/res/UIDrawer/QML/Styles"

Item
{
    id: root

    property AbilityCntr control: AbilityMenuCntr.getAbilityCntr();
    property int cellWidth: 50

    width: 300
    height: root.cellWidth * 3

    Rectangle
    {
        id: mainPanel
        width: root.cellWidth
        height: root.cellWidth

        anchors.right: parent.right
        anchors.top: parent.top

        radius: 3
        border.color: "#1A237E"
        border.width: 3


        color: Styles.humanWindows.windowColor;
        opacity: Styles.humanWindows.windowOpacity;

        Image {
            id: icon
            source: root.control.src;

            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            anchors.margins: 2

            width: height
        }

        SimpleResourceCell
        {
            id: resCell
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            width: root.cellWidth * 4
            color: parent.color
            opacity: 0

            resNameText: "Res: "
            resValText: root.control.cost;

            Behavior on opacity
            {
                id: cellBehavOpacity
                enabled: true
                NumberAnimation {
                    // This specifies how long the animation takes
                    duration: 250
                }
            }
        }

        MouseArea
        {
            anchors.fill: parent
            hoverEnabled: true
            onEntered:
            {
                mainPanel.width = root.cellWidth * 5;
                description.opacity = Styles.humanWindows.windowOpacity;
                resCell.opacity = Styles.humanWindows.windowOpacity;
            }
            onExited:
            {
                mainPanel.width = root.cellWidth;
                description.opacity = 0;
                resCell.opacity = 0;
            }

            onReleased:
            {
                control.wasPressed();
            }
        }


        Behavior on width
        {
            id: behavWidth
            enabled: true
            NumberAnimation {
                // This specifies how long the animation takes
                duration: 250
            }
        }
    }

    Rectangle
    {
        id: description
        anchors.left: mainPanel.left
        anchors.top: mainPanel.bottom
        radius: 3

        border.color: "#1A237E"
        border.width: 1

        width: root.cellWidth * 4
        height: root.cellWidth * 2

        color: Styles.humanWindows.windowColor;
        opacity: 0

        Behavior on opacity
        {
            id: behavOpacity
            enabled: true
            NumberAnimation {
                // This specifies how long the animation takes
                duration: 250
            }
        }
    }
}
