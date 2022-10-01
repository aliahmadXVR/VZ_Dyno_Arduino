
#ifndef DYNO_H
#define DYNO_H
/*
 * Define all functions/defines related to Serial 
 * communication with DynoGUI
 * --------------------------------
 */
#include "timers_en.h"
#include <Adafruit_BMP085.h>


/* 
 *  Msgs Defines 
 *  --------------------------------
 */
#define Dyno_sample_msg 'S'
#define Dyno_start_msg '#'
#define Dyno_stop_msg 'A'
#define Sensor_data_show_msg 'D'
#define Start_dT_transmit_msg 'S'
#define Wheel_BaseF_Adj_msg 'W'
#define Wheel_BaseR_Adj_msg 'R'
#define Dyno_config_msg 'C'
#define Dyno_Brake_msg 'B'
#define Dyno_Disable_Brake_msg 'V'
#define Dyno_LockPin_msg 'L'
#define Dyno_UnLockPin_msg 'U'
#define Dyno_Fan_ON_msg 'F'
#define Dyno_Fan_oFF_msg 'N'

/*
 * Pins Defination
 * --------------------------------
 */

#define HUMIDITY_PIN A2
#define BEARING_TEMP_PIN1 A5
#define BEARING_TEMP_PIN2 A6
#define BEARING_TEMP_PIN3 A7
#define BEARING_TEMP_PIN4 A8 
#define AFR_SENSOR_PIN A14
#define PRESSURE_SENS_PIN A1
#define seaLevelPressure_hPa 1013.25


/*
 * Custom Sturctures
 * --------------------------------
 */
struct Dyno_flag
{
  //bool DYNO_INIT;
  bool RUN_dyno;
  bool RUN_sample;
  bool SHOW_sensor;
  bool ADJ_wheelBase;
  bool ADJ_wheelBaseR;
  bool DYNO_Config;
  bool DYNO_Brake;
  bool DYNO_DisBrake;
  bool DYNO_LOCKPIN_en;
  bool DYNO_LOCKPIN_dis;
  bool DYNO_FAN_ON;
  bool DYNO_FAN_OFF;
}FLAG;

/*
 * This structure contains the variables
 * which will store all the configuration parameters
 */
struct Config_values
{
  int VFD_freq;
  
}Conf_val;

struct Sensor_IN
{
  float temperature_BMP;
  float pressure_BMP;
  float voltage;
  float current;
  float loadCell_1;
  float loadCell_2;
  float gearBox_1;
  float gearBox_2;
  float lockPin_1;
  float lockPin_2;
  float lockPin_3;
  float lockPin_4;
  float AFR;
  
}SENSOR;


/*
 * Custom Variables
 * --------------------------------
 */
uint32_t sensor1;
long int sensor2,sensor3,sensor4,sensor5,sensor6,sensor7,sensor8,sensor9,sensor10;
float sensor11,sensor12,sensor13,sensor14,sensor15,sensor16,sensor17,sensor18,sensor19,sensor20;

int sample_data_sensors[5] = {1,2,3,4,5};
long int sample_data[] {586760,585030,583330,581640,579950,578270,576610,574960,573320,571700,570080,568470,566880,565300,563730,562170,560630,559090,557560,556050,554560,553060,551580,550110,548660,547210,545780,544350,542930,541540,540130,538760,537380,536030,534660,533330,531990,530670,529360,528050,526760,525470,524200,522920,521680,520420,519180,517950,516730,515510,514310,513110,511920,510740,509560,508400,507240,506090,504950,503820,502680,501570,500460,499350,498250,497160,496070,495000,493930,492860,491800,490760,489710,488670,487640,486610,485590,484580,483570,482580,481570,480590,479600,478620,477650,476680,475720,474760,473810,472870,471920,470990,470060,469130,468210,467290,466390,465480,464580,463680,462790,461900,461020,460140,459270,458390,457540,456670,455820,454960,454120,453270,452440,451600,450760,449940,449120,448300,447480,446670,445860,445060,444260,443460,442670,441880,441090,440310,439540,438750,437990,437220,436460,435690,434940,434180,433430,432680,431940,431200,430460,429730,428990,428270,427540,426820,426100,425380,424670,423970,423250,422550,421850,421150,420460,419770,419070,418400,417700,417030,416350,415670,415000,414340,413660,413000,412340,411690,411020,410380,409720,409070,408430,407790,407150,406510,405870,405240,404620,403980,403360,402740,402120,401500,400890,400270,399660,399060,398450,397850,397250,396650,396050,395460,394870,394280,393700,393110,392530,391950,391370,390800,390220,389650,389090,388520,387950,387400,386830,386280,385720,385170,384620,384070,383520,382980,382430,381900,381360,380820,380290,379750,379230,378700,378170,377650,377120,376610,376090,375570,375060,374550,374030,373530,373030,372510,372020,371520,371020,370520,370030,369530,369050,368550,368070,367580,367100,366620,366140,365660,365190,364710,364230,363770,363300,362830,362370,361900,361440,360990,360520,360070,359610,359160,358700,358260,357810,357360,356920,356480,356030,355590,355160,354720,354290,353850,353420,352990,352560,352140,351710,351290,350860,350450,350020,349610,349190,348780,348370,347950,347550,347130,346740,346320,345920,345520,345120,344720,344320,343930,343530,343140,342740,342360,341960,341580,341190,340810,340420,340050,339660,339280,338900,338530,338150,337780,337400,337040,336660,336290,335930,335560,335200,334830,334480,334110,333750,333390,333040,332680,332320,331980,331620,331270,330920,330570,330220,329880,329530,329190,328850,328510,328170,327820,327490,327160,326820,326480,326150,325820,325490,325160,324830,324500,324180,323850,323520,323210,322880,322560,322240,321920,321610,321280,320970,320660,320350,320030,319720,319400,319100,318790,318490,318170,317880,317560,317270,316960,316660,316350,316060,315760,315460,315170,314870,314570,314280,313990,313700,313400,313110,312830,312530,312250,311960,311680,311390,311100,310820,310540,310260,309980,309700,309420,309140,308860,308590,308310,308030,307760,307490,307220,306940,306680,306400,306130,305870,305600,305330,305060,304800,304540,304270,304010,303740,303490,303220,302960,302710,302440,302190,301930,301670,301420,301160,300910,300650,300400,300150,299900,299650,299390,299150,298900,298650,298400,298160,297910,297660,297420,297180,296930,296690,296450,296200,295970,295720,295490,295240,295010,294770,294530,294300,294060,293830,293590,293350,293130,292890,292650,292430,292200,291960,291740,291500,291280,291050,290820,290590,290370,290150,289910,289700,289460,289250,289020,288800,288580,288360,288140,287910,287700,287480,287260,287040,286820,286610,286390,286180,285960,285740,285530,285320,285110,284890,284680,284470,284260,284040,283840,283630,283420,283210,283010,282790,282590,282390,282180,281970,281770,281560,281360,281160,280960,280750,280550,280350,280150,279950,279750,279560,279350,279160,278950,278770,278560,278370,278170,277980,277790,277590,277400,277200,277020,276820,276630,276440,276250,276050,275870,275690,275490,275310,275110,274940,274740,274560,274380,274190,274010,273820,273640,273460,273280,273100,272910,272740,272550,272380,272190,272020,271840,271670,271490,271310,271140,270960,270780,270620,270440,270270,270090,269930,269750,269590,269410,269240,269080,268910,268740,268570,268400,268250,268070,267910,267750,267580,267420,267260,267100,266930,266780,266610,266460,266300,266130,265990,265820,265670,265510,265360,265210,265050,264900,264740,264590,264450,264290,264140,264000,263840,263700,263550,263400,263260,263120,262970,262820,262680,262540,262400,262260,262120,261980,261840,261700,261570,261430,261290,261160,261030,260890,260760,260620,260500,260370,260230,260110,259980,259850,259730,259600,259480,259350,259230,259110,258980,258870,258750,258630,258510,258390,258280,258160,258050,257930,257820,257710,257600,257490,257390,257270,257170,257060,256950,256860,256750,256640,256550,256450,256350,256250,256150,256060,255960,255870,255770,255690,255590,255510,255410,255330,255250,255160,255070,254990,254910,254830,254760,254670,254600,254520,254440,254380,254300,254230,254160,254100,254030,253960,253900,253830,253780,253710,253650,253600,253540,253490,253430,253390,253330,253280,253240,253190,253140,253100,253060,253020,252990,252940,252910,252880,252850,252810,252790,252750,252740,252710,252690,252660,252650,252640,252610,252610,252590,252580,252580,252570,252570,252560,252570,252560,252570,252580,252580,252600,252600,252620,252640,252650,252680,252700,252720,252750,252780,252810,252850,252880,252920,252960,253010,253050,253100,253150,253200,253260,253320,253380,253450,253510,253580,253650,253730,253800,253890,253970,254060,254140,254240,254330,254440,254530,254640,254750,254860,254970,255100,255210,255340,255470,255600,255740,255870,256020,256170,256310,256470,256630,256800,256950,257130,257310,257480,257670,257850,258050,258240,258450,258650,258860,259080,259300,259520,259750,259990,260230,260480,260720,260990,261240,261520,261780,262070,262360,262640,262940,263250,263560,263880,264200,264530,264860,265220,265560,265930,266290,266660,267050,267440,267830,268240,268660,269080,269510,269960,270400,270860,271340,271810,272300,272800,273310,273830,274360,274910,275460,276020,276610,277190,277800,278410,279040,279680,280340,281010,281700,282400,283110,283850,284600,285360,286140,286940,287760,288600,289460,290330,291230,292150,293090,294060,295040,296050,297080,298150,299230,300350,301490,302660,303860,305100,306370,307660,309010,310370,311780,313240,314720,316250,317840,319450,321130,322850,324620,326460,328340,330290,332300,334370,336520,338750,341030,343420,345870,348430,351080,353820,356680,359640,362740,365950,369300,372790,376450,380270,384270,388450,392860,397470,402330,407460,412870,418590,424660,431100,437950,445280,453090,461500,470540,480310,490900,502430,515060,528960,544340,561500,580790,602690,627830,657090,691720,733550,785480,852310,942840,1075490,1298430,1815390};
Adafruit_BMP085 bmp;  //For BMP180 Pressure/temperature sensor//
 
/*
 * All function declarations here
 */

void init_sensors();
void init_DYNO_values();
void Send_To_GUI();
void Send_Sample_To_GUI();
void sample_data_simulate();
void show_sensor_data();
void update_sensors();
void get_BMP_baro_data();
void send_diagnostic_values();

/* 
 *  All functions are defined here
 *  --------------------------------
 */
void init_sensors()
{
   sensor1=sensor2=sensor3=sensor4=sensor5=sensor6=sensor7=sensor8=sensor9=sensor10=10;
   sensor11=sensor12=sensor13=sensor14=sensor15=sensor16=sensor17=sensor18=sensor19=sensor20=15;
//   bmp.begin();
}


/*
 * This function sets all the basic parameters to 
 * default.
 */
void init_DYNO_values()
{
  
}

/*
 * This function sends the '10 sensors' Data to 
 * GUI.
 */
void Send_To_GUI()
{
  Serial.print((String) sensor1 + "A" + sensor2 + "B" + sensor3 + "C" + sensor4 + 
  "D" + sensor5 + "E"  + sensor6 + "F" + sensor7 + "G" + sensor8 + "H" + sensor9 + 
  "I" + sensor10+ "J" + "\n");
}

/*
 * This function is used for sending test
 * values of dyno (as in text file) to the 
 * GUI. This is just for testing purpose.
 */
void Send_Sample_To_GUI()
{
  Serial.print((String) sensor1 + "A" + sensor2 + "B" + sensor3 + "C" + sensor4 + "D" + sensor5 + "E"  + sensor6 + "F" + sensor7 + "G" + sensor8 + "H" + sensor9 + 
  "I" + sensor10+ "J" + "\n");
  //Serial.print((String) sensor1 + "A" + "\n");
  //delay(20); //10
}


/* This Function Simulates Data as Written 
 *  in the Provided Text File (Sample Actual 
 *  DYNO RUN)
 */
void sample_data_simulate() 
{
  static int i = 0; //end value 979
  sensor1 = sample_data[i];  //sample_data variable is global
  Send_Sample_To_GUI();  //this function sends all sensor variables (Global) to GUI
  delay(50);
  i++;
  if(i >979) i=0;
  //Send_Sample_To_GUI();  //this function sends all sensor variables (Global) to GUI
} 

/*
 * This function sets all the Sensor Variables
 * for sending to GUI.
 */
void show_sensor_data()
{
  // Just Send the Sensor variables to GUI//sample_data_sensors
  static int i = 0; 
//  sensor1 = sample_data_sensors[i];  
//Sensor 1 already being updated by the main code (dT coming from Encoder)
  sensor2 = SENSOR.temperature_BMP;
  sensor3 = SENSOR.pressure_BMP;
  sensor4 = 220;
  sensor5 = 50;
  sensor6 = sample_data_sensors[i];
  sensor7 = sample_data_sensors[i];
  sensor8 = sample_data_sensors[i];
  sensor9 = sample_data_sensors[i];
  sensor10 = sample_data_sensors[i];
  Send_To_GUI();
  delay(10);
  i++;
  if(i >4) i=0;
  
}


/*
 * Update the Barometer data
 */
void get_BMP_baro_data()
{
  SENSOR.temperature_BMP = bmp.readTemperature();
  SENSOR.pressure_BMP = bmp.readPressure();
}


/*
 * This functions updtates all sensors.
 * This is called after every 5 seconds by the main loop
 */
void update_sensors()
{
  get_BMP_baro_data();
}


#endif
