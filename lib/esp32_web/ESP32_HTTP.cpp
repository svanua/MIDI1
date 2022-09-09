#include <ESP32_HTTP.h>

#define FILE_SETTING_NAME "/setting.json"

void ESP32_HTTP_init(){
    
  (*_server).onNotFound(handleNotFound);
  (*_server).on("/", HTTP_GET, []() {
      if (!handleFileRead("/index.html")) {//http://192.168.4.1/
      (*_server).send(404, "text/plain", "FileNotFound");
      }
  });

  (*_server).on("/list_profiles",HTTP_GET, []() {
    (*_server).send(200,"text/plain", FS_Read_midi_list());
  });

   (*_server).on("/get_profile", HTTP_GET, []() {
    
    // for (size_t i = 0; i <  (*_server).args(); i++)
    // {
    //   Serial.printf("GetProfile Arg[%d]=%s",i,(*_server).arg(i).c_str());
    // }
    String File_text = FS_Read_file("/"+(*_server).arg(0));
    if ( File_text !="") (*_server).send(200,"text/plain", File_text);
    else {handleNotFound(); }
   
  });

  (*_server).on("/save_profile", HTTP_POST, []() {
    if (FS_Write_file(FILE_SETTING_NAME, (*_server).arg(0))) 
    {
        (*_server).send(200, "text/plain", String(FILE_SETTING_NAME) + String("save to flash"));
    }
    else {(*_server).send(404, "text/plain", String("Error write file to Flash!")+String(FILE_SETTING_NAME));}
  });


}

String FS_Read_file(String path){
static String result = "{\n}";
 Serial.printf("\nRead File to path: %s\n",path.c_str());
     // Открываем файл для чтения
    File File_json = FILESYSTEM.open(path, FILE_READ,false);    // Открываем файл для чтения
    if (File_json.size() > 1024){  Serial.println("File is big!"); return result; }        // Проверяем размер файла, будем использовать файл размером меньше 1024 байта
    if (File_json)  result = File_json.readString();    
    File_json.close();
    Serial.println(result);
    return result;
}

bool FS_Write_file(String filename,String json_str)
{ 
 File file = FILESYSTEM.open(filename, FILE_WRITE,false);
 if(!file) { Serial.println("[FLASH] Error open file to write"); return false;}
 else { 
      try
      {
        file.print(json_str.c_str());
      }
      catch(const std::exception& e)
      {
      Serial.println("[FLASH] Write" + filename);
      }  
  }
 file.close();

 return true;
}

String FS_Read_midi_list(){
  String result="profile_default.json_midi\n";
File root = FILESYSTEM.open("/");
      File file = root.openNextFile();
      while(file){
          String fileName = file.name();
          
          if ((strstr(fileName.c_str(),".json_midi") != NULL) && 
              (0!=strcmp(fileName.c_str(),"profile_default.json_midi"))) 
            {
                result += fileName+"\n";
                Serial.printf("\tFS_File: %s\n", fileName.c_str());
            }
            else {
               //Serial.printf("\tFS_File: %s, extension: other\n", fileName.c_str());
            }
           file = root.openNextFile();
      }
      return result;
}