#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
float LMT;
byte arrayLMT[4];

void setup() {
  Serial.begin(9600);           
  Wire.begin(0x08);               // join i2c bus with address 0x08
  Wire.onReceive(receiveEvent);   // register event
  //for I2C display
  Wire.begin();
  lcd.init();
  lcd.backlight();
}

union
{
  byte arrayLMT[4];
  float LMT;
}myDATA;

void loop() {
  //printing on the Serial Monitor of Nano
  Serial.print("LMT: ");
  Serial.print(myDATA.LMT); 
  Serial.println(" deg C");
  
  //printing on I2C display
  lcd.setCursor(0,0);
  lcd.print("LMT: ");
  lcd.print(myDATA.LMT);
  lcd.print(" ");
  lcd.write(0xDF);//symbol of degree
  lcd.print("C");
  delay(2000);
}

void receiveEvent(int howMany) {
  interrupts();
  myDATA.arrayLMT[3]= Wire.read();
  myDATA.arrayLMT[2]= Wire.read();
  myDATA.arrayLMT[1]= Wire.read();
  myDATA.arrayLMT[0]= Wire.read();
}
