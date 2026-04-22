#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  Wire.setClock(10000); // 10 kHz, très lent

  Serial.println("BME280 Hard Reset Attempt");

  // 1. Reset logiciel
  Wire.beginTransmission(0x76);
  Wire.write(0xE0); // registre reset
  Wire.write(0xB6); // mot magique
  byte err = Wire.endTransmission();
  if (err != 0) {
    Serial.printf("Reset write failed, error %d\n", err);
  } else {
    Serial.println("Reset command sent");
  }
  delay(100);

  // 2. Lire Chip ID
  Wire.beginTransmission(0x76);
  Wire.write(0xD0);
  Wire.endTransmission(false);
  Wire.requestFrom(0x76, 1);
  if (Wire.available()) {
    uint8_t id = Wire.read();
    Serial.printf("Chip ID: 0x%02X (expected 0x60 or 0x58)\n", id);
    if (id == 0x60 || id == 0x58) {
      Serial.println("Sensor is alive!");
    } else {
      Serial.println("Wrong ID - sensor may be damaged or wrong address");
    }
  } else {
    Serial.println("No response - sensor not detected");
  }

  // 3. Essayer l'autre adresse (0x77)
  Wire.beginTransmission(0x77);
  Wire.write(0xD0);
  Wire.endTransmission(false);
  Wire.requestFrom(0x77, 1);
  if (Wire.available()) {
    uint8_t id = Wire.read();
    Serial.printf("Chip ID at 0x77: 0x%02X\n", id);
  } else {
    Serial.println("No response at 0x77 either");
  }
}

void loop() {}