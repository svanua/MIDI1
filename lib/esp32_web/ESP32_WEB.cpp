
#include <ESP32_WEB.h>
#include <ArduinoJson.h>
#include <ESP32_HTTP.h>



WebServer server(80);
StaticJsonDocument<200U> JSON_WiFi_Settings;
TaskHandle_t xHandle_TASK_ESP32_WEB;

void ESP32_WEB_init(){
    FS_init(&server);
    ESP32_HTTP_init();    
     // прочитать фаил конфигурации Wifi
     File File_json = FILESYSTEM.open("/wifi_config.json", "r");
     DeserializationError error = deserializeJson(JSON_WiFi_Settings, File_json);
     wifi_mode_t mode = strstr(JSON_WiFi_Settings["WiFi_mode"].as<String>().c_str(),"AP") ? WIFI_AP : WIFI_STA;
     if ( mode == WIFI_STA){
        WiFi.mode(mode);
        WiFi.begin(JSON_WiFi_Settings["WiFi_STA_ssid"].as<String>().c_str(), JSON_WiFi_Settings["WiFi_STA_password"].as<String>().c_str());
        while (WiFi.status() != WL_CONNECTED) {
            Serial.println("[wifi] wait module connected...");
            vTaskDelay(pdMS_TO_TICKS(500));
        }         
        Serial.printf("[wifi] connection OK! \n go to ip %s",  WiFi.localIP().toString().c_str());
     }
     else {
        WiFi.softAP(JSON_WiFi_Settings["WiFi_AP_ssid"].as<String>().c_str(), JSON_WiFi_Settings["WiFi_AP_password"].as<String>().c_str());
        Serial.println("[WiFi] AP IP address: "+WiFi.softAPIP().toString());//наш IP
        while (WiFi.status() != WL_CONNECTED) {
            Serial.println("wait wifi client...");
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        //Serial.printf("[wifi] connection OK! \n client ip %s",  WiFi.softAPIP().toString().c_str());
     }
    server.begin();
     xTaskCreatePinnedToCore(
        ESP32_WEB_Thread,
        "ESP32_WEB_Thread",
        configMINIMAL_STACK_SIZE * 5,
        NULL,
        20,
        &xHandle_TASK_ESP32_WEB,
        1
      );
    #ifdef SHUTDOWN_NOCLIENT
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
            #ifdef CONST_TIME_WIFI_OFF
                uint32_t Time_WIFI_off = millis()+CONST_TIME_WIFI_OFF;
            #endif
            #ifndef
            uint32_t Time_WIFI_off  =  millis()+JSON_WiFi_Settings["WiFi_wait_connect"].as<uin32_t>()*1000;
            #endif
            if (Time_WIFI_off < millis())  {
            Serial.println("[WiFi] WIFI MODULE OFF");
            WiFi.mode(WIFI_OFF);
            break;
        }
    #endif

}
void ESP32_WEB_Thread(void *pvParameters){
    while(1){
       server.handleClient();
       //webSocket.loop();
        vTaskDelay(10);
    }
}
