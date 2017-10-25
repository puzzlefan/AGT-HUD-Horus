#define STATE_PIN 0
#define EN_PIN 2
#define ERROR_PIN 13

//varaibles
int AnalogTreshhold = 500;
final int SerialSpeed = 38400;

void setup() {
  // put your setup code here, to run once:
  pinMode(EN_PIN,OUTPUT);
  pinMode(ERROR_PIN,OUTPUT);
  digitalWrite(EN_PIN,LOW);
  digitalWrite(ERROR_PIN,LOW);
  while(analogRead(STATE_PIN)<AnalogTreshhold);
  Serial1.begin(SerialSpeed);
  Serial1.write("test");
  delay(100);
  while (Serial1.available()) {
    /* code */
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
