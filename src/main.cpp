#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include "version.h"

// Include config file if it exists, otherwise use example values
#ifdef CONFIG_H
#include "config.h"
#else
#warning "config.h not found - using defaults. Copy config.h.example to config.h and configure your settings!"
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"
#define DEVICE_HOSTNAME "GamerBell"
#define OTA_PASSWORD "admin"
#endif

// WiFi credentials from config
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// Device configuration
const char* hostname = DEVICE_HOSTNAME;

void setupWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(hostname);
    WiFi.begin(ssid, password);
    
    // Wait for connection with timeout
    int attempts = 0;
    const int maxAttempts = 30; // 15 seconds timeout
    
    while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nWiFi connection failed!");
        Serial.println("Please check your credentials in config.h");
    }
}

void setupOTA() {
    // Only setup OTA if WiFi is connected
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Skipping OTA setup - WiFi not connected");
        return;
    }
    
    ArduinoOTA.setHostname(hostname);
    ArduinoOTA.setPassword(OTA_PASSWORD);
    
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
