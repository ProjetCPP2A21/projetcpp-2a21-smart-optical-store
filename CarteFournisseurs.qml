import QtQuick 2.15
import QtQuick.Controls 2.15
import QtPositioning 5.15
import QtLocation 5.15

Item {
    id: mapWindow
    width: 1000
    height: 700

    property var fournisseursData: []

    function updateFournisseurs(data) {
        console.log("📡 Réception des données fournisseurs:", data.length, "fournisseurs")
        fournisseursData = data

        // Effacer les anciens marqueurs
        for (var i = map.mapItems.length - 1; i >= 0; i--) {
            map.removeMapItem(map.mapItems[i])
        }

        // Ajouter les nouveaux marqueurs
        for (var j = 0; j < data.length; j++) {
            var fournisseur = data[j]
            addFournisseurMarker(fournisseur)
        }

        console.log("✅ Marqueurs ajoutés:", data.length)
    }

    function addFournisseurMarker(fournisseur) {
        var component = Qt.createComponent("FournisseurMarker.qml")
        if (component.status === Component.Ready) {
            var marker = component.createObject(map, {
                coordinate: QtPositioning.coordinate(fournisseur.latitude, fournisseur.longitude),
                nom: fournisseur.nom,
                telephone: fournisseur.telephone,
                email: fournisseur.email,
                adresse: fournisseur.adresse,
                ville: fournisseur.ville
            })
            map.addMapItem(marker)
            console.log("📍 Marqueur ajouté:", fournisseur.nom, "à", fournisseur.latitude + "," + fournisseur.longitude)
        } else {
            console.log("❌ Erreur création composant:", component.errorString())
        }
    }

    // En-tête
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50
        color: "#2196F3"

        Text {
            anchors.centerIn: parent
            text: "🗺️ Carte des Fournisseurs - Tunisie"
            color: "white"
            font.bold: true
            font.pixelSize: 18
        }
    }

    Map {
        id: map
        anchors {
            top: parent.top
            topMargin: 50
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        plugin: Plugin {
            name: "osm"
        }

        center: QtPositioning.coordinate(34.0, 9.5) // Centre Tunisie
        zoomLevel: 6

        // Navigation
        DragHandler {
            target: null
            property real speedFactor: 0.03
            onTranslationChanged: {
                map.pan(-translation.x * speedFactor, -translation.y * speedFactor)
            }
        }

        WheelHandler {
            onWheel: function(wheel) {
                map.zoomLevel += wheel.angleDelta.y / 240
            }
        }
    }

    // Panel d'information
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 60
        anchors.leftMargin: 10
        width: 300
        height: 120
        color: "white"
        radius: 8
        border.color: "#3498db"
        border.width: 2
        opacity: 0.9

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 5

            Text {
                text: "📊 Statistiques Carte"
                font.bold: true
                font.pixelSize: 14
                color: "#2c3e50"
            }

            Text {
                text: "Fournisseurs affichés: " + fournisseursData.length
                font.pixelSize: 12
                color: "#34495e"
            }

            Text {
                text: "💡 Conseil: Cliquez sur les points pour voir les détails"
                font.pixelSize: 11
                color: "#7f8c8d"
                font.italic: true
                wrapMode: Text.WordWrap
                width: parent.width
            }
        }
    }

    // Message de bienvenue
    Component.onCompleted: {
        console.log("✅ CarteFournisseurs.qml chargé avec succès")
        console.log("📍 Centre carte:", map.center.latitude + "," + map.center.longitude)
        console.log("🔧 Zoom niveau:", map.zoomLevel)
    }
}
