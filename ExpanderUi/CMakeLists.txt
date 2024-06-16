cmake_minimum_required(VERSION 3.16)

project(ExpanderUi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick SerialPort)

qt_standard_project_setup()

qt_add_executable(appExpanderUi
    main.cpp
)

qt_add_qml_module(appExpanderUi
    URI ExpanderUi
    VERSION 1.0
    QML_FILES
        ui/Main.qml
        ui/views/I2cView.qml
        ui/views/SpiView.qml
        ui/views/SettingsView.qml
        ui/panels/I2cConfigPanel.qml
        ui/panels/I2cLogPanel.qml
        ui/panels/I2cConfigInterfacePanel.qml
        ui/panels/I2cConfigInterfacePanelTab.qml
        ui/panels/I2cRequestListPanel.qml
        ui/panels/I2cRequestFormPanel.qml
        ui/panels/I2cRequestFormMasterTab.qml
        ui/panels/I2cLogListPanel.qml
        ui/panels/ConnectionPanel.qml

        ui/components/I2cRequestListComponent.qml
        ui/components/I2cLogListComponent.qml

        # stores
        ui/stores/Constants.qml
        ui/stores/RootStore.qml
        ui/stores/I2cStore.qml
    RESOURCES
        ui/resources/images/edit_button.png
        ui/resources/images/play_button.png

    # plugins
    SOURCES plugins/i2crequestmodel.h plugins/i2crequestmodel.cpp
    SOURCES plugins/i2clog.h plugins/i2clog.cpp
    SOURCES plugins/i2clogmodel.h plugins/i2clogmodel.cpp
    # containers
    SOURCES plugins/containers/i2cconfig.h plugins/containers/i2cconfig.cpp
    SOURCES plugins/containers/i2crequest.h plugins/containers/i2crequest.cpp
    # forms
    SOURCES plugins/forms/i2cconfigform.h plugins/forms/i2cconfigform.cpp
    SOURCES plugins/forms/i2crequestform.h plugins/forms/i2crequestform.cpp
    # device
    SOURCES plugins/device/interfaceexpander.h plugins/device/interfaceexpander.cpp
    SOURCES plugins/device/devicecom.h plugins/device/devicecom.cpp
    SOURCES plugins/device/comportmodel.h plugins/device/comportmodel.cpp
    SOURCES plugins/device/driver/tfmsgtypes.h
    SOURCES plugins/device/driver/framedriver.h plugins/device/driver/framedriver.cpp
    SOURCES plugins/device/driver/i2cprotocom.h plugins/device/driver/i2cprotocom.cpp
)

add_subdirectory(libraries/tf)
add_subdirectory(libraries/proto)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appExpanderUi PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appExpanderUi
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appExpanderUi
    PRIVATE
        Qt6::Quick
        Qt6::SerialPort
        tf
        proto
)

include(GNUInstallDirs)
install(TARGETS appExpanderUi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
