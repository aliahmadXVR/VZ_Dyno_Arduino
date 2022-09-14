#ifndef TIMERS_EN_H
#define TIMERS_EN_H

#include "braking.h"
/*
 * All Variables and function declaration here
 */
uint32_t total_tick_front_en = 0;
uint16_t ovrcnt_icp4 = 0;
uint32_t total_4 = 0;
uint32_t cur_input_capture = 0;  
uint32_t pre_input_capture = 0; 
uint32_t diff_input_capture = 0;

//For Test purpose only for now
uint32_t diff_diff_input_capture = 0;
uint32_t cur_diff_input_capture = 0;
uint32_t pre_diff_input_capture = 0;
//
bool flag_encoder_main_front = false;
float tick_mul = 62.5e-09;

void initializeTimers();
void int_callback();

void initializeTimers()
{
  noInterrupts();
  // Initialize Timer4 for encoder pulse inputs
  TCCR4A = 0;
  TCCR4B = 0;
  TCCR4C = 0;
  TIFR4 = (1<<ICF4) | (1<<TOV4);
  TCNT4 = 0;
  TCCR4B |= (1 << ICNC4);     // Enable denoiser
  TCCR4B &= ~(1 << ICES4);    // Capture on falling edge
  TIMSK4 |= (1 << ICIE4) | (1 << TOIE4);
  //TCCR4B |= (1 << CS41);   
  TCCR4B |= (1 << CS40); 
  // No prescaler 1 (001)
  // Prescaler 1024 (101)
  // Prescaler 256  (100)
  // Prescaler 8    (010)


  //set timer1 interrupt at 1Hz for getting Halleffect sensor values for brake motors//
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  attachInterrupt(digitalPinToInterrupt(BLDC_HALL1), int_callback, RISING);


  
  sei();  
} //end timer

void int_callback() 
{
  counts ++;
}

ISR(TIMER1_COMPA_vect) //1-sec timer intterupt
{
  
  RPM = (counts * 60) / BLDC_poles;
//  Serial.print("Counts= ");
//  Serial.println(counts);
  counts=0;
  RPS = RPM/60;
  w = 2*pi*RPS;  // In (rad/s)
  theta_rad = w * 1 ; //1 sec
  theta_deg = (theta_rad * (180/pi) ) + prev_theta_deg  ; //Angle in Degree
  prev_theta_deg =  theta_deg;
//  Serial.print("RPM= ");
//  Serial.println(RPM);
//  Serial.print("Angle Degrees= ");
//  Serial.println(theta_deg);

}



// Encoder ISR (Main front)
ISR(TIMER4_CAPT_vect)  // PULSE DETECTED!  (interrupt automatically triggered, not called by main program)
{
   TCNT4 = 0; 
   flag_encoder_main_front = true;
}

// Encoder overflow ISR
ISR (TIMER4_OVF_vect)
{
  ovrcnt_icp4++;
}


#endif
