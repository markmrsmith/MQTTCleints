// const mqtt = require('mqtt');

const broker = 'mqtt://broker.emqx.io';
const topic = 'living_room_temperature_my_house'; // Replace with the appropriate topic for fan status and speed
const clientId = 'mqttjs_' + Math.random().toString(16).substr(2, 8)
const host = 'ws://broker.emqx.io:8083/mqtt'
    const options = {
      keepalive: 60,
      clientId: clientId,
      protocolId: 'MQTT',
      protocolVersion: 5,
      clean: true,
      reconnectPeriod: 1000,
      connectTimeout: 30 * 1000,
      will: {
        topic: 'WillMsg',
        payload: 'Connection Closed abnormally..!',
        qos: 0,
        retain: false
      },
    }
const client = mqtt.connect(host,options);

// Callback when the client is connected
client.on('connect', () => {
    console.log('Connected to MQTT broker');
    // Subscribe to the fan status and speed topic
    client.subscribe(topic, (err) => {
        if (!err) {
            console.log(`Subscribed to topic: ${topic}`);
        }
    });
});

// Callback when a message is received
client.on('message', (receivedTopic, message) => {
    if (receivedTopic === topic) {
        const temperature = parseFloat(message.toString());
        var fanstatus = "Off"
        // Implement your fan control logic based on the temperature here
        if (temperature > 70) {
            fanstatus = "on"
          } else {
            fanstatus = "off"
        }
        console.log(`Current Temperature is ${temperature} degrees - fan ${fanstatus}`);
        
        const data = JSON.parse(message.toString());

        // Update the HTML elements with fan status and speed
        document.getElementById('fanStatus').textContent = fanstatus;
        document.getElementById('fanTemperatrue').textContent = temperature;
    }

});

// Handle errors
client.on('error', (err) => {
    console.error('MQTT error:', err);
});

// Handle disconnects
client.on('close', () => {
    console.log('Disconnected from MQTT broker');
});
