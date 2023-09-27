#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>

#ifdef WIN32
#include <conio.h>
#include <windows.h>
#else
#include <ncurses.h> // For keyboard input handling
#include <unistd.h> // Include unistd.h for usleep
#define _getch getch
#endif

#define ADDRESS     "tcp://broker.emqx.io:1883"
#define CLIENTID    "TemperatureAndFanSubscriber"
#define DEFAULT_TOPIC  "living_room_temperature_my_house"
#define QOS         1
#define FAN_ON_TEMPERATURE 70

int messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message) {
    //printf("Received message on topic: %s\n", topicName);
    //printf("Message payload: %.*s\n", message->payloadlen, (char*)message->payload);

    // Parse temperature from the message payload (replace with your logic)
    int temperature = atoi((char*)message->payload);

    // Fan control logic (replace with your logic)
    const char* fan_state = (temperature > FAN_ON_TEMPERATURE) ? "fan on" : "fan off";
    // this is where you would put the logic to turn on or off the fan
    printf("Current Temperature is %d degrees - %s\r\n", temperature, fan_state);
    fflush(stdout);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return(1);
}

int main(int argc, char* argv[]) {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    char userInput = 'c';
    char* topic = (char*)DEFAULT_TOPIC;

    //process input arguments
    if (argc < 2)
    {
        printf("Usage  MQTTClientSubscriber topic\n;");
    }
    else
    {
        if (argc >= 2)
        {
            topic = argv[1];
        }
        printf("Usage  MQTTClientSubscriber %s\n;", topic);
    }
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    MQTTClient_setCallbacks(client, NULL, NULL, messageArrived, NULL);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect to the MQTT broker, return code %d\n", rc);
        exit(-1);
    }

    MQTTClient_subscribe(client, topic, QOS);
    #ifndef WIN32
// Initialize ncurses
    initscr(); 
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    #endif
    printf("Subscribed to topic: %s\r\n", topic);

    printf("Press 'q' to quit...\r\n");

    while (userInput != 'q' && userInput != 'Q') {
        // The subscriber will receive messages via the messageArrived callback
        // No need for busy waiting or delay here
 
#ifdef WIN32
        if (_kbhit()) {
            userInput = _getch();
        }
#else
        userInput = _getch();
#endif

    }
    #ifndef WIN32
    endwin(); // End ncurses
    #endif
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
    
}
