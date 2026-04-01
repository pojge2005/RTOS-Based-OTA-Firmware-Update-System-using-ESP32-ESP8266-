#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "227";
const char* password = "rocknroll";


// ESP8266 IP
const char* triggerURL = "http://192.168.2.205/update";

void triggerTask(void *pvParameters) {
  while (1) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      Serial.println("Sending OTA trigger...");
      http.begin(triggerURL);

      int httpCode = http.GET();

      Serial.print("Response Code: ");
      Serial.println(httpCode);

      http.end();
    }

    vTaskDelay(10000 / portTICK_PERIOD_MS); // every 10 sec
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Create FreeRTOS task
  xTaskCreate(triggerTask, "Trigger Task", 4096, NULL, 1, NULL);
}

void loop() {}
