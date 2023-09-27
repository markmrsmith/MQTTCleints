# MQTTClient

The following are a set of MQTT clients both publishers and subscribers for both Windows and Linux.

## Publisher Client

There is a single MQTT client publisher written in C but can be created on both Windows and Linux.
[MQTT Client Publisher](MQTTClientPublisher/README.md)

## Subscribers

1. [MQTT Client Subscriber in C](MQTTClientSubscriber/README.md)
2. [MQTT Client Subscriber in Javascript](MQTTClientSubscriberJavascript/README.md)
3. [MQTT Client Subscriber Javascript With HTML](MQTTClientSubscriberJavascriptWithHTML/README.md)
4. [MQTT Client Subscriber in Python](MQTTClientSubscriberPython/README.md)

## To build in Windows

```windows_build.bat```
**complies both the c client publisher and subscriber
** may need to update the path to your complier

## To run in Windows

```windows_run.bat```
** complies both the c client publisher and subscriber

## To build in Linux

** assumes you have gcc installed

`
git submodule update --recursive --remote
rm -rf ./MQTTClientPublisher/MQTTClientPublisher
rm -rf ./MQTTClientSubscriber/MQTTClientSubscriber
cd MQTTClientPublisher
make all
cd ../
cd MQTTClientSubscriber
make all
cd ../`

## To run in Linux

```./MQTTClientPublisher/MQTTClientPublisher
./MQTTClientSubscriber/MQTTClientSubscriber
```

## Testing

** Only for Windows

### Will test 100 publishers

```MQTTClientPublisher\Debug\test.bat```

### Will test 100 subscribers

```MQTTClientSubscribers\Debug\test.bat```
