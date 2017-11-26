#include <CayenneMQTTESP8266.h>
#include <DHT.h>


#define DHT_PIN 2

DHT dht(DHT_PIN, DHT22);

char ssid[] = "KV4";
char wifiPassword[] = "9232258002";

char username[] = "e4ca7f00-c60d-11e7-9768-2143f8645011";
char password[] = "296689e68ebd90f5a765c74275a8c8bd00181860";
char clientID[] = "2d07fba0-cc74-11e7-8123-07faebe02555";

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();

  if (millis() - lastMillis > 3000) {
    lastMillis = millis();

    double temp = dht.readTemperature();
    Cayenne.celsiusWrite(0, temp);
    Serial.println(temp);

    double humid = dht.readHumidity();
    Cayenne.virtualWrite(1, humid, TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT);
    Serial.println(humid);

    Serial.println("");
  }
}
