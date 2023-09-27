# MQTT Client Publisher for C

This C code demonstrates how to create an MQTT client publisher using the MQTTClient library. The publisher connects to an MQTT broker, publishes temperature data to a specific topic, and simulates temperature changes at a specified interval.

## Prerequisites

- The MQTTClient library installed. You can download it from the [Eclipse Paho website](https://www.eclipse.org/paho/clients/c/).
- (it's  already a GIT submodule in the repository)
- A C development environment set up on your system.

## Usage

3. Run the executable:
   ```./MQTTClientPublisher```
   Optionally, you can specify a topic and delay (in microseconds) as command-line arguments. If no topic or delay is provided, the default values will be used.
   ```./MQTTClientPublisher [topic] [delay]```
The program will connect to the MQTT broker, publish temperature data to the specified topic, and simulate temperature changes at the specified interval.

## Keyboard Input

While the program is running, you can press 'q' or 'Q' to quit the program.

## Build

1. Default the MQTT broker details in the code: (not necessary in order to be modified).
   #define ADDRESS     "tcp://broker.emqx.io:1883"
   #define CLIENTID    "TemperaturePublisher"
   #define USERNAME    "emqx"
   #define PASSWORD    "public"
   #define DEFAULT_TOPIC  "living_room_temperature_my_house"
   #define DEFAULT_DELAY  1000
   *(These values are easily replaceable to allow code more reuse or made to be input parameters to make the code more generic)*
2. Compile the code using your C compiler:
    ```make all```

## Dependencies

MQTTClient: The MQTTClient library is used for MQTT communication. You can download it from the [Eclipse Paho website](https://www.eclipse.org/paho/clients/c/).

## License

This code is provided under the MIT License. See the LICENSE file for details.

## Author

Mark Smith <mr.smith.mark@gmail.com>
