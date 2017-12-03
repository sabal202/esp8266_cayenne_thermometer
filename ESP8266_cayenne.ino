#include <CayenneMQTTESP8266.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define DHT_PIN 2

DHT dht(DHT_PIN, DHT22);

const char* ssid = "ddd";
const char* wifiPassword = "ddd";

char username[] = "ddd";
char password[] = "ddd";
char clientID[] = "ddd";

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifiPassword);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed!\nRebooting...");
    delay(5000);
    ESP.restart();
  }

  //ArduinoOTA.setPort(8266);
  //ArduinoOTA.setHostname("myesp8266_thermometer");
  //ArduinoOTA.setPassword((const char *)"sabal");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Serial.println("ArduinoOTA.handle();");
  ArduinoOTA.handle();
  Serial.println("Cayenne.loop();");
  Cayenne.loop();
  Serial.println("End");
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
