#ifndef MY_MQTT_H
#define MY_MQTT_H

    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <PubSubClient.h>
    #include "pins.h"
    #include "utils.h"

    #define MAX_TOKEN_COUNT    1000
    #define DELIMETER           ','

    //#define BUZZER_FREQUENCY 1000 // Frequency in Hz for the buzzer tone.

    void setup_my_mqtt(uint32_t pin);
    bool update_my_mqtt(void);

#endif