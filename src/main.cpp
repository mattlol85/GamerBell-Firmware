#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "version.h"

// WiFi credentials - update these for your network
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Device configuration
const char* hostname = "GamerBell";

void setupWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(hostname);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void setupOTA() {
    ArduinoOTA.setHostname(hostname);
    ArduinoOTA.setPassword("admin");  // Change this for security
    
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else {
            type = "filesystem";
        }
        Serial.println("Start updating " + type);
    });
    
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
            Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
            Serial.println("End Failed");
        }
    });
    
    ArduinoOTA.begin();
    Serial.println("OTA ready");
}

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("========================================");
    Serial.println("GamerBell Firmware");
    Serial.print("Version: ");
    Serial.println(VERSION_STRING);
    Serial.print("Git Commit: ");
    Serial.println(GIT_COMMIT);
    Serial.println("========================================");
    
    setupWiFi();
    setupOTA();
    
    Serial.println("Setup complete!");
}

void loop() {
    ArduinoOTA.handle();
    
    // Your main application code goes here
    
    delay(10);
}
