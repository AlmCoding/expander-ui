cmake_minimum_required(VERSION 3.16)

project(ExpanderUi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

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
        ui/panels/I2cConfigRequestPanel.qml
        ui/panels/I2cRequestListComponent.qml
        ui/panels/RequestModel.qml
        # stores
        ui/stores/RootStore.qml
    RESOURCES
        ui/resources/images/edit_button.png
        ui/resources/images/play_button.png
    SOURCES plugins/i2crequest.h plugins/i2crequest.cpp
    SOURCES plugins/i2crequestmodel.h plugins/i2crequestmodel.cpp
    SOURCES plugins/i2cconfig.h plugins/i2cconfig.cpp
)

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
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appExpanderUi
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
