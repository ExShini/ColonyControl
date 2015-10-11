import QtQuick 2.0
import ColonyControl 1.0

Item
{
    width: 100;
    height: 100;

    z: 3

    property MarkerCntr control: MapController.getMarkerContr();
    property string abilityMarkerSrc: control.abilityMarker;

    x: control.X;
    y: control.Y;
    visible: control.visible;

    Image {
        id: marker
        anchors.fill: parent


        source: control.src;
    }


    Image {
        id: abilityMarker
        anchors.fill: parent

        source: "";
        visible: false;
    }

    onAbilityMarkerSrcChanged:
    {
        if(abilityMarkerSrc === "")
        {
            abilityMarker.visible = false;
        }
        else
        {
            abilityMarker.visible = true;
            abilityMarker.source = abilityMarkerSrc;
        }
    }
}
