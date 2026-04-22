#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define BME_ADDRESS 0xEC // (0x76) if SDO -> GND else 0x77
int SDA_PIN = 21;
int SCL_PIN = 22;

Adafruit_BME280 bme;

float temp, pres, hum, alt;


// Functions
void getValues();
void initLed(int pin);
void blinkLed(int pin, int delay_ms);

void setup() {
  Serial.begin(115200);
  // bme_init(SDA_PIN, SCL_PIN);
  initLed(SDA_PIN);
  // initLed(SCL_PIN);  
}

void loop() {
  // getValues();
  blinkLed(SDA_PIN, 1000);
  // blinkLed(SCL_PIN, 500);
  
}


void bme_init(int sda_pin, int scl_pin) {
  Wire.begin(sda_pin, sda_pin); // SDA=21, SCL=22 (pins par défaut)
  Serial.println("BME280 Test");

  if (!bme.begin(BME280_ADDRESS)) {
    /* code */
    Serial.println("BME280 not found");
    while (!bme.begin(BME280_ADDRESS)) {
      Serial.println("Review hardware setup");
      vTaskDelay(1000);
    }
    
  }
  Serial.println("BME280 Ready - Test");
  vTaskDelay(1000);
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
  Serial.print("\n");
  vTaskDelay(1000);
}

void initLed(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void blinkLed(int pin, int delay_ms) {
  digitalWrite(pin, HIGH);
  vTaskDelay(delay_ms);
  digitalWrite(pin, LOW);
  vTaskDelay(delay_ms);
}
