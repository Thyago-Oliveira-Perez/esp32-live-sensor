#include <WiFi.h>
#include <WebSocketsClient.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebSocketsClient webSocket;

unsigned long lastSend = 0;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  switch(type) {

    case WStype_CONNECTED:
      Serial.println("Connected to websocket");
      break;

    case WStype_DISCONNECTED:
      Serial.println("Disconnected");
      break;

    case WStype_ERROR:
      Serial.println("WebSocket error");
      break;

    case WStype_TEXT:
      Serial.printf("Message: %s\n", payload);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  webSocket.begin("YOUR_IP", 3000, "/");
  webSocket.onEvent(webSocketEvent);
}

void loop() {

  webSocket.loop();

  if (millis() - lastSend > 2000) {

    int head = random(0, 2);
    int torso = random(0, 2);
    int leftArm = random(0, 2);
    int rightArm = random(0, 2);
    int leftLeg = random(0, 2);
    int rightLeg = random(0, 2);

    String json = "{";
    json += "\"head\":" + String(head) + ",";
    json += "\"torso\":" + String(torso) + ",";
    json += "\"leftArm\":" + String(leftArm) + ",";
    json += "\"rightArm\":" + String(rightArm) + ",";
    json += "\"leftLeg\":" + String(leftLeg) + ",";
    json += "\"rightLeg\":" + String(rightLeg);
    json += "}";

    webSocket.sendTXT(json);

    lastSend = millis();
  }
}
