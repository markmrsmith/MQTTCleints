#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>
#ifdef WIN32

#else
#include <getopt.h>  // For command-line argument parsing
#endif
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

#define QOS         2
#define USERNAME    "emqx"
#define PASWORD    "public"
#define DEFAULT_TOPIC       "living_room_temperature_my_house"
#define DEFAULT_DELAY  1000




int main(int argc, char* argv[]) {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer; //default options for MQTT client
    int rc;
    char userInput = 'c';
    int prev_temperature = rand() % 100;  //pick a randmon starting temperature 
    // Replace with your actual temperature reading logic

    char * topic = (char*)DEFAULT_TOPIC;
    int delay_microseconds = DEFAULT_DELAY;
    //process input arguments
    if (argc < 2)
    {
        printf("Usage  MQTTClientPublisher topic delay\n;");
        
    }
    else
    {
        if (argc >= 2)
        {
            topic = argv[1];
        }
        if (argc >= 3)
        {
            delay_microseconds = atoi(argv[2]);
        }
        printf("Usage  MQTTClientPublisher %s %d\n;", topic, delay_microseconds);
    }





    // create cleint and connection
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = USERNAME;
    conn_opts.password =PASWORD;
    
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect to the MQTT broker, return code %d\n", rc);
        exit(-1);
    }

    printf("Press 'q' to quit...\r\n");

    #ifdef WIN32
    HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
    LARGE_INTEGER dueTime = { 0,0 };
    dueTime.QuadPart = -((LONGLONG)delay_microseconds * 10000LL); // Convert milliseconds to 100-nanosecond intervals
    #else 
    // Initialize ncurses
    initscr(); 
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    #endif
    

    while (userInput != 'q' && userInput != 'Q') {
        char payload[20];
        int temperature = prev_temperature + (rand() % 5)- (rand() % 5); // Replace with your actual temperature reading logic
        // for now use previouse temperature +- 5 to make it more resoundable
        // a better approx would a ramp up to relatively stable vaule
        snprintf(payload, sizeof(payload), "%d", temperature);
        MQTTClient_message pubmsg = MQTTClient_message_initializer;
        pubmsg.payload = payload;
        pubmsg.payloadlen = strlen(payload);
        pubmsg.qos = QOS;
        MQTTClient_publishMessage(client, topic, &pubmsg, NULL);
        printf("Send %d to topic %s\r\n", temperature, topic);
        fflush(stdout);
        prev_temperature = temperature;
        #ifdef WIN32
        // Use the timer to create a delay
        SetWaitableTimer(timer, &dueTime, 0, NULL, NULL, FALSE);
        WaitForSingleObject(timer, INFINITE);
        #else
        usleep(delay_microseconds*1000); // Sleep for DELAY milliseconds
        #endif
        
        #ifdef WIN32
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
