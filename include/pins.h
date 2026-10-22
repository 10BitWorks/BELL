#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

#if defined(IS_ESP8266_D1_MINI_BOARD)
    // Left Side Pins
    #define PIN_IO_RST       // RST                     - pull LOW to reset
    #define PIN_IO_A0        // A0   / ADC0             - only pin that supports analog
    #define PIN_IO_D0   (16) // D0   / GPIO16 / WAKE    - pin is high at BOOT
    #define PIN_IO_D5   (14) // D5   / GPIO14 / SCLK
    #define PIN_IO_D6   (12) // D6   / GPIO12 / MISO
    #define PIN_IO_D7   (13) // D7   / GPIO13 / MOSI
    #define PIN_IO_D8   (15) // D8   / GPIO15 / CS      - boot failure if pulled HIGH
                             // 3.3V
    // Right Side Pins
    #define PIN_IO_TX   (1)  // TX   / GPIO1 / TX       - pin is high at BOOT, boot failure if pulled LOW
    #define PIN_IO_RX   (3)  // RX   / GPIO3 / RX       - pin is high at BOOT
    #define PIN_IO_D1   (5)  // D1   / GPIO5 / SCL
    #define PIN_IO_D2   (4)  // D2   / GPIO4 / SDA
    #define PIN_IO_D3   (0)  // D3   / GPIO0 / FLASH    - boot failure if pulled LOW
    #define PIN_IO_D4   (2)  // D4   / GPIO2 / LED      - pin is high on BOOT, boot failure if pulled LOW
                             // G    / GND
                             // 5V

    #define LED_OFF   (HIGH)
    #define LED_ON    (LOW)

#elif defined(IS_ESP8266_NODE_NCU_BOARD)
    // Left Side Pins
    #define PIN_IO_A0        // A0   / ADC0             - only pin that supports analog
                             // RSV  / RESERVED
                             // RSV  / RESERVED
                             // SD3  / GPIO10    / SDD3
                             // SD2  / GPIO9     / SDD2
                             // SD1  / MOSI      / SDD1
                             // CMD  / CS        / SDCMD
                             // SD0  / MISO      / SDD0
                             // CLK  / SCLK      / SDCLK
                             // GND
                             // 3V3
                             // EN
     #define PIN_IO_RST      // RST                      - pull LOW to reset
                             // GND
                             // Vin

    // Right Side Pins
    #define PIN_IO_D0   (16) // D0   / GPIO16 / WAKE    - pin is high at BOOT
    #define PIN_IO_D1   (5)  // D1   / GPIO5  / SCL
    #define PIN_IO_D2   (4)  // D2   / GPIO4  / SDA
    #define PIN_IO_D3   (0)  // D3   / GPIO0  / FLASH    - boot failure if pulled LOW
    #define PIN_IO_D4   (2)  // D4   / GPIO2  / LED      - pin is high on BOOT, boot failure if pulled LOW
                             // 3V3
                             // GND
    #define PIN_IO_D5   (14) // D5   / GPIO14 / SCLK
    #define PIN_IO_D6   (12) // D6   / GPIO12 / MISO
    #define PIN_IO_D7   (13) // D7   / GPIO13 / MOSI
    #define PIN_IO_D8   (15) // D8   / GPIO15 / CS      - boot failure if pulled HIGH
    #define PIN_IO_RX   (3)  // RX   / GPIO3  / RX      - pin is high at BOOT
    #define PIN_IO_TX   (1)  // TX   / GPIO1  / TX      - pin is high at BOOT, boot failure if pulled LOW

    #define LED_OFF   (HIGH)
    #define LED_ON    (LOW)

    #elif defined(IS_ESP32_BOARD)

    // Left Side Pins
                             // EN
                             // VP
                             // VN
                             // D34
                             // D35
                             // D32
                             // D33
                             // D25
                             // D26
                             // D27
                             // D14
                             // D12
                             // D13
                             // GND
                             // Vin

    // Right Side Pins
                             // D23
                             // D22
                             // TX0
                             // RX0
                             // D21
                             // D19
                             // D18
                             // D5
                             // TX2
                             // RX2
                             // D4
                             // D2
                             // D15
                             // GND
                             // 3V3
    
    
    #endif

void setup_pins(void);

#endif