cmake_minimum_required(VERSION 3.16)

project(AgendaContactosInteligente VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.9)


# Agregar los archivos fuente para cada capa
# All your C++ sources (.cpp)
set(CPP_SOURCES
    main.cpp
    src/Presentacion/presentationqml.cpp
    src/Negocio/Contact.cpp
    src/Negocio/Trie.cpp
    src/Negocio/ContactIndex.cpp
    src/Negocio/RecentContacts.cpp
    src/Negocio/ContactManager.cpp
    src/Datos/ContactRepository.cpp
    src/Presentacion/ConsoleUI.cpp   # if you still use console UI
)

# Optional: list headers only for IDE visibility (Qt Creator / CLion loves this)
set(HEADERS
    include/Negocio/Contact.h
    include/Negocio/Trie.h
    include/Negocio/ContactIndex.h
    include/Negocio/RecentContacts.h
    include/Negocio/ContactManager.h
    include/Datos/ContactRepository.h
    include/Presentacion/presentationqml.h
    include/Presentacion/ConsoleUI.h
)

# Crear el ejecutable
qt_add_executable(appAgendaContactosInteligente
    ${SOURCES}
    ${HEADERS}
)

# Incluir las carpetas de los archivos fuente
target_include_directories(appAgendaContactosInteligente PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Negocio
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Datos
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Presentacion
    ${CMAKE_CURRENT_SOURCE_DIR}/src      # optional, if you have any loose headers
)

# Agregar los archivos QML
qt_add_qml_module(appAgendaContactosInteligente
    URI AgendaContactosInteligente
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES include/Negocio/Contact.h src/Negocio/Contact.cpp
        SOURCES include/Negocio/Trie.h
        SOURCES src/Negocio/Trie.cpp
        SOURCES include/Negocio/ContactIndex.h
        SOURCES src/Negocio/ContactIndex.cpp
        SOURCES include/Negocio/RecentContacts.h
        SOURCES src/Negocio/RecentContacts.cpp
        SOURCES src/Datos/ContactRepository.cpp include/Datos/ContactRepository.h
        SOURCES src/Negocio/ContactManager.cpp
        SOURCES include/Negocio/ContactManager.h
        SOURCES include/Presentacion/ConsoleUI.h
        SOURCES src/Presentacion/ConsoleUI.cpp
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
