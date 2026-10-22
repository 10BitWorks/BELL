// heartbeat - Provide a heartbeat status LED.

#include "heartbeat.h"

uint32_t timer_heartbeat = 0;
uint32_t pin_heartbeat = 0;

void setup_heartbeat(uint32_t pin) {
    pin_heartbeat = pin;
    pinMode(pin_heartbeat, OUTPUT);
    digitalWrite(pin_heartbeat, LED_OFF);
    timer_heartbeat = millis();
}

HeartbeatState currentState = STATE_PULSE1_ON;
unsigned long timer = 0;

// Timing intervals
const long period_pulse = 100;  // Short pulse duration. Was 100
const long period_rest = 700;   // Pause between heartbeats. Was 700

void update_heartbeat(void) {
    unsigned long now = millis();
    switch (currentState) {
            case STATE_PULSE1_ON:
            digitalWrite(pin_heartbeat, LED_ON);
            if (now - timer >= period_pulse) {
            timer = now;
            currentState = STATE_PULSE1_OFF;
        }
        break;

        case STATE_PULSE1_OFF:
            digitalWrite(pin_heartbeat, LED_OFF);
            if (now - timer >= period_pulse) {
            timer = now;
            currentState = STATE_PULSE2_ON;
        }
        break;

        case STATE_PULSE2_ON:
            digitalWrite(pin_heartbeat, LED_ON);
            if (now - timer >= period_pulse) {
            timer = now;
            currentState = STATE_PAUSE;
        }
        break;

        case STATE_PAUSE:
            digitalWrite(pin_heartbeat, LED_OFF);
            if (now - timer >= period_rest) {
            timer = now;
            currentState = STATE_PULSE1_ON;
        }
        break;
    }    
}