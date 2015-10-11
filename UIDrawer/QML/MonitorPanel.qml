import QtQuick 2.3

Rectangle {
    id: root
    visible: MonitorPanelCtr.visibility

    border.color: "blue";
    border.width: 1;

    radius: 3

    Item
    {
        id: nuturalRes
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom


        width: (parent.width * 48) / 100


        ResourceCell
        {
            id: fertility
            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.right: parent.right
            anchors.margins: 3;

            height: (parent.height * 48) / 100

            color: root.color;
            opacity: root.opacity

            resNameText: "Fertility"
            resPercent: 100;
            resValText: MonitorPanelCtr.fertility;
        }
        ResourceCell
        {
            id: mineralWealth

            anchors.bottom: parent.bottom;
            anchors.left: parent.left;
            anchors.right: parent.right
            anchors.margins: 3;

            height: (parent.height * 48) / 100

            color: root.color;
            opacity: root.opacity

            resNameText: "MinWealth"
            resPercent: 100;
            resValText: MonitorPanelCtr.mineralWealth;
        }


    }

    Item
    {
        id: products

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom


        width: (parent.width * 48) / 100;


        //res 1
        ResourceCell
        {
            id: res1
            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.right: parent.right
            anchors.margins: 3;

            height: (parent.height * 23) / 100

            color: root.color;
            opacity: root.opacity

            resNameText: MonitorPanelCtr.res1Name
            resPercent: MonitorPanelCtr.res1Percent;
            resValText: MonitorPanelCtr.res1Value;
        }

        //res 2
        ResourceCell
        {
            id: res2
            anchors.top: res1.bottom;
            anchors.left: parent.left;
            anchors.right: parent.right
            anchors.margins: 3;

            height: (parent.height * 23) / 100

            color: root.color;
            opacity: root.opacity

            resNameText: MonitorPanelCtr.res2Name
            resPercent: MonitorPanelCtr.res2Percent;
            resValText: MonitorPanelCtr.res2Value;
        }

        //res 3
        ResourceCell
        {
            id: res3
            anchors.top: res2.bottom;
            anchors.left: parent.left;
            anchors.right: parent.right
            anchors.margins: 3;

            height: (parent.height * 23) / 100

            color: root.color;
            opacity: root.opacity

            resNameText: MonitorPanelCtr.res3Name
            resPercent: MonitorPanelCtr.res3Percent;
            resValText: MonitorPanelCtr.res3Value;
        }

        //res 4
        ResourceCell
        {
            id: res4
            anchors.top: res3.bottom;
            anchors.left: parent.left;
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 3;

            color: root.color;
            opacity: root.opacity

            resNameText: MonitorPanelCtr.res4Name
            resPercent: MonitorPanelCtr.res4Percent;
            resValText: MonitorPanelCtr.res4Value;
        }

    }
}

