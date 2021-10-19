#include "Arduino.h"
#include "HTTPPostClient.h"
#include "WiFi.h"
#include "FS.h"
#include "SPIFFS.h"

#define WIFI_SSID           "XXXXXXXXXXXX" // Add your wifi ssid (wifi name)
#define WIFI_PASSWORD       "XXXXXXXXXXXX" // Add your wifi password

HTTPPostClient client;
File file;

void setup() {
  IPAddress ip(10,12,181,117); // Local IP address of the http server
  
  // Initialize Serial
  Serial.begin(115200);

  // Connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Establishing connection to WiFi..");
    delay(1000);
  }
  Serial.println("Connected to WiFi");

  // Initilalize SPIFFS
  Serial.println(SPIFFS.begin(true) ? "SPIFFS Mounted successfully" : "SPIFFS Mount Failed");

  // Open a file for writing (the file will be created if it doesn't exist)
  Serial.println((file = SPIFFS.open("/data.txt", "w")) ? "File successfully opened for Writing" : "File opening failed");

  // Write something to the file
  file.println("Hello, World");

  // Close the file => REALLY IMPORTANT !
  file.close();

  // Send the content of the file via POST request
  client.postFile("/data.txt", "10.12.181.117", 5000, "/");
  
  // or
  // client.postFile("/data.txt", ip, 5000, "/");
  // or
  // file = SPIFFS.open("/data.txt", "r");
  // client.postFile(file, "10.12.181.117", 5000, "/");
  // or
  // client.postFile(file, ip, 5000, "/");
}

void loop() {
  // put your main code here, to run repeatedly:

}
