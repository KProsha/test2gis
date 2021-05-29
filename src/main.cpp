#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTextCodec>

#include "backend/backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qRegisterMetaType<HistogramState>("HistogramState");

    Backend backend;

    qmlRegisterUncreatableType<HistogramModel>("HistogramModel", 1, 0, "HistogramModel","Error:HistogramModel was created in QML");
    qmlRegisterUncreatableType<Backend>("Backend", 1, 0, "Backend","Error:Backend was created in QML");

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("histogramModel", backend.histogramModel());
    engine.rootContext()->setContextProperty("backend", &backend);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
