#include <MIDIServer.h>
#include <MIDI_SMART.h>
//#include <MIDI.h>

MES_MIDI Message_in_Smart , Message_out_Smart;
uint8_t data1,data2;

void MIDI_SMART (void *parametrs)
{    
    while (1)
    {
               if (xQueueReceive( Q_MIDI_IN, &Message_in_Smart,1 )== pdPASS)
                {
                   
                    switch(Message_in_Smart.MTYPE)                                                   // Get the type of the message we caught
                        {      
                                case midi::NoteOn:  
                                    Message_out_Smart= SMART_EVENT_FINDER(Message_in_Smart);
                                 
                                        if (Q_MIDI_OUT!=0)                                          // note on mes send to MIDI
                                            { 
                                                xQueueSend( Q_MIDI_OUT, &Message_out_Smart, pdMS_TO_TICKS(2));
                                                
                                            }
                                        if (Message_out_Smart.Data2 >0 )Message_out_Smart.Data2=0;  // note off mes send to midi
                                       
                                        if (Q_MIDI_OUT!=0)
                                            { 
                                                xQueueSend( Q_MIDI_OUT, &Message_out_Smart, pdMS_TO_TICKS(2));
                                            }
                                break;

                                case midi::SystemReset:
                                //case midi::NoteOff:  SystemReset
                                    // Serial.println ("Smart_ NOTE FF");
                                        data1= Message_in_Smart.Data1; //
                                        // Serial.println(data1);
                                        data2 = Message_in_Smart.Data2; //
                                        // Serial.println(data2);

                                        Message_out_Smart.MTYPE=midi::NoteOn;
                                        //Serial.println (data1);
                                        Message_out_Smart.Data1 = data1;
                                        //Serial.println (data2);
                                        Message_out_Smart.Data2 = 0;

                                        // Serial.println (" Smart send midi");
                                        if (Q_MIDI_OUT!=0)
                                        { xQueueSend( Q_MIDI_OUT, &Message_out_Smart, pdMS_TO_TICKS(2));
                                    //  Serial.println ("Smart_ Send_Q_OUT_off");
                                        }

                                break;
                    }
                }

        vTaskDelay (1);
    }


}

// ARRAY Input pads from drums 
//---------------------------------------------------------------------------
 Note_Mapping  Base_pads []=
            {

            //---------------- Pad 1-----------------------
            { "Kick" ,      //  Name_pad_input
                47,         //  number note     
                10,         //  Vel_input_min 
                1,          //  Enable Maping 
                100,         // Lenght time pad ms
                0,
                0,
                0,

                //---------- Note1------------
                40,         //  Range Note 1 from Vel input min to this val 
                54,         //  Note1 On number 
                127,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note2------------
                60,         //  Range Note 2 from Vel input note1 to this val 
                56,         //  Note2 On number 
                127,        //  Vel max Note1 
                10,         //  Note2 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note3------------
                90,         //  Range Note 3 from Vel input note2 to this val 
                54,         //  Note1 On number 
                127,        //  Vel max Note3 
                10,         //  Note3 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note4------------
                127,        //  Range Note 4 from Vel input note3 to this val 
                65,         //  Note1 On number 
                127,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                // ---------- note common-------------
                88,         // Number common note 
                127,        // Vel max common note
                10          // Chanel common note 
           //---------- end pad 1 -------------------         
             }, 

              //---------------- Pad 2-----------------------
            { "HiHat" ,      //  Name_pad_input
                42,          //  number note     
                10,         //  Vel_input_min 
                1,          //  Enable Maping 
                100,        // Lenght time pad ms
                0,
                0,
                0,                
                //---------- Note1------------
                100,         //  Range Note 1 from Vel input min to this val 
                42,         //  Note1 On number 
                100,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                300,
                //----------Note1 END --------

                //---------- Note2------------
                127,         //  Range Note 2 from Vel input note1 to this val 
                46,         //  Note2 On number 
                90,        //  Vel max Note1 
                10,         //  Note2 send to ch 
                0,
                100,
                //----------Note1 END --------

                //---------- Note3------------
                127,         //  Range Note 3 from Vel input note2 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note3 
                10,         //  Note3 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note4------------
                127,        //  Range Note 4 from Vel input note3 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                // ---------- note common-------------
                0,          // Number common note 
                127,        // Vel max common note
                10          // Chanel common note 
           //---------- end pad 1 -------------------         
         
             },     

                //---------------- Pad 3-----------------------
            { "RIM" ,      //  Name_pad_input
                38,         //  number note     
                3,          //  Vel_input_min 
                1,          //  Enable Maping 
                400,        // Lenght time pad ms
                0,
                0,
                0,
                //---------- Note1------------
                45,         //  Range Note 1 from Vel input min to this val 
                37,         //  Note1 On number 
                100,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                360,
                //----------Note1 END --------

                //---------- Note2------------
                127,         //  Range Note 2 from Vel input note1 to this val 
                38,         //  Note2 On number 
                110,        //  Vel max Note1 
                10,         //  Note2 send to ch 
                0,
                500,
                //----------Note1 END --------

                //---------- Note3------------
                127,         //  Range Note 3 from Vel input note2 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note3 
                10,         //  Note3 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note4------------
                127,        //  Range Note 4 from Vel input note3 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                // ---------- note common-------------
                0,         // Number common note 
                127,        // Vel max common note
                10          // Chanel common note 
           //---------- end pad 3 -------------------         
         
             },    

                //---------------- Pad 4-----------------------
            { "CRASH-1" ,      //  Name_pad_input
                49,         //  number note     
                3,          //  Vel_input_min 
                1,          //  Enable Maping 
                200,        // Lenght time pad ms
                0,
                0,
                0,
                //---------- Note1------------
                90,         //  Range Note 1 from Vel input min to this val 
                51,         //  Note1 On number 
                100,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note2------------
                127,         //  Range Note 2 from Vel input note1 to this val 
                49,         //  Note2 On number 
                120,        //  Vel max Note1 
                10,         //  Note2 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note3------------
                127,         //  Range Note 3 from Vel input note2 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note3 
                10,         //  Note3 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note4------------
                127,        //  Range Note 4 from Vel input note3 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                // ---------- note common-------------
                0,         // Number common note 
                127,        // Vel max common note
                10          // Chanel common note 
           //---------- end pad 4 -------------------         
         
             },    

             //---------------- Pad 5-----------------------
            { "CRASH-2" ,      //  Name_pad_input
                55,         //  number note     
                3,          //  Vel_input_min 
                1,          //  Enable Maping 
                200,        // Lenght time pad ms
                0,
                0,
                0,
                //---------- Note1------------
                90,         //  Range Note 1 from Vel input min to this val 
                51,         //  Note1 On number 
                100,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note2------------
                127,         //  Range Note 2 from Vel input note1 to this val 
                49,         //  Note2 On number 
                120,        //  Vel max Note1 
                10,         //  Note2 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note3------------
                127,         //  Range Note 3 from Vel input note2 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note3 
                10,         //  Note3 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note4------------
                127,        //  Range Note 4 from Vel input note3 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                // ---------- note common-------------
                0,         // Number common note 
                127,        // Vel max common note
                10          // Chanel common note 
           //---------- end pad 5 -------------------         
         
             },    

             //---------------- Pad 6-----------------------
            { "Tom-1" ,      //  Name_pad_input
                77,         //  number note     
                3,          //  Vel_input_min 
                1,          //  Enable Maping 
                200,        // Lenght time pad ms
                0,
                0,
                0,
                //---------- Note1------------
                90,         //  Range Note 1 from Vel input min to this val 
                51,         //  Note1 On number 
                100,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note2------------
                127,         //  Range Note 2 from Vel input note1 to this val 
                49,         //  Note2 On number 
                120,        //  Vel max Note1 
                10,         //  Note2 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note3------------
                127,         //  Range Note 3 from Vel input note2 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note3 
                10,         //  Note3 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note4------------
                127,        //  Range Note 4 from Vel input note3 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                // ---------- note common-------------
                0,         // Number common note 
                127,        // Vel max common note
                10          // Chanel common note 
           //---------- end pad 6 -------------------         
         
             },    

             //---------------- Pad 7-----------------------
            { "Tom-2" ,      //  Name_pad_input
                49,         //  number note     
                3,          //  Vel_input_min 
                1,          //  Enable Maping 
                200,        // Lenght time pad ms
                0,
                0,
                0,
                //---------- Note1------------
                90,         //  Range Note 1 from Vel input min to this val 
                51,         //  Note1 On number 
                100,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note2------------
                127,         //  Range Note 2 from Vel input note1 to this val 
                49,         //  Note2 On number 
                120,        //  Vel max Note1 
                10,         //  Note2 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note3------------
                127,         //  Range Note 3 from Vel input note2 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note3 
                10,         //  Note3 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note4------------
                127,        //  Range Note 4 from Vel input note3 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                // ---------- note common-------------
                0,         // Number common note 
                127,        // Vel max common note
                10          // Chanel common note 
           //---------- end pad 7 -------------------         
         
             },   


             //---------------- Pad 8-----------------------
            { "Tom-3" ,      //  Name_pad_input
                99,         //  number note     
                3,          //  Vel_input_min 
                1,          //  Enable Maping 
                200,        // Lenght time pad ms
                0,
                0,
                0,
                //---------- Note1------------
                90,         //  Range Note 1 from Vel input min to this val 
                51,         //  Note1 On number 
                100,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note2------------
                127,         //  Range Note 2 from Vel input note1 to this val 
                49,         //  Note2 On number 
                120,        //  Vel max Note1 
                10,         //  Note2 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note3------------
                127,         //  Range Note 3 from Vel input note2 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note3 
                10,         //  Note3 send to ch 
                0,
                200,
                //----------Note1 END --------

                //---------- Note4------------
                127,        //  Range Note 4 from Vel input note3 to this val 
                46,         //  Note1 On number 
                127,        //  Vel max Note1 
                10,         //  Note1 send to ch 
                0,
                200,
                //----------Note1 END --------

                // ---------- note common-------------
                0,         // Number common note 
                127,        // Vel max common note
                10          // Chanel common note 
           //---------- end pad 8 -------------------         
         
             }, 



     //----------------------- end pads -------------------------------
            };

//------------------------------------------------------------------------------


MES_MIDI SMART_EVENT_FINDER (MES_MIDI Smart_mes)
{   
            uint8_t Count_pad = sizeof(Base_pads)/sizeof(Base_pads[0]);
            MES_MIDI Out_smart_mes;
            // Input Number note ana velositi
            // Output MIDI send Mes ON/Off smart mapping 

            Out_smart_mes.MTYPE=Smart_mes.MTYPE;
            Out_smart_mes.Data1=Smart_mes.Data1;
            Out_smart_mes.Data2=Smart_mes.Data2;
            int i;
               // Serial.println(Smart_mes.Data1);
               // Serial.println(Count_pad);
            for (i = 0; i < Count_pad; i = i + 1) 
                {
                if (Base_pads[i].Note  == Smart_mes.Data1)              // find input note in table mapping
                    {
                    //Serial.println(Base_pads[i].Note);
                    Serial.println(Base_pads[i].Name_pad_input);
                    if (Base_pads[i].Mapping_THRUE)                     // if mapping enable then remaping midi mes note and vel
                    {   
                        uint8_t Min_vel =Base_pads[i].Vel_note_min ;  // min input vel
                        uint8_t Max_vel = 127;
                        //Base_pads[i].Last_on_Note = millis();           // last time input pad ms
                        if ((millis()-Base_pads[i].Last_Time_on_Note) < Base_pads[i].Lenght_pad_min) // if time last pad on and curent  pad is ......
                        {   // reapet last note 
                                    Out_smart_mes.Data1= Base_pads[i].Last_Smart_noteOn;
                                    Serial.println("Reapet pads ");
                                    Serial.println(Out_smart_mes.Data1);

                        }
                        
                        else 
                        {

                        //----------------------------------------------------------------------// find 1 range
                                if (Out_smart_mes.Data2>Min_vel && Out_smart_mes.Data2<= Base_pads[i].Vel1) 
                                    {   
                                        Serial.println ("range_1");
                                        Serial.println (Out_smart_mes.Data2);
                                        int Delta_vel = Base_pads[i].Vel1-Min_vel; // delta vel range

                                        Out_smart_mes.Data1= Base_pads[i].Note1;
                                        Base_pads[i].Last_on_Note1 = millis();           // last time input pad ms
                                        Out_smart_mes.Data2= (uint8_t) ((float_t)Base_pads[i].Note1_vel1/Base_pads[i].Vel1 *Out_smart_mes.Data2);
                                         Base_pads[i].Lenght_pad_min = Base_pads[i].Lenght_Note_1;
                                          Serial.println ( Out_smart_mes.Data2);
                                        // Base_pads[i].Last_Smart_noteOn = Out_smart_mes.Data1;


                                    }
                                    else // else 1 note 
                                    {
                                        Min_vel=Base_pads[i].Vel1;
                                         if (Out_smart_mes.Data2>Min_vel && Out_smart_mes.Data2<= Base_pads[i].Vel2) 
                                            {
                                                Base_pads[i].Lenght_pad_min = Base_pads[i].Lenght_Note_2;
                                            Serial.println ("range_2");

                                            Serial.println (Out_smart_mes.Data2);
                                            int Delta_vel = Base_pads[i].Vel2-Min_vel; // delta vel range

                                            Out_smart_mes.Data1= Base_pads[i].Note2;
                                            Base_pads[i].Last_on_Note2 = millis();           // last time input pad ms
                                           Out_smart_mes.Data2= (uint8_t) ((float_t)Base_pads[i].Note2_vel2/Base_pads[i].Vel2  *Out_smart_mes.Data2);
                                            Serial.println ( Out_smart_mes.Data2);
                                            

                                            }
                                            else // else 2 note 
                                                {
                                                    Min_vel=Base_pads[i].Vel2;
                                                    if (Out_smart_mes.Data2>Min_vel && Out_smart_mes.Data2<= Base_pads[i].Vel3) 
                                                        {
                                                            Base_pads[i].Lenght_pad_min = Base_pads[i].Lenght_Note_3;



                                                        }
                                                        else // else 3 note 
                                                             {
                                                                Min_vel=Base_pads[i].Vel3;
                                                                if (Out_smart_mes.Data2>Min_vel && Out_smart_mes.Data2<= Base_pads[i].Vel4) 
                                                                { Base_pads[i].Lenght_pad_min = Base_pads[i].Lenght_Note_4;



                                                                }


                                                             }// else 2 note 
                                                }// else 2 note 
                                    }// else 1 note 
                        }// end else note reapet

                    }// end mapping if 
                        Base_pads[i].Last_Time_on_Note= millis();                   // last time input pad ms
                        Base_pads[i].Last_Smart_noteOn = Out_smart_mes.Data1;
                        Base_pads[i].Last_Smart_velos = Out_smart_mes.Data2;
                        return Out_smart_mes; 
                    }


                    
                    
                      
                }

    return Out_smart_mes;    
}
