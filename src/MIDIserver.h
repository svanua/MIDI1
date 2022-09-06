#pragma once
#ifndef MIDIServer_h
#define MIDIServer_h  
#include <Arduino.h>
#include <MIDI.h>


// Define your transport
//extern MIDI_NAMESPACE::SerialMIDI<HardwareSerial>serialMIDI ;
// Define the MIDI interface
//extern MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>MIDI;


      struct MES_MIDI // MIDI Mes struct
    {
      midi::MidiType MTYPE;
      
      byte Data1,Data2,Data3,Data4;
      uint8_t Ch;

      /* data */
    } ;
extern QueueHandle_t Q_MIDI_IN;             // заголовок очереди входа миди
extern QueueHandle_t Q_MIDI_OUT;

void MIDIserver (void *parametrs);
// Define your transport
// Define your transport

// code def

#endif