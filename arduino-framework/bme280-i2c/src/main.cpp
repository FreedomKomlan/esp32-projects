#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define SDA_PIN 21
#define SCL_PIN 22
#define BME_ADDRESS 0xEC // (0x76) if SDO -> GND else 0x77

Adafruit_BME280 bme;

float temp, pres, hum, alt;


// Functions
void getValues();

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN); // SDA=21, SCL=22 (pins par défaut)
  Serial.println("BME280 Test");

  if (!bme.begin(BME280_ADDRESS)) {
    /* code */
    Serial.println("BME280 not found");
    while (!bme.begin(BME280_ADDRESS)) {
      Serial.println("Review hardware setup");
      delay(1000);
    }
    
  }
  Serial.println("BME280 Ready - Test");
  delay(1000);
  
}

void loop() {
  getValues();
  Serial.print("\n");
  delay(1000);
  
}

void getValues(){
  temp = bme.readTemperature();
  pres = bme.readPressure()/100.0f;
  hum = bme.readHumidity();
  alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  Serial.print("Altitude: "); Serial.println(alt);
  Serial.print("Pressure: "); Serial.println(pres);
  Serial.print("Temperature: "); Serial.println(temp);
  Serial.print("Humidity: "); Serial.println(hum);
}
