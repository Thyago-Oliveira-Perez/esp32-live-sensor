# ESP32 WebSocket Bridge

A simple example showing how an **ESP32 sends data over WiFi using WebSockets** to a **Node.js server**.

This project demonstrates a basic real-time communication setup where the ESP32 connects to a WiFi network and periodically sends messages to a WebSocket server running on Node.js.

## Architecture

ESP32 → WiFi → WebSocket → Node.js Server

The ESP32 acts as a **WebSocket client** and the Node.js application acts as a **WebSocket server** that receives and logs incoming messages.

## Features

* ESP32 connects to WiFi
* WebSocket communication over the local network
* Node.js server listens for incoming messages
* Simple JSON message example
* Real-time data streaming

## Project Structure

```
esp32-websocket-bridge/
│
├── firmware/
│   └── index.ino
│   └── package.json
│   └── package-lock.json
│
├── server/
│   └── index.js
│
└── README.md
```

## Requirements

### Hardware

* ESP32 development board

### Software

* Arduino IDE
* Node.js (v16+ recommended)

### Arduino Libraries

Install the following library in the Arduino IDE:

* WebSockets by Markus Sattler

## Setup

### 1. ESP32

Update the WiFi credentials and server IP inside the ESP32 sketch:

```
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
```

Set the IP address of the machine running the Node.js server:

```
webSocket.begin("YOUR_SERVER_IP", 3000, "/");
```

Upload the sketch to your ESP32.

### 2. Node.js Server

Navigate to the server directory:

```
cd node-server
```

Install dependencies:

```
npm install ws
```

Run the server:

```
node server.js
```

You should see:

```
WebSocket server listening on port 3000
```

## Example Output

When the ESP32 connects and sends data:

```
ESP32 connected
Data received: {"sensor":25}
Data received: {"sensor":25}
```

## Notes

* Make sure the ESP32 and the Node.js server are on the **same network**.
* Close the Arduino Serial Monitor if it is using the same device.
* Replace the IP address in the ESP32 code with the correct address of your computer.

## License

MIT
