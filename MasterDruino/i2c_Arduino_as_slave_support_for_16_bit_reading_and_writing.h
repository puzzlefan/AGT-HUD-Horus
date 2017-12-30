#include <Wire.h>
// I2C stuff
#define SLAVE_ADDRESS 0x42//Adress
#define DATA_COUNT 6//Register count

//recifed command, defines which register gets returned
int I2Ccommand = 0;
//The Register witch holds the data could nearly be any size you wish but one chapter is only 8 Bit long Arduino has only 16 bits and there shut be a max of 256 Registers
unsigned int Register[DATA_COUNT];

void I2CSetup(){
  for(int i = 0;i < DATA_COUNT;i++)
  {
    Register[i] = 0;
  }
}

// I2C callback for received data
void receiveData(int byteCount)
{
 /*
  * //Outputs the complete Input for Debug
  * Serial.println("Anfang Input");
  * while(Wire.available()){
  * Serial.println(Wire.available());
  * Serial.println(Wire.read());
  * }
  * Serial.println("Ende Input");
  */
    int bufferOne = Wire.read();//initiate Buffers, could be array bit is not
    int bufferTwo = -1;
    int bufferThree = -1;

    // read I2C value
    if(Wire.available()>0){//reads second value if its exists
      bufferTwo = Wire.read();
    }
    if(Wire.available()>0){  //reads the third value if its exists
      bufferThree = Wire.read();
    }

    //Outputs all the two Buffer for debugging
    /*Serial.println(bufferOne);
    Serial.println(bufferTwo);
    Serial.println(bufferThree);
    Serial.println();
    */

    if(bufferTwo == -1){
      I2Ccommand = bufferOne;//when there are only 8 bits it was a read command
    }
    else{
      if(bufferThree == -1){
        Register[bufferOne]=bufferTwo;//if there is only one byte sendet onee gets saved
      }
      else{
       Register[bufferOne]= (bufferThree << 8) + bufferTwo;//TwoToOne(bufferTwo,bufferThree, bufferOne);//when there are two bytes of Data they get combined before saving
      }
      I2Ccommand = -1;//when data was recieved nothing is send back
    }
    while(Wire.available()>0){  //reads the third value if its exists
      Serial.println(bufferOne);
      Serial.println(bufferTwo);
      Serial.println(bufferThree);
      Serial.println(Wire.read());
      Serial.println("there is something left");
    }
}

// I2C callback for sending data
// This is called from the I2C master!
void sendData()
{
    // which command for Arduino?
    if (I2Ccommand != -1)
    {
      byte bufie [2] ;//= { byte(bufaa), byte(buf) };
      bufie[0] = Register[I2Ccommand];
      bufie[1] = Register[I2Ccommand] >> 8;
      Wire.write(bufie,sizeof(bufie));
      return;
    }
    //Outputs the complete Register for Debugging
    /*for(int i = 0;i<=19;i++){
      Serial.print(Register[i]);
    }
    Serial.println();
    */
}
