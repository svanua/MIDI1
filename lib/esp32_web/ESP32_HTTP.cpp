#include <ESP32_HTTP.h>

#define FILE_SETTING_NAME "/setting.json"

void ESP32_HTTP_init(){
    
  (*_server).onNotFound(handleNotFound);
  (*_server).on("/", HTTP_GET, []() {
      if (!handleFileRead("/index.html")) {//http://192.168.4.1/
      (*_server).send(404, "text/plain", "FileNotFound");
      }
  });
   (*_server).on("/get_MIDI_info", HTTP_GET, []() {
        (*_server).send(200,"text/plain", handlGetMIDIInfo());
  });

  (*_server).on("/save_settings", HTTP_POST, []() {
    if (FS_Write_file(FILE_SETTING_NAME, (*_server).arg(0))) 
    {
        (*_server).send(200, "text/plain", String(FILE_SETTING_NAME) + String("save to flash"));
    }
    else {(*_server).send(404, "text/plain", String("Error write file to Flash!")+String(FILE_SETTING_NAME));}
  });


}


void handleNotFound() {
  if (!handleFileRead((*_server).uri())) {
       String message = "File Not Found\n\n";
        message += "URI: ";
        message += (*_server).uri();
        message += "\nMethod: ";
        message += ((*_server).method() == HTTP_GET) ? "GET" : "POST";
        message += "\nArguments: ";
        message += (*_server).args();
        message += "\n";
        for (uint8_t i = 0; i < (*_server).args(); i++) {
          message += " " + (*_server).argName(i) + ": " + (*_server).arg(i) + "\n";
        }
        (*_server).send(404, "text/plain", message);
    }
}

String handlGetMIDIInfo(){
    return "{\"MIDIInfo\":null}";
}