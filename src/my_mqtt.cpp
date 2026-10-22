// my_mqtt - Establish and maintain an MQTT connection to a broker, and subscribe to a topic to control the bell.

#include "my_mqtt.h"

//static const bool VERBOSE_INFO = true;
//static const bool VERBOSE_WARN = true;
//static const bool VERBOSE_ERR = true;
static const bool VERBOSE_DEBUG = true;

#if defined(LOCATION_10BITWORKS)
    //const char* mqtt_server = "10.7.1.81";    // kiln pi
    const char* mqtt_server = "10.7.1.106";     // proxmox server
#elif defined(LOCATION_HOME)
    const char* mqtt_server = "192.168.1.130";
#endif
const char* mqtt_topic = "bell";

WiFiClient espClient;
PubSubClient client(espClient);

uint32_t tokens[MAX_TOKEN_COUNT];
size_t token_count = 0;
uint32_t token_index = 0;

bool my_mqtt_isDirty = false;
bool isSequencing = false;
uint32_t timer_bell = 0;
uint32_t pin_bell = 0;

// Function to handle incoming MQTT messages
void callback_old(char* topic, byte* payload, unsigned int length) {

    String message = "";
    for (uint32_t i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println(message);

    // Toggle the pin controlling the bell based on the message
    if (message == "1") {
        digitalWrite(pin_bell, HIGH); // Set pin high to energize relay and ring the bell.
        timer_bell = millis() + 100;
    } else if (message == "0") {
        digitalWrite(pin_bell, LOW);  // Set pin low to release the relay and silence the bell.
        timer_bell = 0;
    }
}


void callback(char* topic, byte* payload, unsigned int length) {

    // Convert the payload to a null-terminated char array buffer for easier processing.
    char buffer[length + 1];
    memcpy(buffer, payload, length);
    buffer[length] = '\0';
    if(VERBOSE_DEBUG) printf("As string: %s\n", buffer); 

    // Get the number of possible tokens contained in the buffer.
    uint32_t max_token_count = count_char(buffer, DELIMETER) + 1;
    if(VERBOSE_DEBUG) printf("%s: %u\n", "max_token_count", max_token_count);

    // Validate the buffer and parse it into an array of unsigned integers if valid.
    if(is_csv_valid(buffer, DELIMETER)) {
        token_count = parse_csv_into_integer_array(buffer, DELIMETER, tokens, MAX_TOKEN_COUNT);
        if(VERBOSE_DEBUG) printf("%s: %u\n", "token_count", token_count);
        if(VERBOSE_DEBUG) report_array_uint32(tokens, token_count);
        
        my_mqtt_isDirty = true;
        token_index = 0;
    }

}

void reconnect() {
    while (!client.connected()) {
        if (client.connect(HOSTNAME)) {
            // Subscribe to the topic when connected
            client.subscribe(mqtt_topic);
        } else {
            delay(5000);
        }
    }
}

void setup_my_mqtt(uint32_t pin) {
    pin_bell = pin;
    pinMode(pin_bell, OUTPUT);
    digitalWrite(pin_bell, LOW);

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    Serial.println("MQTT Broker IP: " + String(mqtt_server));
    Serial.println("MQTT Topic: bell, Payload: A csv list of durations and pauses in milliseconds.");

}

bool update_my_mqtt(void) {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    
    if(my_mqtt_isDirty) { 

        if(millis() >= timer_bell) {
            // Timer has elapsed
            if(token_index < token_count) {
                printf("Processing token index %u: %u ms, %s\n", token_index, tokens[token_index], (token_index % 2) ? "pause" : "ring");
                isSequencing = true;
                timer_bell = millis() + tokens[token_index++];
            } else {
                // All tokens processed, reset index, state, and timer.
                token_index = 0;
                isSequencing = false;
                timer_bell = 0;

                my_mqtt_isDirty = false;
            }
        }

        #ifdef BUZZER_FREQUENCY
            if(token_index % 2 == 0) {
                noTone(pin_bell);   // Even index: pause (silence bell)
            } else {
                tone(pin_bell, BUZZER_FREQUENCY); // Odd index: ring bell
            }
        #else
            if(token_index % 2 == 0) {
                digitalWrite(pin_bell, LOW);  // Even index: pause (silence bell)
            } else {
                digitalWrite(pin_bell, HIGH); // Odd index: ring bell
            }
        #endif
        

    } else {
        digitalWrite(pin_bell, LOW);  // Ensure bell is silent when not processing tokens.
    }

    return true;
}