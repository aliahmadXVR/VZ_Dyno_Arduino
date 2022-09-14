
#include "dyno_serial.h"
#include "wheelbase.h"
#include "vfd.h"
#include "braking.h"
#include "timers_en.h"
#include "loadCell.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>


LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
char Serial_data_IN; //use to save every incoming data
String appendSerialData;
String appendSerialData1;
/*
 * Some variables related to Dyno Configurations
 * Might be Deleted Afterwards if unused
 */
char *strings[10];
char *ptr = NULL;
byte index = 0;
char array[100] = "";
String Config_data_IN; //used to save the config data from Arduino
char *ss[8];
int firstSerial = 0; //0
bool first_time_counter = true;

//These two variables are just for testing the first serial 
char c= '0'; //use to save every incoming data
//

const int BUFFER_SIZE = 100;
char buf[BUFFER_SIZE];
double start_time =0;



void setup() {

/*
 * Initialize all the Sensors/Other component
 * functions here. Might be move to seprate function 
 * in the end when eveything is complete.
 */
  init_sensors();
  init_locking_pins();
  init_wheelbase_motor();
  init_brakes();
  init_vfd();
  initializeTimers();
  
  // Serial1.begin(115200);
  Serial.begin(115200);
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print(".. Hello ..");
  lcd.setCursor(4,1);
  lcd.print("VZ Dyno");

  start_time = millis();
   bmp.begin();
} //end Setup

void loop() {

  /*if(flag_encoder_main_front == true)
  {
      total_4 = (ovrcnt_icp4*65536) + ICR4;
      flag_encoder_main_front = false;

      cur_input_capture = total_4;
      diff_input_capture = cur_input_capture - pre_input_capture;
      pre_input_capture = cur_input_capture; 

      sensor1 = diff_input_capture;
      //Serial.println(sensor1);
     
      //sensor1 = 327678;
      //Serial.println(sensor1);
      //Serial.print((String) sensor1 + "A" + "\n");
  }*/


  //  Update the sensors every 5 seconds
  double time_now = millis();

  if ( (time_now - start_time) > 5000)
  {
    update_sensors();
    start_time = millis();
  }
  /*
   * From Here the Main Serial Recieve starts 
   * which controls the main program after 
   * configuration msgs
   */
   
    while(Serial.available()>0) 
    {
        Serial_data_IN = Serial.read(); 
        appendSerialData += Serial_data_IN;
    }

    
  /*
   * Switch statement on Incoming FLAG
   * ----------------------------------
   */
  
  switch (Serial_data_IN)
  {
    case Dyno_start_msg:
    {
      //lcd.clear();
      lcd.home();
      lcd.print("Dyno Started");
      appendSerialData=""; 
      Serial_data_IN=0;
      
      FLAG.RUN_dyno =1; //Enable the Dyno RUN Flag
      FLAG.SHOW_sensor = 0;//Disable sensor data sending function
      FLAG.ADJ_wheelBase = 0; //Disable wheel base adjustment fucntion
      FLAG.DYNO_Config=0;
      FLAG.DYNO_Brake=0;
      FLAG.DYNO_LOCKPIN_en=0;
      FLAG.DYNO_LOCKPIN_dis=0;
      break;
    };

    case Dyno_stop_msg:
    {
      //lcd.clear();
      lcd.home();
      lcd.print("Dyno Stopped");
      appendSerialData=""; 
      Serial_data_IN=0;
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.SHOW_sensor = 0; //Disable sensor data sending function
      FLAG.ADJ_wheelBase = 0; //Disable wheel base adjustment fucntion
      FLAG.DYNO_Config=0;
      FLAG.DYNO_Brake=0;
      FLAG.DYNO_LOCKPIN_en=0;
      FLAG.DYNO_LOCKPIN_dis=0;
      break;
    };

    case Sensor_data_show_msg:
    {
      lcd.clear();
      lcd.home();
      lcd.print("ShowSensor");
      appendSerialData=""; 
      Serial_data_IN=0;
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.SHOW_sensor = 1; //Enable dyno sensor data sending
      FLAG.ADJ_wheelBase=0;
      FLAG.DYNO_Config=0;
      FLAG.DYNO_Brake=0;
      FLAG.DYNO_LOCKPIN_en=0;
      FLAG.DYNO_LOCKPIN_dis=0;
      break;
    };

    case Wheel_BaseF_Adj_msg:
    {
      lcd.clear();
      lcd.home();
      lcd.print("WBase Adj");
      appendSerialData=""; 
      Serial_data_IN=0;
      FLAG.RUN_dyno=0;
      FLAG.SHOW_sensor = 0;  //Disable the show sensor data flag
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.ADJ_wheelBase = 1; //Enable wheel base adjustment fucntion
      FLAG.ADJ_wheelBaseR = 0; //Enable wheel base adjustment fucntion
      FLAG.DYNO_Config=0;
      FLAG.DYNO_Brake=0;
      FLAG.DYNO_LOCKPIN_en=0;
      FLAG.DYNO_LOCKPIN_dis=0;
      break;
    };

    case Wheel_BaseR_Adj_msg:
    {
      lcd.clear();
      lcd.home();
      lcd.print("WBase Adj");
      appendSerialData=""; 
      Serial_data_IN=0;
      FLAG.RUN_dyno=0;
      FLAG.SHOW_sensor = 0;  //Disable the show sensor data flag
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.ADJ_wheelBase = 0;
      FLAG.ADJ_wheelBaseR = 1; //Enable wheel base adjustment fucntion
      FLAG.DYNO_Config=0;
      FLAG.DYNO_Brake=0;
      FLAG.DYNO_LOCKPIN_en=0;
      FLAG.DYNO_LOCKPIN_dis=0;
      break;
    };

    case Dyno_config_msg:
    {
      lcd.clear();
      lcd.home();
      lcd.print("Dyno Config");
      appendSerialData=""; 
      FLAG.RUN_dyno=0;
      FLAG.SHOW_sensor = 0;  //Disable the show sensor data flag
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.ADJ_wheelBase = 0; //Disable wheel base adjustment fucntion
      FLAG.DYNO_Config =1; //Enable Dyno config function
      FLAG.DYNO_Brake=0;
      FLAG.DYNO_LOCKPIN_en=0;
      FLAG.DYNO_LOCKPIN_dis=0;
      break;
    }

    case Dyno_Brake_msg:
    {
     // lcd.clear();
      lcd.home();
      lcd.print("Brake Dyno");
      appendSerialData=""; 
      FLAG.SHOW_sensor = 0;  //Disable the show sensor data flag
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.ADJ_wheelBase = 0; //Disable wheel base adjustment fucntion
      FLAG.DYNO_Config =0; //Disable Dyno config function
      FLAG.DYNO_Brake =1; //Enable Brakes
      FLAG.DYNO_DisBrake = 0;
      FLAG.DYNO_LOCKPIN_en=0;
      FLAG.DYNO_LOCKPIN_dis=0;
     // dyno_enable_brake();
      break;
    }

    case Dyno_Disable_Brake_msg:
    {
      lcd.home();
      lcd.print("Disable-Brake");
      appendSerialData=""; 
      FLAG.SHOW_sensor = 0;  //Disable the show sensor data flag
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.ADJ_wheelBase = 0; //Disable wheel base adjustment fucntion
      FLAG.DYNO_Config =0; //Disable Dyno config function
      FLAG.DYNO_Brake =0; //Enable Brakes
      FLAG.DYNO_LOCKPIN_en=0;
      FLAG.DYNO_LOCKPIN_dis=0;
      FLAG.DYNO_DisBrake = 1;
     // dyno_disable_brake();
      break;
    }
    
    case Dyno_LockPin_msg:
    {
      //lcd.clear();
      lcd.home();
      lcd.print("LockPins En");
      appendSerialData=""; 
      FLAG.SHOW_sensor = 0;  //Disable the show sensor data flag
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.ADJ_wheelBase = 0; //Disable wheel base adjustment fucntion
      FLAG.DYNO_Config =0; //Disable Dyno config function
      FLAG.DYNO_Brake =0; //Disable Brakes
      FLAG.DYNO_LOCKPIN_en =1; //Enable Lockpins
      FLAG.DYNO_LOCKPIN_dis=0;
      break;
    }
    case Dyno_UnLockPin_msg:
    {
     // lcd.clear();
      lcd.home();
      lcd.print("Un-LockPins");
      appendSerialData=""; 
      FLAG.SHOW_sensor = 0;  //Disable the show sensor data flag
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.ADJ_wheelBase = 0; //Disable wheel base adjustment fucntion
      FLAG.DYNO_Config =0; //Disable Dyno config function
      FLAG.DYNO_Brake =0; //Disable Brakes
      FLAG.DYNO_LOCKPIN_en =0; //disable Lockpins enable signal
      FLAG.DYNO_LOCKPIN_dis =1; //Enable disengage lock pin signal
      break;
    }
    
    case Dyno_Fan_ON_msg:
    {
     // lcd.clear();
      lcd.home();
      lcd.print("FAN-ON");
      appendSerialData=""; 
      FLAG.SHOW_sensor = 0;  //Disable the show sensor data flag
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.ADJ_wheelBase = 0; //Disable wheel base adjustment fucntion
      FLAG.DYNO_Config =0; //Disable Dyno config function
      FLAG.DYNO_Brake =0; //Disable Brakes
      FLAG.DYNO_LOCKPIN_en =0; //disable Lockpins enable signal
      FLAG.DYNO_LOCKPIN_dis =0; //Enable disengage lock pin signal
      FLAG.DYNO_FAN_ON  = 1;
      FLAG.DYNO_FAN_OFF  = 0;
      break;
    }
    
    case Dyno_Fan_oFF_msg:
    {
     // lcd.clear();
      lcd.home();
      lcd.print("FAN-OFF");
      appendSerialData=""; 
      FLAG.SHOW_sensor = 0;  //Disable the show sensor data flag
      FLAG.RUN_dyno =0; //Disable the Dyno Serial
      FLAG.ADJ_wheelBase = 0; //Disable wheel base adjustment fucntion
      FLAG.DYNO_Config =0; //Disable Dyno config function
      FLAG.DYNO_Brake =0; //Disable Brakes
      FLAG.DYNO_LOCKPIN_en =0; //disable Lockpins enable signal
      FLAG.DYNO_LOCKPIN_dis =0; //Enable disengage lock pin signal
      FLAG.DYNO_FAN_ON  = 0;
      FLAG.DYNO_FAN_OFF  = 1;
      
      break;
    }

 
    default:
    {
      
    };
   
  }//End Serial Data In


  /*
   * Function Calling & Decision Making based on FLAG
   * ------------------------------------------------
   */
//  Serial.println("Looping");
  if(FLAG.RUN_dyno == 1)
  {
//    if (Serial1.available() > 0) 
//    {
//      //uint32_t rlen = Serial1.readBytesUntil('\n', buf, BUFFER_SIZE);
//      uint32_t data_in = Serial1.parseInt(); 
//      //Serial.println("I received: ");
//
//      //int x = atoi(buf);
//      //Serial.print("I received: ");
//      //Serial.print(data_in);
//      
//      //sensor1 = data_in;
//
//      sensor1 = map(data_in, 196443, 1048642, 0, 1023 );   //Calcuates the POT value back 
//      //uint32_t voltage= sensor1 * (5.0 / 1023.0);  //Converting to Voltage
//    }
    
    sample_data_simulate(); //This function sends the sample data only
    
  }

  if (FLAG.RUN_dyno == 0)
  {
    //dont call any function for now.
  }
  
  if (FLAG.SHOW_sensor == 1)
  {
    //send sensor data to GUI
    show_sensor_data();
  }

  if (FLAG.ADJ_wheelBase == 1)
  {
    value = digitalRead(encoder_clk);
    if (value != rotation)
    { 
       if (digitalRead(DT) != value) 
       {                                // Clockwise
         RotPosition ++;
         LeftRight = true;
       } 
       else 
       {                                //Counterclockwise
         LeftRight = false;
         RotPosition--;
       }
      
       if (LeftRight)
       {                
         counter = counter+1;
       }
       else
       {                                 
         counter = counter-1;
       }
     } 
  rotation = value;
  wheelBase_adjust(false); //Move wheelbase in forward direction
  }

  if (FLAG.ADJ_wheelBaseR == 1)
  {
    value = digitalRead(encoder_clk);
    if (value != rotation)
    { 
       if (digitalRead(DT) != value) 
       {                                // Clockwise
         RotPosition ++;
         LeftRight = true;
       } 
       else 
       {                                //Counterclockwise
         LeftRight = false;
         RotPosition--;
       }
      
       if (LeftRight)
       {                
         counter = counter+1;
       }
       else
       {                                 
         counter = counter-1;
       }
     } 
  rotation = value;
  wheelBase_adjust(true); //Move wheelbase in reverse direction
  }
  
  if (FLAG.DYNO_Brake == 1)
  {
//      Serial.println("Braking Check");
//      Serial.println(FLAG.DYNO_Brake);
      //dyno_enable_brake();
      bool status_bb = dyno_enable_brake();
      if (status_bb == true) 
      {
        FLAG.DYNO_Brake = 0;
      }
  }
  
  if (FLAG.DYNO_DisBrake == 1)
  {
    bool status = dyno_disable_brake();
    if (status == true) 
    {
      FLAG.DYNO_DisBrake = 0;
//      Serial.println("Position reached disabled Brake"); 
    }
  }
  
  if(FLAG.DYNO_LOCKPIN_en == 1)
  {
    Enable_Lockpins();
  }

  if(FLAG.DYNO_LOCKPIN_dis == 1)
  {
    Disable_Lockpins();
  }
  
  if(FLAG.DYNO_FAN_ON == 1)
  {
    set_VFD_freq_On();
  } 

  if(FLAG.DYNO_FAN_OFF == 1)
  {
    set_VFD_freq_Off();
  }


} //end MAIN Loop
