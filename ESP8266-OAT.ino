#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>

const char* ssid = "227";
const char* password = "rocknroll";

const char* firmwareURL = "http://192.168.2.209:8000/firmware.bin";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected!");

  WiFiClient client;
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, firmwareURL);

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.println("Update Failed");
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No Update");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("Update Success");
      break;
  }
}

void loop() {}
