#include <WiFi.h>
#include <WebSocketsClient.h>
#include <WiFiManager.h>
#include <Preferences.h>

WebSocketsClient webSocket;
Preferences preferences;

String serverIp;
int serverPort = 3000;

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

void setupWifi() {

  WiFiManager wm;

  preferences.begin("config", false);

  serverIp = preferences.getString("serverIp", "");

  char serverField[40];
  strcpy(serverField, serverIp.c_str());

  WiFiManagerParameter custom_server("server", "Server IP", serverField, 40);

  wm.addParameter(&custom_server);

  wm.startConfigPortal("ESP32-SETUP");

  serverIp = String(custom_server.getValue());

  preferences.putString("serverIp", serverIp);

  preferences.end();

  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  Serial.print("Server IP: ");
  Serial.println(serverIp);
}

void setup() {

  Serial.begin(115200);

  setupWifi();

  Serial.print("Connecting to: ");
  Serial.println(serverIp);

  delay(1000);

  webSocket.begin(serverIp.c_str(), serverPort, "/");
  webSocket.onEvent(webSocketEvent);

  webSocket.setReconnectInterval(2000);
  webSocket.enableHeartbeat(15000, 3000, 2);
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

    if (webSocket.isConnected()) {
      webSocket.sendTXT(json);
    }

    lastSend = millis();
  }
}