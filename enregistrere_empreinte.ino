#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial fingerSerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

uint8_t idToEnroll = 0;  // slot où on va stocker l'empreinte

void setup() {
  Serial.begin(9600);
  fingerSerial.begin(57600);

  Serial.println("Initialisation capteur...");
  finger.begin(57600);
  if (!finger.verifyPassword()) {
    Serial.println("Capteur non detecte, verifie le cablage.");
    while (1);
  }
  Serial.println("Capteur OK.");
  Serial.println("Tape un ID d'empreinte (1..127) puis appuie sur Enter :");
}

void loop() {
  // 1) On attend que l'utilisateur tape un ID d'empreinte dans le moniteur série
  if (Serial.available()) {
    idToEnroll = Serial.parseInt(); // lit nombre tapé
    if (idToEnroll > 0) {
      Serial.print("Enregistrement de l'empreinte dans le slot ");
      Serial.println(idToEnroll);
      enrollFingerprint(idToEnroll);
      Serial.println("Tape un nouvel ID pour une autre empreinte :");
    }
  }
}

void enrollFingerprint(uint8_t id) {
  int p = -1;
  Serial.println("Place ton doigt sur le capteur...");

  // Attente image 1
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }
  Serial.println("Image 1 OK");

  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) {
    Serial.println("Erreur conversion image 1");
    return;
  }

  Serial.println("Retire ton doigt.");
  delay(2000);

  Serial.println("Remets le même doigt...");
  p = -1;
  // Attente image 2
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }
  Serial.println("Image 2 OK");

  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) {
    Serial.println("Erreur conversion image 2");
    return;
  }

  // Création du modèle
  p = finger.createModel();
  if (p != FINGERPRINT_OK) {
    Serial.println("Impossible de créer le modèle, recommence.");
    return;
  }

  // Stockage du modèle dans le slot 'id'
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.print("Empreinte enregistree avec succes dans le slot ");
    Serial.println(id);
  } else {
    Serial.println("Erreur lors du stockage du modele.");
  }
}
