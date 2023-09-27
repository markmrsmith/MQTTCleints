@echo off
setlocal enabledelayedexpansion

REM Number of publishers to run
set num_publishers=100

REM Path to the MQTT publisher executable
set publisher_executable=MQTTClientPublisher.exe

REM MQTT broker address and port
REM set broker=tcp://broker.emqx.io:1883

REM MQTT client ID prefix (customize as needed)
REM set client_id_prefix=Publisher

REM MQTT topic
REM set topic=temperature

REM Delay between starting each publisher (in milliseconds)
set delay_ms=1000

REM Loop to start publishers
for /l %%i in (1,1,%num_publishers%) do (
    start "" /b %publisher_executable% %topic% %delay_ms%
    rem ping -n %delay_ms% 127.0.0.1 >nul
)

echo Started %num_publishers% publishers.

endlocal
