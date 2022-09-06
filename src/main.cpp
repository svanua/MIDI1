#include <Arduino.h>
#include <MIDIServer.h>
//#include <MIDI.h>
#include <MIDI_SMART.h>


// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.
  


  TaskHandle_t xHandle_MidiServer          =NULL; // Task MIDI IN/OUT

  TaskHandle_t xHandle_MIDI_SMART          =NULL; // SMART MIDI EVENT
// Chizhik commentariy
void setup()
{
     Serial.begin (115200);



      xTaskCreatePinnedToCore(
        MIDIserver
        ,  "T_MIDIServer"
        ,  1024+(512*2)  // Stack size
        ,  NULL
        ,  2 // Priority
        ,  &xHandle_MidiServer
        ,  0);
   
     xTaskCreatePinnedToCore(
        MIDI_SMART
        ,  "T_MIDI_SMART"
        ,  1024+(512*2)  // Stack size
        ,  NULL
        ,  2 // Priority
        ,  &xHandle_MIDI_SMART
        ,  0);
     
}

void loop()
{
    
}