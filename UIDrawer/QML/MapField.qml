import QtQuick 2.3
import QtQuick.Controls 1.2

Flickable {
    id: root
    boundsBehavior: Flickable.StopAtBounds;

    MouseArea
    {
        anchors.fill: parent

        onWheel:
        {
            // stub
        }
    }
}
