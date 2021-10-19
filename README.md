# Arduino-HTTPPostClient

A Beginner friendly Arduino library to help you send HTTP POST requests


## Installation

1. Download the repo as a .zip .
2. In the Arduino IDE, go to `Sketch` > `Include Library` > `Add .ZIP Library..` and select the .zip folder you just downloader.

## Usage

`HTTPPOSTClient` is a wrapper arround the `WiFiClient` from `WiFi.h`. It thus have exactly the same propoerties and functions and can be used for the same applications.

`HTTPPOSTClient` offers two new functions: `post()` and `postFile()`.
Those functions allow you to respectively send a string of text and the content of a file to a HTTP Web server via a POST request.

## Examples

```c++
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
```

  ## Functions prototypes
```c++
int post(const char *data, const char *ip, int port, const char *path, const char *contentType = "application/json");
```

```c++
int post(const char *data, IPAddress ip, int port, const char *path, const char *contentType = "application/json");
```

```c++
int postFile(File f, IPAddress ip, int port, const char *path, const char *contentType = "application/json");
```

```c++
int postFile(File f, const char *ip, int port, const char *path, const char *contentType = "application/json");
```

```c++
int postFile(const char *file_path, IPAddress ip, int port, const char *path, const char *contentType = "application/json");
```

```c++
int postFile(const char *file_path, const char *ip, int port, const char *path, const char *contentType = "application/json");
```  

```c++
void setBufferSize(uint16_t size);
```
