//#define CAYENNE_DEBUG
#define DHT_PIN 2
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <DHT.h>

DHT dht(DHT_PIN, DHT22);

// WiFi network info.
char ssid[] = "KV4";
char wifiPassword[] = "9232258002";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
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

	//Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
	if (millis() - lastMillis > 3000) {
		lastMillis = millis();
		//Write data to Cayenne here. This example just sends the current uptime in milliseconds.
    double temp = dht.readTemperature();
    Serial.println(temp);
		Cayenne.celsiusWrite(0, temp);
		//Some examples of other functions you can use to send data.
		//Cayenne.celsiusWrite(1, 22.0);
		//Cayenne.luxWrite(2, 700);
    double humid = dht.readHumidity();
		Cayenne.virtualWrite(1, humid, TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT);
    Serial.println(humid);
    Serial.println("");
	}
}

CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
