#ifndef HEARTBEAT_H
#define HEARTBEAT_H

    #include <Arduino.h>
    #include "pins.h"
    
    enum HeartbeatState {
        STATE_PULSE1_ON,
        STATE_PULSE1_OFF,
        STATE_PULSE2_ON,
        STATE_PAUSE
    };

    void setup_heartbeat(uint32_t pin);
    void update_heartbeat(void);

#endif