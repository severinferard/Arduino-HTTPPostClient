#ifndef HTTPPostClient_H_
# define HTTPPostClient_H_

#include "Arduino.h"
#include "WiFi.h"
#include "FS.h"
#include "SPIFFS.h"

class HTTPPostClient: public WiFiClient
{
private:
	uint16_t _buffer_size = 256;
public:
	HTTPPostClient();
	~HTTPPostClient();
	int postFile(File f, IPAddress ip, int port, const char *path, const char *contentType = "application/json");
	int postFile(File f, const char *ip, int port, const char *path, const char *contentType = "application/json");
  int postFile(const char *file_path, IPAddress ip, int port, const char *path, const char *contentType = "application/json");
  int postFile(const char *file_path, const char *ip, int port, const char *path, const char *contentType = "application/json");

  int post(const char *data, const char *ip, int port, const char *path, const char *contentType = "application/json");
  int post(const char *data, IPAddress ip, int port, const char *path, const char *contentType = "application/json");
	void setBufferSize(uint16_t size);
};


#endif
