#include <CayenneMQTTESP8266.h>
#include <DHT.h>

#define DHT_PIN 2

DHT dht(DHT_PIN, DHT22);

char ssid[] = "";
char wifiPassword[] = "";

char username[] = "e4ca7f00-645011";
char password[] = "4275a8c8bd00181860";
char clientID[] = "2d07faebe02555";

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  Serial.println("Ready");
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
