import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    id: draggedIntro
    width: 2500;
    height: 1600
    color: "#e20d0d"
    property real scaleValue: 1.0

    property int areaWidth: 600
    property int areaHeight: 200


    transform: Scale {
        id: locScale
        origin.x: 0
        origin.y: 0
        xScale: scaleValue;
        yScale: scaleValue;
    }

    onAreaHeightChanged:
    {
        scaleValue = 1.0;
    }

    onAreaWidthChanged:
    {
        scaleValue = 1.0;
    }
}
