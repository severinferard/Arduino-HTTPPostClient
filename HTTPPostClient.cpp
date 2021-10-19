#include "HTTPPostClient.h"

HTTPPostClient::HTTPPostClient(){}
HTTPPostClient::~HTTPPostClient(){}

int HTTPPostClient::postFile(File f, IPAddress ip, int port, const char *path, const char *contentType)
{
	IPAddress			remoteIP = this->remoteIP();
	uint16_t            bytesread;
	char				buffer[_buffer_size];

	this->connect(ip, port);
	this->printf("POST %s HTTP/1.1\n", path);
	this->printf("Host %u.%u.%u.%u \n", remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3]);
	this->printf("User-Agent: Arduino/1.0\n");
	this->printf("Connection: close\n");
	this->printf("Content-Type: %s\n", contentType);
	this->printf("Content-Length: %d\n", f.size());
	
	bytesread = _buffer_size - 1;
	while (f.available() && bytesread == (_buffer_size - 1))
	{
		bytesread = f.readBytes(buffer, _buffer_size - 1);
		buffer[bytesread] = '\0';
		this->printf("%s", buffer);
   Serial.println(bytesread);
    Serial.printf("%d\n", _buffer_size);
   Serial.println(buffer);
	}

	this->stop();
	return f.size();
}

int HTTPPostClient::postFile(File f, const char *ip, int port, const char *path, const char *contentType)
{
	IPAddress srv((uint32_t)0);
    if(!WiFiGenericClass::hostByName(ip, srv)){
        return 0;
    }
	return postFile(f, srv, port, path, contentType);
}

int HTTPPostClient::postFile(const char *file_path, IPAddress ip, int port, const char *path, const char *contentType)
{
  File f = SPIFFS.open(file_path, "r");
  postFile(f, ip, port, path, contentType);
}

int HTTPPostClient::postFile(const char *file_path, const char *ip, int port, const char *path, const char *contentType)
{
  File f = SPIFFS.open(file_path, "r");
  postFile(f, ip, port, path, contentType);
}

int HTTPPostClient::post(const char *data, IPAddress ip, int port, const char *path, const char *contentType)
{
  IPAddress      remoteIP = this->remoteIP();
  
  this->connect(ip, port);
  this->printf("POST %s HTTP/1.1\n", path);
  this->printf("Host %u.%u.%u.%u \n", remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3]);
  this->printf("User-Agent: Arduino/1.0\n");
  this->printf("Connection: close\n");
  this->printf("Content-Type: %s\n", contentType);
  this->printf("Content-Length: %d\n", strlen(data));
  this->printf("%s");
}

int HTTPPostClient::post(const char *data, const char *ip, int port, const char *path, const char *contentType)
{
  IPAddress srv((uint32_t)0);
    if(!WiFiGenericClass::hostByName(ip, srv)){
        return 0;
    }
    return (post(data, srv, port, path, contentType));
}

void HTTPPostClient::setBufferSize(uint16_t size)
{
	_buffer_size = size;
}
