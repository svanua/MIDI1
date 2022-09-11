#pragma once    
#include <ESP32_FSBrowser.h>

const String p_note_json_def = "{\"Name_pad_input\": \"default_p1\",\"Note\": 1,\"Vel_note_min\": 0,\"Mapping_THRUE\": 0,\"Lenght_pad_min\": 0,\"Note_common\": 0,\"Note_common_vel\": 0,\"Vel1\": 0,\"Note1\": 0,\"Note1_vel1\": 0,\"Ch_n1\": 0,\"Lenght_Note_1\": 0,\"Vel2\": 0,\"Note2\": 0,\"Note2_vel2\": 0,\"Ch_n2\": 0,\"Lenght_Note_2\": 0,\"Vel3\": 0,\"Note3\": 0,\"Note3_vel3\": 0,\"Ch_n3\": 0,\"Lenght_Note_3\": 0,\"Vel4\": 0,\"Note4\": 0,\"Note4_vel4\": 0,\"Ch_n4\": 0,\"Lenght_Note_4\": 0}";

void ESP32_HTTP_init();

String FS_Read_file(String path);
bool FS_Write_file(String filename,String json_str);
bool FS_Create_profile(String filename);
String FS_Read_midi_list();
