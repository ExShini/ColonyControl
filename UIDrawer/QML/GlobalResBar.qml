import QtQuick 2.3

Rectangle {
    id: root

    border.color: "white";
    border.width: 1;

    radius: 3

    SimpleResourceCell
    {
        id: mainResCell
        anchors.top: parent.top;
        anchors.bottom: parent.bottom
        anchors.left: parent.left;
        width: (parent.width * 45) / 100
        anchors.margins: 3;


        color: root.color;
        opacity: root.opacity

        resNameText: MonitorPanelCtr.mainResName
        resValText: MonitorPanelCtr.mainResValue;
    }

    SimpleResourceCell
    {
        id: scinseResCell
        anchors.top: parent.top;
        anchors.bottom: parent.bottom
        anchors.right: parent.right;
        width: (parent.width * 45) / 100
        anchors.margins: 3;

        color: root.color;
        opacity: root.opacity

        resNameText: MonitorPanelCtr.scienseName
        resValText: MonitorPanelCtr.scienseValue;
    }
}

