import QtQuick 2.15
import QtQuick.Controls 2.15  // ← AJOUTER CET IMPORT POUR POPUP
import QtPositioning 5.15
import QtLocation 5.15

MapQuickItem {
    id: marker

    property string nom: ""
    property string telephone: ""
    property string email: ""
    property string adresse: ""
    property string ville: ""

    anchorPoint.x: sourceItem.width / 2
    anchorPoint.y: sourceItem.height / 2

    sourceItem: Rectangle {
        width: 20
        height: 20
        radius: 10
        color: "#e74c3c"
        border.color: "white"
        border.width: 3

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onEntered: {
                parent.scale = 1.2
                parent.color = "#c0392b"
            }

            onExited: {
                parent.scale = 1.0
                parent.color = "#e74c3c"
            }

            onClicked: {
                console.log("👆 Clic sur marqueur:", nom)
                infoPopup.nom = nom
                infoPopup.telephone = telephone
                infoPopup.email = email
                infoPopup.adresse = adresse
                infoPopup.ville = ville
                infoPopup.open()
            }
        }
    }

    Popup {
        id: infoPopup
        x: -140
        y: -160
        width: 320
        height: 180
        modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        property string nom: ""
        property string telephone: ""
        property string email: ""
        property string adresse: ""
        property string ville: ""

        background: Rectangle {
            color: "white"
            radius: 12
            border.color: "#3498db"
            border.width: 3
        }

        Column {
            anchors.fill: parent
            anchors.margins: 15
            spacing: 8

            Text {
                text: infoPopup.nom
                font.bold: true
                font.pixelSize: 18
                color: "#2c3e50"
                width: parent.width
                elide: Text.ElideRight
            }

            Rectangle {
                width: parent.width
                height: 2
                color: "#ecf0f1"
                radius: 1
            }

            // Téléphone
            Row {
                width: parent.width
                spacing: 8

                Text {
                    text: "📞"
                    font.pixelSize: 14
                }

                Text {
                    text: infoPopup.telephone ? infoPopup.telephone : "Non spécifié"
                    font.pixelSize: 14
                    color: "#34495e"
                    width: parent.width - 30
                    wrapMode: Text.WrapAnywhere
                }
            }

            // Email
            Row {
                width: parent.width
                spacing: 8

                Text {
                    text: "✉️"
                    font.pixelSize: 14
                }

                Text {
                    text: infoPopup.email ? infoPopup.email : "Non spécifié"
                    font.pixelSize: 14
                    color: "#34495e"
                    width: parent.width - 30
                    elide: Text.ElideMiddle
                }
            }

            // Adresse
            Row {
                width: parent.width
                spacing: 8
                visible: infoPopup.adresse

                Text {
                    text: "📍"
                    font.pixelSize: 14
                }

                Text {
                    text: infoPopup.adresse
                    font.pixelSize: 12
                    color: "#7f8c8d"
                    width: parent.width - 30
                    wrapMode: Text.WordWrap
                    maximumLineCount: 2
                    elide: Text.ElideRight
                }
            }

            // Ville
            Row {
                width: parent.width
                spacing: 8

                Text {
                    text: "🏙️"
                    font.pixelSize: 14
                }

                Text {
                    text: infoPopup.ville ? infoPopup.ville : "Tunisie"
                    font.pixelSize: 12
                    color: "#7f8c8d"
                    font.italic: true
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("✅ Marqueur créé pour:", nom)
    }
}
