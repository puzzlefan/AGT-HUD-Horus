/* YourDuino.com Example: BlueTooth HC-05 Setup
 - WHAT IT DOES: 
   - Sets "Key" pin on HC-05 HIGH to enable command mode
   - THEN applies Vcc from 2 Arduino pins to start command mode
   - SHOULD see the HC-05 LED Blink SLOWLY: 2 seconds ON/OFF 
 
 Sends, Receives AT commands
   For Setup of HC-05 type BlueTooth Module
   NOTE: Set Serial Monitor to 'Both NL & CR' and '9600 Baud' at bottom right   
 - SEE the comments after "//" on each line below
 - CONNECTIONS:
   - GND
   - Pin 2 to HC-05 TXD
   - Pin 3 to HC-05 RXD
   - Pin 4 to HC-05 KEY
   - Pin 5+6 to HC-05 VCC for power control
 - V1.02 05/02/2015
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SoftwareSerial.h>  
/*-----( Declare Constants and Pin Numbers )-----*/
#define HC_05_TXD_ARDUINO_RXD 2
#define HC_05_RXD_ARDUINO_TXD 3
#define HC_05_SETUPKEY        4
#define HC_05_PWR1            5  // Connect in parallel to HC-05 VCC
#define HC_05_PWR2            6  // Connect in parallel to HC-05 VCC

/*-----( Declare objects )-----*/
SoftwareSerial BTSerial(HC_05_TXD_ARDUINO_RXD, HC_05_RXD_ARDUINO_TXD); // RX | TX
/*-----( Declare Variables )-----*/
//NONE

void setup()   /****** SETUP: RUNS ONCE ******/
{
  pinMode(HC_05_SETUPKEY, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  pinMode(HC_05_PWR1, OUTPUT);      // Connect in parallel to HC-05 VCC
  pinMode(HC_05_PWR2, OUTPUT);      // Connect in parallel to HC-05 VCC
  
  digitalWrite(HC_05_SETUPKEY, HIGH);  // Set command mode when powering up
  
  Serial.begin(9600);   // For the Arduino IDE Serial Monitor
  Serial.println("YourDuino.com HC-05 Bluetooth Module AT Command Utility V1.02");
  Serial.println("Set Serial Monitor to 'Both NL & CR' and '9600 Baud' at bottom right");
  Serial.println("Vcc Power Up DELAY");
  delay(2000);
  Serial.println("Applying VCC Power. LED should blink SLOWLY: 2 Seconds ON/OFF");
  digitalWrite(HC_05_PWR1, HIGH); // Power VCC
  digitalWrite(HC_05_PWR2, HIGH);  
  delay(2000);
  Serial.println("Enter AT commands in top window.");
  BTSerial.begin(38400);  // HC-05 default speed in AT command mode

}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  // READ from HC-05 and WRITE to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // READ Arduino Serial Monitor and WRITE to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());

}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
//NONE

//*********( THE END )***********


