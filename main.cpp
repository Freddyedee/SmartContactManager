// #include <QGuiApplication>
// #include <QQmlApplicationEngine>
// #include <iostream>

// int main(int argc, char *argv[])
// {
//     /*
//     Inicializar Qt

//     Procesar argumentos de línea de comandos

//     Preparar el loop de eventos

//     Sin esta línea, ninguna app Qt puede funcionar.
//     */

//     QGuiApplication app(argc, argv);

//     /*
//         Carga archivos qml, crear arbol de objetos qml, maneja errores de carga
//         expone objetos c++ a qml.
//     */
//     QQmlApplicationEngine engine;

//     /*
//         Manejo de errores, cierra la app si falla la carga QML

//     */
//     QObject::connect(
//         &engine,
//         &QQmlApplicationEngine::objectCreationFailed,
//         &app,
//         []() { QCoreApplication::exit(-1); },
//         Qt::QueuedConnection);
//     /*Qt::QueuedConnection

//     Garantiza que la salida ocurra después de que Qt termine de procesar la señal.
//     */

//     qDebug() << "Cargando QML...";


//     engine.loadFromModule("AgendaContactosInteligente", "Main");
//     return app.exec();
// }

#include "ContactManager.h"
#include "ConsoleUI.h"
#include <iostream>

int main() {
    try {
        ContactManager manager;
        ConsoleUI ui(&manager);
        ui.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}


