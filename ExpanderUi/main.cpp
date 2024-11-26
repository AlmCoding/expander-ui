#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "plugins/containers/com/installertypes.h"
#include "plugins/containers/i2c/i2ctypes.h"
#include "plugins/device/comportmodel.h"
#include "plugins/device/firmwaredownloader.h"
#include "plugins/device/firmwarefilemodel.h"
#include "plugins/device/interfaceexpander.h"
#include "plugins/forms/i2cconfigform.h"
#include "plugins/forms/i2crequestform.h"
#include "plugins/i2clogmodel.h"
#include "plugins/i2crequestmodel.h"
#include "plugins/utility.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableMetaObject(InstallerTypes::staticMetaObject, "expander.containers.types", 1, 0,
                                     "InstallerTypes", "Error: InstallerTypes");
    qmlRegisterUncreatableMetaObject(I2cTypes::staticMetaObject, "expander.containers.types", 1, 0, "I2cTypes",
                                     "Error: I2cTypes");

    qmlRegisterType<Utility>("expander.utility", 1, 0, "Utility");
    qmlRegisterType<I2cConfigForm>("expander.forms", 1, 0, "I2cConfigForm");
    qmlRegisterType<I2cRequestForm>("expander.forms", 1, 0, "I2cRequestForm");

    qmlRegisterType<I2cRequestModel>("expander.models", 1, 0, "I2cRequestModel");
    qmlRegisterType<I2cLogModel>("expander.models", 1, 0, "I2cLogModel");
    qmlRegisterType<ComPortModel>("expander.models", 1, 0, "ComPortModel");
    qmlRegisterType<FirmwareFileModel>("expander.models", 1, 0, "FirmwareFileModel");

    qmlRegisterType<FirmwareDownloader>("expander.FirmwareDownloader", 1, 0, "FirmwareDownloader");
    qmlRegisterType<InterfaceExpander>("expander.InterfaceExpander", 1, 0, "InterfaceExpander");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/ExpanderUi/ui/Main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
