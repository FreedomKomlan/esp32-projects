#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define BME_ADDRESS 0x76 // (0x76) if SDO -> GND else 0x77
int SDA_PIN = 21;
int SCL_PIN = 22;

Adafruit_BME280 bme;

float temp, pres, hum, alt;


// Functions
void scani2c();
void readstate(int sda_pin, int scl_pin);
void bme_init(int sda_pin, int scl_pin);
void getValues();
void initLed(int pin);
void blinkLed(int pin, int delay_ms);

void setup() {
  Serial.begin(115200);
  readstate(SDA_PIN, SCL_PIN);
  scani2c();
  bme_init(SDA_PIN, SCL_PIN);
  // initLed(SDA_PIN);
  // initLed(SCL_PIN);  
}

void loop() {
  getValues();
  // blinkLed(SDA_PIN, 1000);
  // blinkLed(SCL_PIN, 500);
  
}


void bme_init(int sda_pin, int scl_pin) {
  Wire.setClock(100000);
  Wire.begin(sda_pin, scl_pin); // SDA=21, SCL=22 (pins par défaut)
  Serial.println("BME280 Test");

  if (!bme.begin(0x76)) {
    /* code */
    Serial.println("BME280 not found");
    while (!bme.begin(0x76)) {
      Serial.println("Review hardware setup");
      vTaskDelay(5000);
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

void scani2c() {
  byte error, address;
  int nDevices = 0;
  Serial.println("Scanning...");
  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Device found at 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.print(" (7-bit) or 0x");
      Serial.print((address << 1), HEX);
      Serial.println(" (8-bit)");
      nDevices++;
    }
  }
  if (nDevices == 0) Serial.println("No I2C devices found");
  vTaskDelay(5000);
}

void readstate(int sda_pin, int scl_pin) {
  // Read lines state
  pinMode(sda_pin, INPUT_PULLUP);
  pinMode(scl_pin, INPUT_PULLUP);
  delay(10);
  bool sda_state = digitalRead(21);
  bool scl_state = digitalRead(22);
  Serial.printf("SDA: %d, SCL: %d\n", sda_state, scl_state);
  if (!sda_state) Serial.println("Warning: SDA is LOW (bus stuck?)");
}