#ifndef WHEELBASE_H
#define WHEELBASE_H


/*
 * Pins Defination
 * --------------------------------
 */
#define LOCKPIN_PIN1 6
#define LOCKPIN_PIN1_c 7
#define LOCKPIN_PIN3 8
#define LOCKPIN_PIN4 9
#define LOCKPIN1_POT A12
#define LOCKPIN2_POT A11
#define LOCKPIN3_POT A10
#define LOCKPIN4_POT A9
#define WHEELBASE_MOTOR_DIR_PIN1 43
#define WHEELBASE_MOTOR_DIR_PIN2 44
//#define WHEELBASE_PROX_SENS1 51
//#define WHEELBASE_PROX_SENS2 52
#define WHEELBASE_MOT_HALL_SEN 18 //20  //Not using now actual pin is 20
#define encoder_clk 51 //change this pin
#define DT 52
#define wheelbase_Enticks 8 //change this pin  

/*
 * Custom Variables 
 */

bool wheelbase_rev_sig = false ;
int wheelbase_counts = 0;
bool homing_done = false; //By Default no homing is done
void CalwheelBasePos();
int RotPosition = 0; 
int rotation, counter=0;  
int value;
boolean LeftRight;
/* 
 *  All functions are defined here
 *  --------------------------------
 */
void init_wheelbase_motor();
void run_wheelbase_motor_forward();
void run_wheelbase_motor_rev();
void stop_wheelbase_motor();
void wheelBase_adjust(bool wheelbase_rev_sig);
void Enable_Lockpins();
void Disable_Lockpins();
void homing_wheelBase();
int get_WheelbaseEncoder_ticks();


/*
 * This function inits the wheel bases pins to 
 * high logic at start.
 */
void init_locking_pins()
{
    pinMode(LOCKPIN_PIN1 , OUTPUT);
    pinMode(LOCKPIN_PIN1_c , OUTPUT);
    pinMode(LOCKPIN_PIN3 , OUTPUT);
    pinMode(LOCKPIN_PIN4 , OUTPUT);
    //Use High logic @init for Relays & Low Logic for LEDs 
    digitalWrite(LOCKPIN_PIN1, 0);
    digitalWrite(LOCKPIN_PIN1_c, 0);
    digitalWrite(LOCKPIN_PIN3, 0);
    digitalWrite(LOCKPIN_PIN4, 0);
    
    //Init the Wheelbase Hall Sens Pin
    pinMode(WHEELBASE_MOT_HALL_SEN, INPUT);
    digitalWrite(WHEELBASE_MOT_HALL_SEN, LOW); // Setting LOW for rising edge
}


/*
 * This function sets the wheelbase 
 * motor direction. Assuming 1,0 one dir 
 * and 0,1 other dir. 
 */
void init_wheelbase_motor()
{
  //Init the Motor Direction pins as output
  pinMode(WHEELBASE_MOTOR_DIR_PIN1 , OUTPUT);
  pinMode(WHEELBASE_MOTOR_DIR_PIN2 , OUTPUT);
  //Init the Wheelbase Prox sensor pins as input
//  pinMode(WHEELBASE_PROX_SENS1 , INPUT);
//  pinMode(WHEELBASE_PROX_SENS2 , INPUT);
  //Stop the motor by default
  digitalWrite(WHEELBASE_MOTOR_DIR_PIN1, 0); //change to 0, just done for relays testing
  digitalWrite(WHEELBASE_MOTOR_DIR_PIN2, 0);

  //enable the rotary encoder for wheelbase position
  pinMode (encoder_clk,INPUT);
  pinMode (DT,INPUT);
  rotation = digitalRead(encoder_clk); 
  
  homing_done = false; //By Default no homing is done
}

void run_wheelbase_motor_forward()
{
  //Set the direction to forward side
  digitalWrite(WHEELBASE_MOTOR_DIR_PIN1, 1);
  digitalWrite(WHEELBASE_MOTOR_DIR_PIN2, 0);  
}

void run_wheelbase_motor_rev()
{
  //Set the direction to rev side
  digitalWrite(WHEELBASE_MOTOR_DIR_PIN1, 0);
  digitalWrite(WHEELBASE_MOTOR_DIR_PIN2, 1);
}

void stop_wheelbase_motor()
{
  //Same logic stops the wheelbase motor//
  digitalWrite(WHEELBASE_MOTOR_DIR_PIN1, 1);
  digitalWrite(WHEELBASE_MOTOR_DIR_PIN2, 1);
}
/*
 * Starts to adjust the wheelbase
 */
void wheelBase_adjust(bool wheelbase_rev_sig)
{
 
    if(wheelbase_rev_sig == false)
    {
      run_wheelbase_motor_forward();
      if(RotPosition >= 30)
      {
        stop_wheelbase_motor();
        return;
      }
    }
  
    else
    {
      run_wheelbase_motor_rev();
      if(RotPosition <= -30)
      {
        stop_wheelbase_motor();
        return;
      }
    }

}

/*
 * Calcuates the Ticks of the wheelbase encoder
 */
void CalwheelBasePos()
{
  if (wheelbase_rev_sig == false)  wheelbase_counts++;

  else wheelbase_counts--;
}

/*
 * Homing Function
 */
void homing_wheelBase()
{
  //Run the Wheelbase motor forward until it comes to one
  //extreme end
  run_wheelbase_motor_forward();
  wheelbase_counts = 0;
  homing_done = true;
  
}

 

/*
 * Enable all lockpins
 * 
 */
void Enable_Lockpins()
{
//  int pin1 = analogRead(LOCKPIN1_POT);
//  int pin2 = analogRead(LOCKPIN2_POT);
//  int pin3 = analogRead(LOCKPIN3_POT);
//  int pin4 = analogRead(LOCKPIN4_POT);
//
//  //this check is for checking the analog voltage on the internal Proximity sensor
//  if( (pin1 >= 4000) && (pin2 >= 4000) && (pin3 >= 4000) && (pin4 >= 4000) ) //4000 is generally random here for now.
//  {
    digitalWrite(LOCKPIN_PIN1, 1);
    digitalWrite(LOCKPIN_PIN1_c, 0);
//    digitalWrite(LOCKPIN_PIN3, 1);
//    digitalWrite(LOCKPIN_PIN4, 1);
//  }
}

/*
 * Disable all lockpins
 */
void Disable_Lockpins()
{
  digitalWrite(LOCKPIN_PIN1, 0);
  digitalWrite(LOCKPIN_PIN1_c, 1);
//  digitalWrite(LOCKPIN_PIN3, 0);
//  digitalWrite(LOCKPIN_PIN4, 0);
}


/*
 * Returns the wheelbase encoder ticks
 */
 /*
int get_WheelbaseEncoder_ticks()
{
  value = digitalRead(CLK);
  if (value != rotation)
  { 
    // we use the DT pin to find out which way we turning.
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
  
  }
  rotation = value;
}*/
#endif
