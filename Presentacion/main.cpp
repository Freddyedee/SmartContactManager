#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "Backend/backendmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    BackendManager backend;
    qDebug() << "Backend creado:" << &backend;

    engine.rootContext()->setContextProperty("backend", &backend);

    const QUrl url = QUrl::fromLocalFile(
        QCoreApplication::applicationDirPath() +
        "/../../Presentacion/Main.qml"
        );

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
        );

    qDebug() << "Intentando cargar QML desde:" << url;
    engine.load(url);

    if (engine.rootObjects().isEmpty()) {
        qCritical() << "ERROR: No se cargó ningún objeto QML";
        return -1;
    }

    qDebug() << "QML cargado correctamente";
    return app.exec();
}
