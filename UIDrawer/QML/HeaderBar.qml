import QtQuick 2.0
import "qrc:/res/UIDrawer/QML/Styles"

Rectangle {

    border.color: "blue";
    border.width: 1;
    radius: 3

    anchors.horizontalCenter: parent.horizontalCenter;
    anchors.top: parent.top;

    width: (parent.width * 60) / 100;
    height: (parent.height * 5) / 100;
    z:1

    color: Styles.humanWindows.windowColor;
    opacity: Styles.humanWindows.windowOpacity;

    visible: MonitorPanelCtr.visibility
}

