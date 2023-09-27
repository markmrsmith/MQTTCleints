# Fan Control Web Application

This web application allows you to control a fan based on temperature data received via MQTT. It displays the fan status and temperature on a web page and listens for updates from an MQTT broker.

## Prerequisites

Before running this web application, make sure you have the following:

- A web server or hosting environment to serve the HTML and JavaScript files.
- MQTT broker details (provided in the JavaScript code).
- A compatible web browser to view the application.

## Usage

1. Update the MQTT broker details: (not necessary)

   ```javascript
   const broker = 'mqtt://broker.emqx.io';
   const topic = 'living_room_temperature_my_house'; // example broker and topic

2. Run a live server and connect to fan-control.html
Access the web application using a web browser. You should see the fan status and temperature displayed on the web page.
As the MQTT broker sends updates, the fan status and temperature will be automatically updated on the web page.

## Dependencies

MQTT.js: The MQTT.js library is used for MQTT communication.
Web server or hosting environment to serve the HTML and JavaScript files.

## License

This code is provided under the MIT License. See the LICENSE file for details.

## Author

Mark Smith <mr.smith.mark@gmail.com>
