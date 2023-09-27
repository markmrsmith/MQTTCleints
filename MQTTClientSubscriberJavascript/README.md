
# MQTT Client for JavaScript

This JavaScript code demonstrates how to create an MQTT client using the MQTT.js library. The client connects to an MQTT broker, subscribes to a specific topic, and reacts to incoming messages.

## Prerequisites

Before using this script, make sure you have the following:

- Node.js installed on your system.
- The MQTT.js library installed. You can install it using npm:

   ```npm install mqtt```

## Usage

1. Update the MQTT broker details: (not necessary)

   const broker = 'mqtt://broker.emqx.io';
   const topic = 'living_room_temperature_my_house'; // example broker and topic

## Run the script

node mqtt_client.js
The script will connect to the MQTT broker, subscribe to the specified topic, and print the current temperature along with the fan status based on the received temperature.

## Error Handling

The script handles errors and disconnections from the MQTT broker. It also gracefully handles the SIGINT signal (Ctrl+C) to ensure a clean shutdown.

## Dependencies

MQTT.js: The MQTT.js library is used for MQTT communication.

## License

This code is provided under the MIT License. See the LICENSE file for details.

## Author

Mark Smith <mr.smith.mark@gmail.com>
