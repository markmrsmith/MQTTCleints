const mqtt = require('mqtt');

const broker = 'mqtt://broker.emqx.io';
const topic = 'living_room_temperature_my_house';

// Create an MQTT client instance
const client = mqtt.connect(broker);

// Callback when the client is connected
client.on('connect', () => {
  console.log('Connected to MQTT broker');
  // Subscribe to the desired topic
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
    var fanstatus = "off"
    if (temperature > 70) {
      fanstatus = "on"
    } else {
      fanstatus = "off"
    }
    console.log(`Current Temperature is ${temperature} degrees - fan ${fanstatus}`);
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

// Gracefully handle SIGINT (Ctrl+C)
process.on('SIGINT', () => {
  client.end(() => {
    process.exit();
  });
});
