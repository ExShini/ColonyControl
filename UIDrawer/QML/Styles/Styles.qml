import QtQuick 2.0
pragma Singleton

QtObject {
    property QtObject humanWindows: QtObject
    {
        readonly property color windowColor: "#1E88E5";
        readonly property real windowOpacity: 0.8
    }
}
