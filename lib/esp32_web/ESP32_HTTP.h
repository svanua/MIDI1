#pragma once    
#include <ESP32_FSBrowser.h>

void ESP32_HTTP_init();

String FS_Read_midi_list();
bool FS_Write_file(String filename,String json_str);
String FS_Read_file(String path);
