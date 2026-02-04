cmake_minimum_required(VERSION 3.16)

project(AgendaContactosInteligente VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appAgendaContactosInteligente
    main.cpp
    Presentacion/src/presentationqml.cpp
    Presentacion/include/presentationqml.h
    Negocio/include/
    Negocio/src/
    Datos/include/
    Datos/src/
)

qt_add_qml_module(appAgendaContactosInteligente
    URI AgendaContactosInteligente
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES Datos/include/test.h
        SOURCES Datos/src/test.cpp
        SOURCES Negocio/src/test.cpp
        SOURCES Negocio/include/test.h

)



# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAgendaContactosInteligente PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAgendaContactosInteligente
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAgendaContactosInteligente
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appAgendaContactosInteligente
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


