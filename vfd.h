#ifndef VFD_H
#define VFD_H

/*
 * Pins Defination
 * --------------------------------
 */
#define VFD_FREQ_IN_PIN 4 //4 //Pin which is connceted to VFD freq. control pin A1N


/* 
 *  All functions are defined here
 *  --------------------------------
 */
void init_vfd();
void set_VFD_freq_On();
void set_VFD_freq_Off();

/*
 * Any Specific Variables
 */


 

/*
 * Init the LED/VFD Freq set pin to output mode
 */
void init_vfd()
{
  pinMode(VFD_FREQ_IN_PIN, OUTPUT);
}

 
/*
 * This functions sets the VFD Frequency 
 * on the specified Pin
 */
void set_VFD_freq_On()
{
  analogWrite(VFD_FREQ_IN_PIN, Conf_val.VFD_freq);
}

/*
 * This functions sets the frequency to 0
 */
void set_VFD_freq_Off()
{
  analogWrite(VFD_FREQ_IN_PIN, 0);
}


#endif
