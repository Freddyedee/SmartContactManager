cmake_minimum_required(VERSION 3.16)

project(AgendaContactosInteligente VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Incluir las carpetas de los archivos fuente
include_directories(
    ${PROJECT_SOURCE_DIR}/src/Negocio/include
    ${PROJECT_SOURCE_DIR}/src/Presentacion/include
    ${PROJECT_SOURCE_DIR}/src/Datos/include
)

# Agregar los archivos fuente para cada capa
set(SOURCES
    main.cpp
    src/Presentacion/presentationqml.cpp               # Lógica de la presentación
                                                        # Lógica de la capa de negocio
                                                        # Lógica de la capa de datos
    src/Datos/ContactRepository.cpp

    include/Presentacion/presentationqml.h
    include/Negocio/Contact.h
    include/Datos/ContactRepository.h

)

# Crear el ejecutable
qt_add_executable(appAgendaContactosInteligente
    ${SOURCES}
    ${HEADERS}
)

# Agregar los archivos QML
qt_add_qml_module(appAgendaContactosInteligente
    URI AgendaContactosInteligente
    VERSION 1.0
    QML_FILES
        Main.qml
)

# Enlazar las bibliotecas necesarias
target_link_libraries(appAgendaContactosInteligente
    PRIVATE Qt6::Quick
)

# Configurar las propiedades del ejecutable
set_target_properties(appAgendaContactosInteligente PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Instalación
include(GNUInstallDirs)
install(TARGETS appAgendaContactosInteligente
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
