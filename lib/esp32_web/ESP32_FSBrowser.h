#pragma once
#include <Arduino.h>
#include <WebServer.h>

#define FORMAT_FILESYSTEM false

#define FILESYSTEM SPIFFS

#if FILESYSTEM == FFat
#include <FFat.h>
#endif
#if FILESYSTEM == SPIFFS
#include <SPIFFS.h>
#endif

extern  WebServer *_server;

void FS_init(WebServer *server);

String formatBytes(size_t bytes);
String getContentType(String filename);
bool exists(String path);

bool handleFileRead(String path);
void handleFileDelete();
void handleFileCreate();
void handleFileList();

bool FS_Write_file(String filename,String json_str);