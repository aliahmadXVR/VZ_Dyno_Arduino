#ifndef BRAKING_H
#define BRAKING_H
#include "timers_en.h"

/*
 * This file contains functions related to the braking
 * function. Load cell parameter/data to be added afterwards.
 */
/*
 * Pins Defination
 * --------------------------------
 */
#define BLDC_BRK_PIN_FRONT 27
#define BLDC_BRK_PIN_AFT 13 
#define DIR_PIN_FRONT 34 
#define DIR_PIN_AFT 35 
#define BLDC_HALL1 3
#define BLDC_HALL2 2
#define ClUTCH_1 24
#define ClUTCH_2 23
#define SOLE_1_HOLD 41
#define SOLE_2_HOLD 37
#define SOLE_EN_1 40
#define SOLE_EN_2 36


/*
 * Functions declarations
 */
void init_brakes();
void set_dir(int pos);
bool dyno_enable_brake(); //Enable Brakes
bool dyno_disable_brake(); //Disable Brakes
bool move_to_pos1();
bool move_to_pos2();
/*
 * Custom Variables
 * --------------------------------
 */
//Braking related global variables
 uint32_t counts = 0;
int freq = 0;
int BLDC_poles = 4;//from data sheet
double RPM =0;
float pi = 3.141;
double RPS; 
double w; 
double theta_rad;
double theta_deg;
double prev_theta_deg= 0;
////////////

/* 
 *  All functions are defined here
 *  --------------------------------
 */
 
/*
 * Initialize the brakes BLDC motors
 * Sets the direction
 * Disables the brakes
 */
void init_brakes()
{
  pinMode(BLDC_BRK_PIN_FRONT , OUTPUT);
  pinMode(BLDC_BRK_PIN_AFT , OUTPUT);
  pinMode(DIR_PIN_FRONT , OUTPUT);
  pinMode(DIR_PIN_AFT , OUTPUT);
  pinMode(BLDC_HALL1 , OUTPUT);
  pinMode(BLDC_HALL2 , OUTPUT);
  pinMode(ClUTCH_1 , OUTPUT);
  pinMode(ClUTCH_2 , OUTPUT);
  pinMode(SOLE_1_HOLD , OUTPUT);
  pinMode(SOLE_2_HOLD , OUTPUT);
  pinMode(SOLE_EN_1 , OUTPUT);
  pinMode(SOLE_EN_2 , OUTPUT);

  pinMode(BLDC_HALL1, INPUT_PULLUP);
  
  digitalWrite(BLDC_BRK_PIN_FRONT , 1);

  //set_dir(1);
  //dyno_disable_brake();
}

/**
 * Brake BLDC Halleffect sensor Callback
 */
void encoder_interrupt_sub() 
{
  counts ++;
}


/*
 * Sets the Brake Motors to Clockwise
 * or Anticlockwise direction
 */
void set_dir(int dir) 
{
  /* 
   *  This function assumes that @ 1,1 on both pins, the motor has 
   *  one direction and on 0,0 the motor has second direction 
   */

  if(dir ==1 || dir ==2)
  {
    if (dir == 1)
    {
      //Set Direction first and then run the Motor 
      digitalWrite(DIR_PIN_FRONT,1);
    }
    else
    {
      digitalWrite(DIR_PIN_FRONT,0);
    }
  }

   else 
   {
      digitalWrite(DIR_PIN_FRONT,1);
      return;
   }  
  
}

/*
 * Enables both Front and AFT brakes
 */
bool dyno_enable_brake()
{
//  Serial.println("theta1 = ");
//  Serial.print(theta_deg);
  digitalWrite(SOLE_EN_1,1); 
  digitalWrite(SOLE_EN_2,1); 
  
  delay(100); //100ms delay after solenoid energize
  digitalWrite(SOLE_1_HOLD,1);
  digitalWrite(SOLE_2_HOLD,1); 
  
  digitalWrite(ClUTCH_1,1); 
  digitalWrite(ClUTCH_2,1); 

  digitalWrite(BLDC_BRK_PIN_FRONT , 0);
  //After setting all the solenoids, now release the brakes.
  set_dir(1); //Sets the BLDCs to clockwise movement which dis-engages the brakes.
  bool status_b = move_to_pos1();
  delay (1000);
  while(1)
  {
      digitalWrite(BLDC_BRK_PIN_FRONT , 1);

  }
  //digitalWrite(ClUTCH_1,0); 
  //digitalWrite(ClUTCH_2,0);
  if ( status_b == true ) {return true;}
  else {return false;}
  
}


bool dyno_disable_brake()
{
  digitalWrite(ClUTCH_1,1); 
  digitalWrite(ClUTCH_2,1); 
  
   
  delay(100); //100ms delay after solenoid energize

  digitalWrite(BLDC_BRK_PIN_FRONT , 0);
  //After setting all the solenoids, now release the brakes.
  set_dir(2); //Sets the BLDC to anti clockwise movement which engages the brakes.
  bool status = move_to_pos2();
  digitalWrite(SOLE_EN_1,0); 
  digitalWrite(SOLE_EN_2,0); 
  digitalWrite(SOLE_1_HOLD,0);
  digitalWrite(SOLE_2_HOLD,0); 
  //digitalWrite(ClUTCH_1,0); 
  //digitalWrite(ClUTCH_2,0);
  if ( status == true ) {return true;}
  else {return false;}
}

bool move_to_pos1()
{
//  Serial.println("Moving motors");
//  Serial.println("theta = ");
//  Serial.print(theta_deg);
  if(theta_deg >= 16000)
  {
    //stop motors
//    Serial.println("Stopping motors");
    digitalWrite(BLDC_BRK_PIN_FRONT , 1);
    theta_deg = 0;
    return true;
  }
}

bool move_to_pos2()
{
  if(theta_deg >= 16000)
  {
    //stop motors
    digitalWrite(BLDC_BRK_PIN_FRONT , 1);
    theta_deg = 0;
    return true;
  }
}
#endif
