import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("living_room_temperature_my_house")

def on_message(client, userdata, msg):
    temperature = int(msg.payload)
    fan_state = "on" if temperature >= 70 else "off"
    print(f"Received temperature: {temperature} degrees - fan {fan_state}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("broker.emqx.io", 1883, 60)

client.loop_forever()
client.disconnect()