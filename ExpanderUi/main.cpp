#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>

#include "plugins/containers/com/installertypes.h"
#include "plugins/containers/i2c/i2ctypes.h"
#include "plugins/device/comportmodel.h"
#include "plugins/device/firmwaredownloader.h"
#include "plugins/device/firmwarefilemodel.h"
#include "plugins/device/interfaceexpander.h"
#include "plugins/forms/i2cconfigform.h"
#include "plugins/forms/i2crequestform.h"
#include "plugins/i2clogdetails.h"
#include "plugins/i2clogmodel.h"
#include "plugins/i2crequestmodel.h"
#include "plugins/updatemanager.h"
#include "plugins/utility.h"
#include "version.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    qSetMessagePattern("[%{type}] (%{file}:%{line}) - %{message}");

    qmlRegisterUncreatableMetaObject(InstallerTypes::staticMetaObject, "expander.containers.types", 1, 0,
                                     "InstallerTypes", "Error: InstallerTypes");
    qmlRegisterUncreatableMetaObject(I2cTypes::staticMetaObject, "expander.containers.types", 1, 0, "I2cTypes",
                                     "Error: I2cTypes");

    qmlRegisterType<Utility>("expander.Utility", 1, 0, "Utility");
    qmlRegisterType<UpdateManager>("expander.UpdateManager", 1, 0, "UpdateManager");
    qmlRegisterType<I2cLogDetails>("expander.I2cLogDetails", 1, 0, "I2cLogDetails");
    qmlRegisterType<I2cConfigForm>("expander.forms", 1, 0, "I2cConfigForm");
    qmlRegisterType<I2cRequestForm>("expander.forms", 1, 0, "I2cRequestForm");

    qmlRegisterType<I2cRequestModel>("expander.models", 1, 0, "I2cRequestModel");
    qmlRegisterType<I2cLogModel>("expander.models", 1, 0, "I2cLogModel");
    qmlRegisterType<ComPortModel>("expander.models", 1, 0, "ComPortModel");
    qmlRegisterType<FirmwareFileModel>("expander.models", 1, 0, "FirmwareFileModel");

    qmlRegisterType<FirmwareDownloader>("expander.FirmwareDownloader", 1, 0, "FirmwareDownloader");
    qmlRegisterType<InterfaceExpander>("expander.InterfaceExpander", 1, 0, "InterfaceExpander");

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/ExpanderUi/ui/Main.qml");
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

#if defined(Q_OS_WIN)
    QIcon icon("ExpanderUi/ui/resources/images/icon.ico");
#elif defined(Q_OS_UNIX)
    QIcon icon("ExpanderUi/ui/resources/images/icon.png");
#endif
    qDebug() << "Icon is null?" << icon.isNull();
    app.setWindowIcon(icon);
    app.setApplicationVersion(
        QString("V%1.%2.%3").arg(PROJECT_VERSION_MAJOR).arg(PROJECT_VERSION_MINOR).arg(PROJECT_VERSION_PATCH));

    return app.exec();
}
