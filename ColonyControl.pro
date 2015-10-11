TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    UIDrawer/uidrawer.cpp \
    UIDrawer/UIElements/uimapcontroller.cpp \
    gameapp.cpp \
    Core/gamecore.cpp \
    UIDrawer/UIElements/cellcontroller.cpp \
    Core/objectcontroller.cpp \
    UIDrawer/UIElements/menucontroller.cpp \
    Core/gobject.cpp \
    Core/gobjwrapper.cpp \
    Core/smcont.cpp \
    Core/buildings/building.cpp \
    Core/buildings/human/humsettlers.cpp \
    UIDrawer/UIElements/uiresdictionary.cpp \
    Core/buildings/sector.cpp \
    Core/mapgenerator.cpp \
    Core/randomgen.cpp \
    UIDrawer/UIElements/monitorpanelcontroller.cpp \
    UIDrawer/UIElements/markercontroller.cpp \
    Core/playercontroller.cpp \
    Core/player/player.cpp \
    Core/player/humanplayer.cpp \
    Core/player/requestmanager.cpp \
    Core/UnitController/unitcontroller.cpp \
    Core/UnitController/Units/unit.cpp \
    Core/UnitController/unitwrapper.cpp \
    UIDrawer/UIElements/uiunitcontroller.cpp \
    UIDrawer/UIElements/uiunitcntr.cpp \
    Core/UnitController/Units/Human/humshuttle.cpp \
    Core/buildings/human/humcolonycenter.cpp \
    Core/UnitController/Units/unitfactory.cpp \
    Core/UnitController/Units/Human/humanunitfactory.cpp \
    Core/SubComponents/emptysectorradar.cpp \
    Core/player/buildmanager.cpp \
    UIDrawer/UIElements/abilitybuttoncntr.cpp \
    UIDrawer/UIElements/abilitymenucontroller.cpp \
    Core/buildings/buildingfactory.cpp \
    Core/buildings/human/humanbuildingfactory.cpp \
    Core/player/Human/humanbuildmanager.cpp \
    Core/buildings/human/humtransportcenter.cpp \
    TestModule/testmanager.cpp \
    TestModule/requestmanagertest.cpp \
    Core/player/abilitymanager.cpp \
    Core/player/Human/humanabilitymanager.cpp \
    Core/player/abilityexecutor.cpp \
    Core/player/Human/Abilities/ioncanonsatellite.cpp \
    Core/UnitController/Units/bullet.cpp \
    Core/player/Human/Abilities/ioncanonbullet.cpp \
    Core/objectstatecontroller.cpp \
    AudioModule/audiocontroller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    UIDrawer/uidrawer.h \
    UIDrawer/UIElements/uimapcontroller.h \
    gameapp.h \
    Enums/mapsettings.h \
    Core/gamecore.h \
    UIDrawer/UIElements/cellcontroller.h \
    Core/objectcontroller.h \
    Enums/coresettings.h \
    Enums/guisettings.h \
    UIDrawer/UIElements/menucontroller.h \
    Core/gobject.h \
    Enums/objects.h \
    Core/gobjwrapper.h \
    Core/smcont.h \
    Core/buildings/building.h \
    Core/buildings/human/humsettlers.h \
    UIDrawer/UIElements/uiresdictionary.h \
    Core/buildings/sector.h \
    Core/mapgenerator.h \
    Enums/mapgeneratorsettings.h \
    Enums/map.h \
    Core/randomgen.h \
    Enums/randomsettings.h \
    UIDrawer/UIElements/monitorpanelcontroller.h \
    UIDrawer/UIElements/markercontroller.h \
    Enums/gameprocessingsettings.h \
    Core/playercontroller.h \
    Core/player/player.h \
    Core/player/humanplayer.h \
    Enums/procsettings/humanprocessingsettings.h \
    Core/player/requestmanager.h \
    Core/UnitController/unitcontroller.h \
    Core/UnitController/Units/unit.h \
    Core/UnitController/unitwrapper.h \
    UIDrawer/UIElements/uiunitcontroller.h \
    UIDrawer/UIElements/uiunitcntr.h \
    Core/UnitController/Units/Human/humshuttle.h \
    Core/buildings/human/humcolonycenter.h \
    Core/UnitController/Units/unitfactory.h \
    Core/UnitController/Units/Human/humanunitfactory.h \
    Enums/procsettings/humanunitprocessing.h \
    Enums/procsettings/unitprocessing.h \
    Core/SubComponents/emptysectorradar.h \
    Enums/races.h \
    Core/player/buildmanager.h \
    UIDrawer/UIElements/abilitybuttoncntr.h \
    UIDrawer/UIElements/abilitymenucontroller.h \
    Core/buildings/buildingfactory.h \
    Core/buildings/human/humanbuildingfactory.h \
    Core/player/Human/humanbuildmanager.h \
    Core/buildings/human/humtransportcenter.h \
    TestModule/testmanager.h \
    TestModule/requestmanagertest.h \
    Enums/procsettings/ability.h \
    Core/player/abilitymanager.h \
    Core/player/Human/humanabilitymanager.h \
    Core/player/abilityexecutor.h \
    Core/player/Human/Abilities/ioncanonsatellite.h \
    Core/UnitController/Units/bullet.h \
    Core/player/Human/Abilities/ioncanonbullet.h \
    Enums/objstatus.h \
    Core/objectstatecontroller.h \
    AudioModule/audiocontroller.h





### Copy of Qt libraries
QT5_LIBS = $$[QT_INSTALL_PREFIX]/bin/libgcc_s_dw2-1.dll \
           $$[QT_INSTALL_PREFIX]/bin/libwinpthread-1.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Core.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Cored.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Gui.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Network.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Qml.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Quick.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Multimedia.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5MultimediaWidgets.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5MultimediaQuick_p.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5OpenGL.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5PrintSupport.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Sensors.dll \
#           $$[QT_INSTALL_PREFIX]/bin/libstdc++-6.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Positioning.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Svg.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Widgets.dll \
           $$[QT_INSTALL_PREFIX]/bin/icudt54.dll \
           $$[QT_INSTALL_PREFIX]/bin/icuin54.dll \
           $$[QT_INSTALL_PREFIX]/bin/icuuc54.dll

QT5_LIBSD = $$[QT_INSTALL_PREFIX]/bin/libgcc_s_dw2-1.dll \
           $$[QT_INSTALL_PREFIX]/bin/libwinpthread-1.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Cored.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Guid.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Networkd.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Qmld.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Quickd.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Multimediad.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5MultimediaWidgetsd.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5MultimediaQuick_p.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5OpenGLd.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5PrintSupportd.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Sensorsd.dll \
#           $$[QT_INSTALL_PREFIX]/bin/libstdc++-6.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Positioningd.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Svgd.dll \
           $$[QT_INSTALL_PREFIX]/bin/Qt5Widgetsd.dll \
           $$[QT_INSTALL_PREFIX]/bin/icudt54.dll \
           $$[QT_INSTALL_PREFIX]/bin/icuin54.dll \
           $$[QT_INSTALL_PREFIX]/bin/icuuc54.dll

CONFIG(debug, debug|release) {
    DEST = debug
    copy_qt5_libs.input = QT5_LIBSD
} else {
    DEST = release
    copy_qt5_libs.input = QT5_LIBS
}


copy_qt5_libs.input = QT5_LIBS
copy_qt5_libs.output = $${OUT_PWD}/$${DEST}/${QMAKE_FILE_BASE}${QMAKE_FILE_EXT}
copy_qt5_libs.commands = ${COPY_FILE} ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
QMAKE_EXTRA_COMPILERS += copy_qt5_libs
