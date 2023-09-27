# Python MQTT Client

This Python script demonstrates how to connect to an MQTT broker, subscribe to a topic, and react to incoming messages.

## Prerequisites

Before running this script, make sure you have the following:

- Python installed on your system (Python 3 recommended).
- The Paho MQTT client library installed. You can install it using pip:
   pip install paho-mqtt

## Usage

default the MQTT broker details:
client.connect("broker.emqx.io", 1883, 60)
topic "living_room_temperature_my_house"  *(manually change if you are using a different topic name)*

## Run the script

python mqtt_client.py
The script will connect to the MQTT broker, subscribe to the specified topic ("living_room_temperature_my_house" in the provided code), and print temperature data along with fan status based on the received temperature.

## Dependencies

Paho MQTT: The Paho MQTT client library is used for MQTT communication.

## License

This code is provided under the MIT License.

## Author

Mark Smith  <mark.smith@gmail.com>.
