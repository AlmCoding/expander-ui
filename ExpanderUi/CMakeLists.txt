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
        ui/panels/I2cRequestFormSlaveTab.qml
        ui/panels/I2cLogListPanel.qml
        ui/panels/ConnectionPanel.qml
        ui/panels/DeviceInfoPanel.qml

        ui/components/I2cRequestListComponent.qml
        ui/components/I2cLogListComponent.qml

        # stores
        ui/stores/Constants.qml
        ui/stores/RootStore.qml
        ui/stores/I2cStore.qml
    RESOURCES
        ui/resources/images/edit_button.png
        ui/resources/images/play_100.png
        ui/resources/images/play_square_100.png
        ui/resources/images/play_round_90.png

    # plugins
    SOURCES plugins/i2crequestmodel.h plugins/i2crequestmodel.cpp
    SOURCES plugins/i2clog.h plugins/i2clog.cpp
    SOURCES plugins/i2clogmodel.h plugins/i2clogmodel.cpp

    # containers
    SOURCES plugins/containers/com/installertypes.h
    SOURCES plugins/containers/i2c/i2ctypes.h
    SOURCES plugins/containers/i2c/i2cconfig.h plugins/containers/i2c/i2cconfig.cpp
    SOURCES plugins/containers/i2c/i2crequest.h plugins/containers/i2c/i2crequest.cpp
    SOURCES plugins/containers/i2c/i2cconfigstatus.h plugins/containers/i2c/i2cconfigstatus.cpp
    SOURCES plugins/containers/i2c/i2crequeststatus.h plugins/containers/i2c/i2crequeststatus.cpp
    SOURCES plugins/containers/i2c/i2cnotification.h plugins/containers/i2c/i2cnotification.cpp
    SOURCES plugins/containers/ctrl/ctrltypes.h
    SOURCES plugins/containers/ctrl/ctrlrequest.h plugins/containers/ctrl/ctrlrequest.cpp
    SOURCES plugins/containers/ctrl/deviceinfo.h plugins/containers/ctrl/deviceinfo.cpp

    # forms
    SOURCES plugins/forms/i2cconfigform.h plugins/forms/i2cconfigform.cpp
    SOURCES plugins/forms/i2crequestform.h plugins/forms/i2crequestform.cpp

    # device
    SOURCES plugins/device/interfaceexpander.h plugins/device/interfaceexpander.cpp
    SOURCES plugins/device/devicemanager.h plugins/device/devicemanager.cpp
    SOURCES plugins/device/comportmodel.h plugins/device/comportmodel.cpp
    SOURCES plugins/device/driver/tfmsgtypes.h
    SOURCES plugins/device/driver/framedriver.h plugins/device/driver/framedriver.cpp
    SOURCES plugins/device/driver/i2cprotocom.h plugins/device/driver/i2cprotocom.cpp
    SOURCES plugins/device/driver/ctrlprotocom.h plugins/device/driver/ctrlprotocom.cpp
    SOURCES plugins/device/i2cservice.h plugins/device/i2cservice.cpp
    SOURCES plugins/device/ctrlservice.h plugins/device/ctrlservice.cpp
    SOURCES plugins/device/firmwareinstaller.h plugins/device/firmwareinstaller.cpp
)

add_subdirectory(libraries/tf)
add_subdirectory(libraries/proto)
add_subdirectory(libraries/enum)

# Add CubeProgrammer_API.dll and include dir
target_include_directories(appExpanderUi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cube/include)
target_link_directories(appExpanderUi PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cube/lib)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libraries/cube/lib/ DESTINATION .)

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
        magic_enum
        CubeProgrammer_API
)

include(GNUInstallDirs)
install(TARGETS appExpanderUi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
