// =========================
// CONFIG
// =========================
#define SIMULATION_MODE 1   // 1 = simulation, 0 = capteur AS608 réel

const int LED_PIN = 13;

// =========================
// Includes / objets capteur
// =========================
#if !SIMULATION_MODE
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial fingerSerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);
#endif

// =========================
// Prototypes
// =========================
int getFingerprintID();
int fakeFingerprintID();

#if !SIMULATION_MODE
int getFingerprintID_real();
#endif

// =========================
// SETUP
// =========================
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

#if SIMULATION_MODE
  Serial.println("=== MODE SIMULATION ACTIVE ===");
  Serial.println("Tape un nombre (ID d'empreinte) dans le moniteur serie puis Enter.");
  Serial.println("Ex: 5  -> la LED s'allume et FINGER_OK:ID=5 est envoye.");
#else
  Serial.println("=== MODE CAPTEUR AS608 (REEL) ===");
  fingerSerial.begin(57600);

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Capteur AS608 detecte.");
  } else {
    Serial.println("Erreur: capteur AS608 non detecte !");
    // Blink rapide pour signaler l'erreur
    while (1) {
      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
      delay(200);
    }
  }
#endif
}

// =========================
// LOOP
// =========================
void loop() {
  int id = getFingerprintID();

  if (id >= 0) {
    // Empreinte reconnue (ou simulee)
    Serial.print("FINGER_OK:ID=");
    Serial.println(id);

    // Allume la LED pour signaler OK
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
  }

  delay(50);
}

// =========================
// Fonction commune: choisit le mode
// =========================
int getFingerprintID() {
#if SIMULATION_MODE
  return fakeFingerprintID();
#else
  return getFingerprintID_real();
#endif
}

// =========================
// MODE SIMULATION
// =========================
int fakeFingerprintID() {
  // On lit ce que l'utilisateur tape dans le moniteur serie
  if (Serial.available()) {
    int id = Serial.parseInt();  // lit un nombre
    if (id > 0) {
      Serial.print("SIMULATION: empreinte ID = ");
      Serial.println(id);
      return id;
    }
  }
  return -1;
}

// =========================
// MODE REEL (AS608)
// =========================
#if !SIMULATION_MODE
int getFingerprintID_real() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    // Serial.println("Empreinte non reconnue.");
    return -1;
  }

  Serial.print("Empreinte trouvee, ID: ");
  Serial.print(finger.fingerID);
  Serial.print("  Confiance: ");
  Serial.println(finger.confidence);

  return finger.fingerID;
}
#endif
