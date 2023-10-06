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
#define CLIENTID    "TemperaturePublisher"

#define QOS         2  //HIGH Quality of Service
#define USERNAME    "emqx"
#define PASWORD     "public"
#define DEFAULT_TOPIC       "living_room_temperature_my_house"
#define DEFAULT_DELAY  1000 //one second




int main(int argc, char* argv[]) {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer; //default options for MQTT client
    int MQTTClientReturn= MQTTCLIENT_FAILURE;
    char userInput = 'c';
    char ClientIdString[128];
    int prev_temperature = rand() % 100;  //pick a randmon starting temperature 
    // Replace with your actual temperature reading logic

    char * topic = (char*)DEFAULT_TOPIC;
    int delay_milliseconds = DEFAULT_DELAY;
    //process input arguments
    if (argc < 2)
    {
        printf("Usage  MQTTClientPublisher topic delay in milliseconds\n;");
        
    }
    else
    {
        if (argc >= 2)
        {
            topic = argv[1];
        }
        if (argc >= 3)
        {
            delay_milliseconds = atoi(argv[2]);
        }
        printf("Usage  MQTTClientPublisher %s %d\n;", topic, delay_milliseconds);
    }





    // create cleint and connection
    // should make client ID unique
    snprintf(ClientIdString, sizeof(ClientIdString), "%s_%d", CLIENTID, rand());
    MQTTClient_create(&client, ADDRESS, ClientIdString, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = USERNAME;
    conn_opts.password =PASWORD;
    
 

    printf("Press 'q' to quit...\r\n");

    #ifdef WIN32
    HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
    LARGE_INTEGER dueTime = { 0,0 };
    dueTime.QuadPart = -((LONGLONG)delay_milliseconds * 10000LL); // Convert milliseconds to 100-nanosecond intervals
    #else 
    // Initialize ncurses
    initscr(); 
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    #endif
    

    while (userInput != 'q' && userInput != 'Q') {
        char payload[20];
        int temperature = prev_temperature + (rand() % 5) - (rand() % 5); // Replace with your actual temperature reading logic
        // for now use previouse temperature +- 5 to make it more resonable
        // a better approx would a ramp up to relatively stable vaule

        // try to create connection
        if (MQTTClientReturn != MQTTCLIENT_SUCCESS)
        {
            MQTTClientReturn = MQTTClient_connect(client, &conn_opts);
            if (MQTTClientReturn != MQTTCLIENT_SUCCESS)
                printf("Failed to connect to the MQTT broker, return code %d\n", MQTTClientReturn);
            else
                printf("Connected to the MQTT broker, %s\n", ClientIdString);
        }
        else
        {
            snprintf(payload, sizeof(payload), "%d", temperature);
            MQTTClient_message pubmsg = MQTTClient_message_initializer;
            pubmsg.payload = payload;
            pubmsg.payloadlen = strlen(payload);
            pubmsg.qos = QOS;
            MQTTClient_publishMessage(client, topic, &pubmsg, NULL);
            printf("Send %d to topic %s\r\n", temperature, topic);
            fflush(stdout);
        }
        prev_temperature = temperature;
        #ifdef WIN32
        // Use the timer to create a delay
        SetWaitableTimer(timer, &dueTime, 0, NULL, NULL, FALSE);
        WaitForSingleObject(timer, INFINITE);
        #else
        usleep(delay_milliseconds *1000); // Sleep for DELAY milliseconds
        #endif
        
        #ifdef WIN32// check for input from the keyboard
        if (_kbhit()) {
            userInput = _getch();
        }
        #else
        userInput = _getch();
        #endif
    }
    //cleanup
    #ifdef WIN32
    CloseHandle(timer);
    #else
    endwin(); // End ncurses
    #endif
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return 0;
}
