#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 19    // broche DATA (GPIO4)
#define DHTTYPE DHT11   // modèle DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    Serial.println("DHT11 test start");
    dht.begin();
}

void loop() {
    delay(2000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
        Serial.println("Échec lecture DHT11 !");
    } else {
        Serial.print("Humidité: ");
        Serial.print(h);
        Serial.print("%  Température: ");
        Serial.print(t);
        Serial.println("°C");
    }
}