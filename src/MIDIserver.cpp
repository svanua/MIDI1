
#include <MIDIServer.h>
#include <MIDI.h>



 QueueHandle_t Q_MIDI_IN=xQueueCreate( 15, sizeof(MES_MIDI ) ); // Queue Input mes;          

    uint8_t data1_out, data2_out;

  QueueHandle_t Q_MIDI_OUT=xQueueCreate( 15, sizeof(MES_MIDI ) ); // Queue OUTPUT mes;  

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI_2);

void MIDIserver (void *parametrs)
{
        //MIDI.begin(MIDI_CHANNEL_OMNI);                      
        MIDI_2.begin(10);                   // Launch MIDI and listen to channel 10
        MIDI_2.turnThruOff();
        uint32_t Time_note = 0;
           
        MES_MIDI Message_in, Message_out ;

        while (1)
        {
            
                            /* code */
                    if (MIDI_2.read())                    // If we have received a message
                    {    // если есть данные на входе 
                    Message_in.MTYPE=MIDI_2.getType();
                    Message_in.Data1=MIDI_2.getData1();
                    Message_in.Data2=MIDI_2.getData2();
                  
                    //Serial.println ( Message_in.MTYPE);
                    //Serial.println ( Message_in.Data1);
                    //Serial.println (Message_in.Data2);

                        // send mes in Q_IN
                            if (Q_MIDI_IN!=0){
                            xQueueSend( Q_MIDI_IN, &Message_in, pdMS_TO_TICKS(2));
                           //Serial.println ("S-Input Midi send to smart");
                             }
                    }

//-------------------------------------------------------------------------
                   if ( xQueueReceive( Q_MIDI_OUT, &Message_out,1 )== pdPASS)
                   {          //  Serial.println("SERVER MIDI OUT Q");
                              //  Serial.println(Message_out.MTYPE);
                               //  Serial.println(Message_out.Data1);
                               //  Serial.println(Message_out.Data2);


                    if (Message_out.MTYPE== midi::NoteOn)
                    MIDI_2.sendNoteOn(Message_out.Data1, Message_out.Data2, 10);
                    if (Message_out.MTYPE== midi::NoteOff)
                    MIDI_2.sendNoteOn(Message_out.Data1, Message_out.Data2, 10);
                   }
                        vTaskDelay (1);
        
        }


}