#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    /*
    Inicializar Qt

    Procesar argumentos de línea de comandos

    Preparar el loop de eventos

    Sin esta línea, ninguna app Qt puede funcionar.
    */

    QGuiApplication app(argc, argv);

    /*
        Carga archivos qml, crear arbol de objetos qml, maneja errores de carga
        expone objetos c++ a qml.
    */
    QQmlApplicationEngine engine;

    /*
        Manejo de errores, cierra la app si falla la carga QML

    */
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
        /*Qt::QueuedConnection

    Garantiza que la salida ocurra después de que Qt termine de procesar la señal.
    */
    engine.loadFromModule("AgendaContactosInteligente", "Main");
//sssss
    return app.exec();
}
