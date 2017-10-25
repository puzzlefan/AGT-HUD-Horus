/* Example: BlueTooth HC-05 Setup
 - WHAT IT DOES: 
   - Sets "EN" pin on HC-05 HIGH to enable command mode
   - THEN applies Vcc from 2 Arduino pins to start command mode
   - SHOULD see the HC-05 LED Blink SLOWLY: 2 seconds ON/OFF 
 
 Sends, Receives AT commands
   For Setup of HC-05 type BlueTooth Module
   NOTE: Set Serial Monitor to 'Both NL & CR' and '9600 Baud' at bottom right   
 - SEE the comments after "//" on each line below
 - CONNECTIONS:
   - GND
   - Pin z,B, 10 to HC-05 TXD
   - Pin z.B. 11 to HC-05 RXD
   - Pin z.B. 2 to HC-05 EN
   - Pin z.B. VCC to HC-05 VCC for power control
   - Pin z.B. 3 to HC-05 State
 - V1.02 05/02/2015
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SoftwareSerial.h>  
/*-----( Declare Constants and Pin Numbers )-----*/
#define HC_05_TXD_ARDUINO_RXD 10
#define HC_05_RXD_ARDUINO_TXD 11
#define HC_05_EN        4
#define HC_05_State     5

/*-----( Declare objects )-----*/
SoftwareSerial BTSerial(HC_05_TXD_ARDUINO_RXD, HC_05_RXD_ARDUINO_TXD); // RX | TX
/*-----( Declare Variables )-----*/
//NONE

void setup()   /****** SETUP: RUNS ONCE ******/
{
  pinMode(HC_05_EN, OUTPUT); 
  pinMode(HC_05_State, INPUT);
  
  digitalWrite(HC_05_SETUPKEY, LOW);  // Set command mode when powering up
  
  Serial.begin(9600);   // For the Arduino IDE Serial Monitor
  Serial.println("Set Serial Monitor to 'Both NL & CR' and '9600 Baud' at bottom right");
  Serial.println("Applying VCC Power. LED should blink SLOWLY: 2 Seconds ON/OFF");
  delay(2000);
  Serial.println("Enter AT commands in top window.");
  BTSerial.begin(38400);  // HC-05 default speed in AT command mode

}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  // READ from HC-05 and WRITE to Arduino Serial Monitor
  if (BTSerial.available())
  {
    Serial.write(BTSerial.read());
    //Serial.println("sollte lesen");
  }

  // READ Arduino Serial Monitor and WRITE to HC-05
  if (Serial.available())
  {
    BTSerial.write(Serial.read());
    //Serial.println("soltel schreiben");
  }

}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
//NONE

//*********( THE END )***********


