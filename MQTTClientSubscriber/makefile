CC = gcc
CFLAGS = -Wall -std=c++11
LIBS = -lpaho-mqtt3c -lncurses
# Additional include directories
INCLUDE_DIRS = -I../paho.mqtt.c/src/ -I/usr/local/include
LIB_DIRS = -L/usr/local/lib
SRC = MQTTClientSubscriber.cpp
TARGET = MQTTClientSubscriber

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(SRC) -o $(TARGET) $(LIB_DIRS) $(LIBS)

clean:
	rm -f $(TARGET)
