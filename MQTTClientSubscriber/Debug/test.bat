@echo off
setlocal enabledelayedexpansion

REM Number of subscribers to run
set num_subscribers=100

REM Path to the MQTT subscriber executable
set subscriber_executable=MQTTClientSubscriber.exe

REM MQTT broker address and port
REM set broker=tcp://broker.emqx.io:1883

REM MQTT client ID prefix (customize as needed)
REM set client_id_prefix=subscriber

REM MQTT topic
REM set topic=temperature

REM Delay between starting each subscriber (in milliseconds)
set delay_ms=1000

REM Loop to start subscribers
for /l %%i in (1,1,%num_subscribers%) do (
    start "" /b %subscriber_executable% %topic%
    rem ping -n %delay_ms% 127.0.0.1 >nul
)

echo Started %num_subscribers% subscribers.

endlocal
