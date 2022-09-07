#include <ESP32_FSBrowser.h>

WebServer *_server;

void FS_init(WebServer *server){
  _server = server;
if (FORMAT_FILESYSTEM) FILESYSTEM.format();
  FILESYSTEM.begin();
  {
      File root = FILESYSTEM.open("/");
     
      File file = root.openNextFile();
      while(file){
          String fileName = file.name();
           size_t fileSize = file.size();
           Serial.printf("\tFS_File: %s, size: %s\n", fileName.c_str(), formatBytes(fileSize).c_str());
           file = root.openNextFile();
      }
     Serial.printf("FS_init INIT \n");
  }
}

//format bytes
String formatBytes(size_t bytes) {
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  } else {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

String getContentType(String filename) {
  if ((*_server).hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}

bool exists(String path){
  bool yes = false;
  File file = FILESYSTEM.open(path, "r");
  if(!file.isDirectory()){
    yes = true;
  }
  file.close();
  return yes;
}

bool handleFileRead(String path) {
  //// Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) {
    path += "index.htm";
  }
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (exists(pathWithGz) || exists(path)) {
    if (exists(pathWithGz)) {
      path += ".gz";
    }
    File file = FILESYSTEM.open(path, "r");
    (*_server).streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void handleFileUpload() {
  File fsUploadFile;
  if ((*_server).uri() != "/edit") {
    return;
  }
  HTTPUpload& upload = (*_server).upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) {
      filename = "/" + filename;
    }
    //// Serial.print("handleFileUpload Name: "); //// Serial.println(filename);
    fsUploadFile = FILESYSTEM.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    ////// Serial.print("handleFileUpload Data: "); //// Serial.println(upload.currentSize);
    if (fsUploadFile) {
      fsUploadFile.write(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile) {
      fsUploadFile.close();
    }
    //// Serial.print("handleFileUpload Size: "); //// Serial.println(upload.totalSize);
  }
}

void handleFileDelete() {
  if ((*_server).args() == 0) {
    return (*_server).send(500, "text/plain", "BAD ARGS");
  }
  String path = (*_server).arg(0);
  //// Serial.println("handleFileDelete: " + path);
  if (path == "/") {
    return (*_server).send(500, "text/plain", "BAD PATH");
  }
  if (!exists(path)) {
    return (*_server).send(404, "text/plain", "FileNotFound");
  }
  FILESYSTEM.remove(path);
  (*_server).send(200, "text/plain", "");
  path = String();
}

void handleFileCreate() {
  if ((*_server).args() == 0) {
    return (*_server).send(500, "text/plain", "BAD ARGS");
  }
  String path = (*_server).arg(0);
  //// Serial.println("handleFileCreate: " + path);
  if (path == "/") {
    return (*_server).send(500, "text/plain", "BAD PATH");
  }
  if (exists(path)) {
    return (*_server).send(500, "text/plain", "FILE EXISTS");
  }
  File file = FILESYSTEM.open(path, "w");
  if (file) {
    file.close();
  } else {
    return (*_server).send(500, "text/plain", "CREATE FAILED");
  }
  (*_server).send(200, "text/plain", "");
  path = String();
}

void handleFileList() {
  if (!(*_server).hasArg("dir")) {
    (*_server).send(500, "text/plain", "BAD ARGS");
    return;
  }

  String path = (*_server).arg("dir");
  //// Serial.println("handleFileList: " + path);


  File root = FILESYSTEM.open(path);
  path = String();

  String output = "[";
  if(root.isDirectory()){
      File file = root.openNextFile();
      while(file){
          if (output != "[") {
            output += ',';
          }
          output += "{\"type\":\"";
          output += (file.isDirectory()) ? "dir" : "file";
          output += "\",\"name\":\"";
          output += String(file.name());
          output += "\"}";
          file = root.openNextFile();
      }
  }
  output += "]";
  (*_server).send(200, "text/json", output);
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