#ifndef MY_WIFI_H
#define MY_WIFI_H

    #include <Arduino.h>
    
    #if defined(ARDUINO_ARCH_ESP8266)
        #include <ESP8266WiFi.h>
        // Includes below added for OTA updates.
        #include <ESP8266mDNS.h>
        #include <WiFiUdp.h>
        #include <ArduinoOTA.h>

    #elif defined(ARDUINO_ARCH_ESP32)
        #include <WiFi.h>
    #endif

    void setup_arduino_ota(void);
    void setup_my_wifi();
    void update_my_wifi(void);

#endif