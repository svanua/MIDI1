#pragma once
#ifndef MIDI_SMART_h
#define MIDI_SMART_h 
#include <Arduino.h>
#include <MIDI.h>

void MIDI_SMART (void *parametrs);
MES_MIDI SMART_EVENT_FINDER (MES_MIDI Smart_mes);
struct Note_Mapping 
            {// input data

            char  Name_pad_input [10];      // name input pad
            u_int8_t Note;                  // number note
            uint8_t Vel_note_min;           // Vel_input_min
            bool Mapping_THRUE;             // Enable mapping 
            uint16_t Lenght_pad_min;        // lenght time ms repeat pads 
            uint32_t Last_Time_on_Note;     // Last time this note on 
            uint8_t Last_Smart_noteOn;      // Last Smart Note On 
            uint8_t Last_Smart_velos;      // Last Smart Note vel 

            
            // maping section
            uint8_t Vel1;                   // Note1 mapping from velositi
            uint8_t Note1;
            uint8_t Note1_vel1;
            uint8_t Ch_n1;
            uint32_t Last_on_Note1;
            uint16_t Lenght_Note_1;        // lenght time ms repeat note1
            

            uint8_t Vel2;                   // Note2 mapping from velositi
            uint8_t Note2;
            uint8_t Note2_vel2;
            uint8_t Ch_n2;
            uint32_t Last_on_Note2;
            uint16_t Lenght_Note_2;        // lenght time ms repeat note1

            uint8_t Vel3;                   // Note3 mapping from velositi
            uint8_t Note3;
            uint8_t Note3_vel3;
            uint8_t Ch_n3;
            uint32_t Last_on_Note3;
            uint16_t Lenght_Note_3;        // lenght time ms repeat note1

            uint8_t Vel4;                   // Note4 mapping from velositi
            uint8_t Note4;
            uint8_t Note4_vel4;
            uint8_t Ch_n4;
            uint32_t Last_on_Note4;
            uint16_t Lenght_Note_4;        // lenght time ms repeat note1

            uint8_t Note_common;            // Note input plus note common 
            uint8_t Note_common_vel;
            uint8_t Ch_common_note; 

};


 


#endif