import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15 // Necesario para el estilo moderno

ApplicationWindow {
    id: window
    width: 1000
    height: 750
    visible: true
    title: "Repositorio de Contactos"

    // Configuración de Estilo Material
    Material.theme: Material.Light
    Material.accent: "#171717" // Un negro
    Material.primary: "#171717"

    property var contactosModel: []
    property int editingId: -1

    // Funciones lógicas se mantienen igual
    function log(msg) { console.log("[UI]", msg) }
    function refreshAll() { contactosModel = backend.getContacts() }
    function clearForm() {
        nombre.text = ""; tel.text = ""; email.text = ""
        editingId = -1
    }

    Component.onCompleted: refreshAll()

    // Fondo general con un tono gris muy suave para que los contenedores resalten
    background: Rectangle { color: "#f5f7fa" }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 25
        spacing: 20

        // ───────────────── CABECERA ─────────────────
        Text {
            text: "Agenda de Contactos"
            font.pixelSize: 28
            font.weight: Font.DemiBold
            color: "#171717"
            Layout.bottomMargin: 10
        }

        // ───────────────── FORMULARIO (Diseño Card) ─────────────────
        Pane {
            Layout.fillWidth: true
            padding: 20
            Material.elevation: 7 // Efecto de sombra

            background: Rectangle {
                color: "white"
                radius: 8
            }

            ColumnLayout {
                anchors.fill: parent
                spacing: 15

                Text {
                    text: editingId === -1 ? "NUEVO CONTACTO" : "EDITAR CONTACTO"
                    font.letterSpacing: 1.2
                    font.bold: true
                    color: Material.accent
                }

                RowLayout {
                    spacing: 15
                    TextField {
                        id: nombre
                        placeholderText: "Nombre completo"
                        Layout.fillWidth: true
                        selectByMouse: true
                    }

                    TextField {
                        id: tel
                        placeholderText: "Teléfono"
                        Layout.fillWidth: true
                        selectByMouse: true

                        inputMethodHints: Qt.ImhDigitsOnly
                        validator: RegularExpressionValidator {
                            regularExpression: /^[0-9]+$/
                        }

                        color: acceptableInput || text === "" ? "#171717" : "red"
                    }

                    TextField {
                        id: email
                        placeholderText: "Correo electrónico"
                        Layout.fillWidth: true
                        selectByMouse: true

                        validator: RegularExpressionValidator {
                            regularExpression: /^[^@\s]+@[^@\s]+\.[^@\s]+$/
                        }

                        color: (text === "" || acceptableInput) ? "#171717" : "red"
                    }

                    Button {
                        text: editingId === -1 ? "Agregar" : "Guardar"
                        highlighted: true
                        Material.elevation: 2

                        enabled:
                            nombre.text.length > 0 &&
                            tel.acceptableInput &&
                            (email.text === "" || email.acceptableInput)

                        onClicked: {
                            var ok = editingId === -1
                                ? backend.addContact(nombre.text, tel.text, email.text)
                                : backend.updateContact(editingId, nombre.text, tel.text, email.text)

                            if (ok) {
                                clearForm()
                                refreshAll()
                            }
                        }
                    }

                    Button {
                        text: "Cancelar"
                        flat: true
                        visible: editingId !== -1
                        onClicked: clearForm()
                    }

                    Text {
                        visible: !tel.acceptableInput && tel.text !== ""
                        text: " ¡El teléfono debe contener solo números!"
                        color: "red"
                        font.pixelSize: 12
                    }

                    Text {
                        visible: email.text !== "" && !email.acceptableInput
                        text: "¡El correo no es válido!"
                        color: "red"
                        font.pixelSize: 12
                    }

                }
            }
        }

        // ───────────────── BÚSQUEDAS Y ACCIONES ─────────────────
        RowLayout {
            Layout.fillWidth: true
            spacing: 20

            // Card de Búsqueda
            Pane {
                Layout.fillWidth: true
                Material.elevation: 2
                background: Rectangle { color: "white"; radius: 8 }

                RowLayout {
                    anchors.fill: parent
                    spacing: 10

                    TextField {
                        placeholderText: " Buscar por nombre..."
                        Layout.fillWidth: true
                        onTextChanged: contactosModel = text.length > 0 ? backend.searchByName(text) : backend.getContacts()
                    }

                    Rectangle { width: 1; Layout.fillHeight: true; color: "#eee" } // Separador visual

                    TextField {
                        id: searchExact
                        placeholderText: "Teléfono o Email..."
                        Layout.fillWidth: true
                    }
                    Button {
                        text: "Buscar"
                        onClicked: {
                            var r = backend.searchByTelOrEmail(searchExact.text)
                            contactosModel = r.id !== undefined ? [r] : []
                        }
                    }
                }
            }

            // Botones de Acción Rápidos
            RowLayout {
                Button {
                    text: "Recientes"
                    onClicked: contactosModel = backend.getRecentContacts()
                }
                Button {
                    text: "Ver Todos"
                    flat: true
                    onClicked: refreshAll()
                }
                Button {
                    text: "Exportar"
                    Material.accent: "#2C0091"
                    highlighted: true
                    onClicked: backend.exportCSV("C:/Users/USER/Desktop/contactos.csv") //ruta donde se exportara el svc
                }
            }
        }

        // ───────────────── LISTA DE CONTACTOS ─────────────────
        Text {
            text: "Listado (" + contactosModel.length + ")"
            font.pixelSize: 14
            color: "#7f8c8d"
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: contactosModel
            clip: true
            spacing: 8

            delegate: ItemDelegate { // ItemDelegate es mejor que Rectangle para interactividad
                width: listView.width
                height: 70

                background: Rectangle {
                    color: "white"
                    radius: 6
                    border.color: highlighted ? Material.accent : "transparent"
                    layer.enabled: true
                    // Sutil sombra para cada fila
                }

                contentItem: RowLayout {
                    spacing: 20

                    // Avatar circular generado con las iniciales
                    Rectangle {
                        width: 40; height: 40
                        radius: 20
                        color: "#171717"
                        Layout.leftMargin: 10
                        Text {
                            anchors.centerIn: parent
                            text: modelData.nombre.charAt(0).toUpperCase()
                            color: "white"
                            font.bold: true
                        }
                    }

                    ColumnLayout {
                        spacing: 2
                        Text {
                            text: modelData.nombre
                            font.bold: true
                            font.pixelSize: 16
                            color: "#2c3e50"
                        }
                        RowLayout {
                            Text { text: modelData.telefono; color: "#7f8c8d"; font.pixelSize: 12 }
                            Text { text: "✉ " + modelData.email; color: "#7f8c8d"; font.pixelSize: 12; Layout.leftMargin: 15 }
                        }
                    }

                    Item { Layout.fillWidth: true }

                    RowLayout {
                        Layout.rightMargin: 10
                        spacing: 5
                        Button {
                            text: "Editar"
                            flat: true
                            onClicked: {
                                nombre.text = modelData.nombre
                                tel.text = modelData.telefono
                                email.text = modelData.email
                                editingId = modelData.id
                            }
                        }
                        Button {
                            text: "Eliminar"
                            flat: true
                            Material.foreground: Material.Red
                            onClicked: if (backend.deleteContact(modelData.id)) refreshAll()
                        }
                    }
                }
            }
        }
    }
}
