#include "main.h"

void setup() {
  Serial.begin(115200);
  Serial.println("\nSystem Booted");
  
  setup_pins();
  setup_heartbeat(PIN_IO_D4);
  setup_my_wifi();
  setup_my_mqtt(PIN_IO_D1);
}

void loop() {
  ArduinoOTA.handle();
  update_heartbeat();
  update_my_mqtt();
}