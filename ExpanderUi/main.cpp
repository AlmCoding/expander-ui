#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "plugins/i2cconfig.h"
#include "plugins/i2clogmodel.h"
#include "plugins/i2crequestform.h"
#include "plugins/i2crequestmodel.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<I2cConfig>("expander.I2cConfig", 1, 0, "I2cConfig");
    qmlRegisterType<I2cRequestModel>("expander.I2cRequestModel", 1, 0, "I2cRequestModel");
    qmlRegisterType<I2cRequestForm>("expander.I2cRequestForm", 1, 0, "I2cRequestForm");
    qmlRegisterType<I2cLogModel>("expander.I2cLogModel", 1, 0, "I2cLogModel");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/ExpanderUi/ui/Main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
