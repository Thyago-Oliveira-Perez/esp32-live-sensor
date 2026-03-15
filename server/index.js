const WebSocket = require('ws')

const wss = new WebSocket.Server({ host: "0.0.0.0", port: 3000 })

console.log("WebSocket listening on port 3000")

wss.on('connection', (ws) => {

  console.log("ESP32 connected")

  ws.on('message', (message) => {
    console.log("Data received:", message.toString())
  })

  ws.on('close', () => {
    console.log("ESP32 disconnected")
  })

})
