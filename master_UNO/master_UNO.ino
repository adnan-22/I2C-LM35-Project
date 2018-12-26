#include <Wire.h>
byte busStatus;
float LMT;
byte arrayLMT[4];
void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);  //INTERNAK 1.1v for the Vref of ADC 
  Wire.begin();                // join i2c bus
  //checking the slave is present or not
  do
  {                                       
    Wire.beginTransmission(0x08);
    busStatus=Wire.endTransmission();
  }while(busStatus!=0);
}
union 
{
  float  LMT;
  byte arrayLMT[4];

}myDATA;
void loop() {
  myDATA.LMT=100*(1.1/1024)*analogRead(A0); //calculating the temp using LM35 sensor;
  Serial.println(myDATA.LMT);
  //transmitting the digits to slave
  Wire.beginTransmission(0x08); // transmit to slave (0x08)
  Wire.write(myDATA.arrayLMT[3]);  
  Wire.write(myDATA.arrayLMT[2]);  
  Wire.write(myDATA.arrayLMT[1]);
  Wire.write(myDATA.arrayLMT[0]);               
  Wire.endTransmission();    // stop transmitting
  delay(2000);
}
