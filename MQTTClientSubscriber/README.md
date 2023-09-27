# MQTT Client subscriber for C

This C code demonstrates how to create an MQTT client subscriber using the MQTTClient library. The client connects to an MQTT broker, subscribes to a specific topic, and receives to incoming messages.

## Prerequisites

- The MQTTClient library installed. You can download it from the [Eclipse Paho website](https://www.eclipse.org/paho/clients/c/).
- (it's  already a GIT submodule in the repository)
- A C development environment set up on your system.

## Usage

  ```./MQTTClientSubscriber```
   Optionally, you can specify a topic as a command-line argument. If no topic is provided, the default topic will be used.
   ```./mqttclientSubscriber [topic]```
   The program will connect to the MQTT broker, subscribe to the specified topic, and print the current temperature along with the fan status based on the received temperature.

## Build

1. Default the MQTT broker details in the code: (not necessary to be modified).
   #define ADDRESS     "tcp://broker.emqx.io:1883"
   #define CLIENTID    "TemperatureAndFanSubscriber"
   #define FAN_ON_TEMPERATURE 70
   #define DEFAULT_TOPIC  "living_room_temperature_my_house"
   *(These values are easily replaceable to allow code more reuse or made to be input parameters to make the code more generic)*
2. Compile the code using your C compiler:
    ```make all```

## Error Handling

The code handles errors and disconnections from the MQTT broker. It also provides a way to quit the program by pressing 'q' or 'Q'.

## Dependencies

MQTTClient: The MQTTClient library is used for MQTT communication. You can download it from the [Eclipse Paho website](https://www.eclipse.org/paho/clients/c/).

## License

This code is provided under the MIT License. See the LICENSE file for details.

## Author

Mark Smith <mr.smith.mark@gmail.com>
