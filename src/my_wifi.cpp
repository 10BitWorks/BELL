// my_wifi -Establish an maintain a WiFi connection to a network.

#include "my_wifi.h"

#if defined(LOCATION_10BITWORKS)
	const char* ssid = "xblight";
	const char* password = "keykeykey";
#elif defined(LOCATION_HOME)
	const char* ssid = "SpectrumSetup-0D";
	const char* password = "zebraidea804";
#elif defined(LOCATION_WORK)
	const char *ssid = "Pour-More";
	const char* password = "JqM537UFZ9";	
#endif

#if 0
	void setup_my_wifi() {
		
		delay(10);
		Serial.print("Connecting to WiFi ");
		WiFi.begin(ssid, password);
		while (WiFi.status() != WL_CONNECTED) {
			delay(500);
			Serial.print(".");
		}

		Serial.println("\nWiFi connected.");
		Serial.print("ESP IP: ");
		Serial.println(WiFi.localIP());

	}
#else

	void setup_my_wifi() {
		
		delay(10);
		Serial.print("Connecting to WiFi ");
		WiFi.mode(WIFI_STA);
		WiFi.hostname(HOSTNAME);
		WiFi.begin(ssid, password);

		while (WiFi.waitForConnectResult() != WL_CONNECTED) {
			Serial.println("Connection Failed! Rebooting...");
			delay(5000);
			ESP.restart();
		}

		Serial.println("\nWiFi connected.");
		Serial.print("ESP IP: ");
		Serial.println(WiFi.localIP());

		setup_arduino_ota();

	}

	void setup_arduino_ota(void) {
		// Port defaults to 8266
		ArduinoOTA.setPort(8266);

		// Hostname defaults to esp8266-[ChipID]
		ArduinoOTA.setHostname(HOSTNAME);

		// No authentication by default
		//ArduinoOTA.setPassword((const char *)"10bitrocks");

		ArduinoOTA.onStart([]() {
			Serial.println("Start");
		});
		ArduinoOTA.onEnd([]() {
			Serial.println("\nEnd");
		});
		ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
			Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
		});
		ArduinoOTA.onError([](ota_error_t error) {
			Serial.printf("Error[%u]: ", error);
			if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
			else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
			else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
			else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
			else if (error == OTA_END_ERROR) Serial.println("End Failed");
		});
		ArduinoOTA.begin();

		Serial.print("OTA Hostname: ");
		Serial.println(ArduinoOTA.getHostname());
		Serial.println("OTA ready.");

	}
#endif

void update_my_wifi(void) {

}