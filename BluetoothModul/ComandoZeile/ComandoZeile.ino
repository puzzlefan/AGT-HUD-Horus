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
   - Pin      19 to HC-05 TXD
   - Pin      18 to HC-05 RXD
   - Pin z.B. 2 to HC-05 EN
   - Pin z.B. VCC to HC-05 VCC for power control
   - Pin z.B. 3 to HC-05 State
 - V1.02 05/02/2015
   Questions: terry@yourduino.com */

/*-----( Declare Constants and Pin Numbers )-----*/
#define HC_05_EN        2
#define HC_05_State     0 //has to be analog because voltage to small
#define SerialConnection 1

/*-----( Declare Variables )-----*/
HardwareSerial* SerialPort[4]={&Serial, &Serial1, &Serial2, &Serial3};

void setup()   /****** SETUP: RUNS ONCE ******/
{
  pinMode(HC_05_EN, OUTPUT);
  digitalWrite(HC_05_EN, HIGH);  // Set command mode when powering up, if you want to use this as a serial playgound BETWEEN the two devices it needs to b3e low

  Serial.begin(9600);   // For the Arduino IDE Serial Monitor
  Serial.println("Set Serial Monitor to 'Both NL & CR' and '9600 Baud' at bottom right");
  Serial.println("LED should blink SLOWLY: 2 Seconds ON/OFF");
  delay(2000);
  Serial.println("Enter AT commands in top window.");
  SerialPort[SerialConnection]->begin(38400);// HC-05 default speed in AT command mode

}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  // READ from HC-05 and WRITE to Arduino Serial Monitor
  if (SerialPort[SerialConnection]->available())
  {
    Serial.write(SerialPort[SerialConnection]->read());
    //Serial.println("sollte lesen");
  }

  // READ Arduino Serial Monitor and WRITE to HC-05
  if (Serial.available())
  {
    SerialPort[SerialConnection]->write(Serial.read());
    //Serial.println("soltel schreiben");
  }

}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/
//NONE
//14,3,60CA2
//*********( THE END )***********
