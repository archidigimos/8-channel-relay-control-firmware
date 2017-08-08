#include <EEPROM.h>

int address = 0;
byte value;

int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;
int relay5 = 6;
int relay6 = 7;
int relay7 = 8;
int relay8 = 9;

int decState1 = 0;
int decState2 = 0;
int decState3 = 0;
int decState4 = 0;
int decState5 = 0;
int decState6 = 0;
int decState7 = 0;
int decState8 = 0;
int stateTotal = 0;

int remState = 10;
int eepromSelect=0;
int selected=0;
String statuStr = "";
int execute = 0;

void feedback(String relay)
{
    /*
   * odd == on
   * even == off
   * To find out the relay point, obtain even/2 or (odd+1)/2
  */
  
  if(relay=="1"){if(decState1==1)Serial.print("1");else if(decState1==0)Serial.print("2");}
  else if(relay=="2"){if(decState2==2)Serial.print("3");else if(decState2==0)Serial.print("4");}
  else if(relay=="3"){if(decState3==4)Serial.print("5");else if(decState3==0)Serial.print("6");}
  else if(relay=="4"){if(decState4==8)Serial.print("7");else if(decState4==0)Serial.print("8");}
  else if(relay=="5"){if(decState5==16)Serial.print("9");else if(decState5==0)Serial.print("10");}
  else if(relay=="6"){if(decState6==32)Serial.print("11");else if(decState6==0)Serial.print("12");}
  else if(relay=="7"){if(decState7==64)Serial.print("13");else if(decState7==0)Serial.print("14");}
  else if(relay=="8"){if(decState8==128)Serial.print("15");else if(decState8==0)Serial.print("16");}
}

void processData(String str)
{
  /*
  if(str=="RL1_OFF"){digitalWrite(relay1, LOW);decState1=0;Serial.print("relay1_on");}
  else if(str=="RL1_ON"){digitalWrite(relay1, HIGH);decState1=1;Serial.print("relay1_off");}
  if(str=="RL2_OFF"){digitalWrite(relay2, LOW);decState2=0;Serial.print("relay2_on");}
  else if(str=="RL2_ON"){digitalWrite(relay2, HIGH);decState2=2;Serial.print("relay2_off");}
  if(str=="ALL_ON"){digitalWrite(relay1, HIGH);digitalWrite(relay2, HIGH);decState1=1;decState2=2;Serial.print("all_on");}
  else if(str=="ALL_OFF"){digitalWrite(relay1, LOW);digitalWrite(relay2, LOW);decState1=0;decState2=0;Serial.print("all_off");}
  if(str=="RL3_ON"){digitalWrite(relay3, LOW);decState3=4;Serial.print("relay3_on");}
  else if(str=="RL3_OFF"){digitalWrite(relay3, HIGH);decState3=0;Serial.print("relay3_off");}
  if(str=="RL4_ON"){digitalWrite(relay4, LOW);decState4=8;Serial.print("relay4_on");}
  else if(str=="RL4_OFF"){digitalWrite(relay4, HIGH);decState4=0;Serial.print("relay4_off");}
  if(str=="RL5_ON"){digitalWrite(relay5, LOW);decState5=16;Serial.print("relay5_on");}
  else if(str=="RL5_OFF"){digitalWrite(relay5, HIGH);decState5=0;Serial.print("relay5_off");}
  if(str=="RL6_ON"){digitalWrite(relay6, LOW);decState6=32;Serial.print("relay6_on");}
  else if(str=="RL6_OFF"){digitalWrite(relay6, HIGH);decState6=0;Serial.print("relay6_off");}
  if(str=="RL7_ON"){digitalWrite(relay7, LOW);decState7=64;Serial.print("relay7_on");}
  else if(str=="RL7_OFF"){digitalWrite(relay7, HIGH);decState7=0;Serial.print("relay7_off");}
  if(str=="RL8_ON"){digitalWrite(relay8, LOW);decState8=128;Serial.print("relay8_on");}
  else if(str=="RL8_OFF"){digitalWrite(relay8, HIGH);decState8=0;Serial.print("relay8_off");}
  */
  /*
   * odd == on
   * even == off
   * To find out the relay point, obtain even/2 or (odd+1)/2
  */
  if(str=="1"){digitalWrite(relay1, LOW);decState1=1;}//Serial.print("1");}
  else if(str=="2"){digitalWrite(relay1, HIGH);decState1=0;}//Serial.print("2");}
  if(str=="3"){digitalWrite(relay2, LOW);decState2=2;}//Serial.print("3");}
  else if(str=="4"){digitalWrite(relay2, HIGH);decState2=0;}//Serial.print("4");}
  if(str=="5"){digitalWrite(relay3, LOW);decState3=4;}//Serial.print("5");}
  else if(str=="6"){digitalWrite(relay3, HIGH);decState3=0;}//Serial.print("6");}
  if(str=="7"){digitalWrite(relay4, LOW);decState4=8;}//Serial.print("7");}
  else if(str=="8"){digitalWrite(relay4, HIGH);decState4=0;}//Serial.print("8");}
  if(str=="9"){digitalWrite(relay5, LOW);decState5=16;}//Serial.print("9");}
  else if(str=="10"){digitalWrite(relay5, HIGH);decState5=0;}//Serial.print("10");}
  if(str=="11"){digitalWrite(relay6, LOW);decState6=32;}//Serial.print("11");}
  else if(str=="12"){digitalWrite(relay6, HIGH);decState6=0;}//Serial.print("12");}
  if(str=="13"){digitalWrite(relay7, LOW);decState7=64;}//Serial.print("13");}
  else if(str=="14"){digitalWrite(relay7, HIGH);decState7=0;}//Serial.print("14");}
  if(str=="15"){digitalWrite(relay8, LOW);decState8=128;}//Serial.print("15");}
  else if(str=="16"){digitalWrite(relay8, HIGH);decState8=0;}//Serial.print("16");}
  
  if(str=="unamereq")Serial.print("sergey");
  if(str=="passreq")Serial.print("brin");
  if(str.substring(0,1)=="F")feedback(str.substring(1));
  if(str=="req_state")Serial.println(value);
  if(str=="execute")execute = 1;

  stateTotal = decState1+decState2+decState3+decState4+decState5+decState6+decState7+decState8;
  EEPROM.write(address, stateTotal);
}

void serialReceive()
{
 String str = "";
  while(Serial.available()>0)
  {
    char temp = (char)Serial.read();
    str += temp;
    delay(10);
  }
  if(str != "")
  {
    processData(str);
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);
  digitalWrite(relay7, HIGH);
  digitalWrite(relay8, HIGH);


  pinMode(remState, INPUT);
}

void loop() {
  eepromSelect = digitalRead(remState);
  value = EEPROM.read(address);
  if((eepromSelect==1)&&(selected==0))
    {
      if(bitRead(value,0)==1){digitalWrite(relay1, HIGH);decState1=1;}
      else if(bitRead(value,0)==0){digitalWrite(relay1, LOW);decState1=0;}
      if(bitRead(value,1)==1){digitalWrite(relay2, HIGH);decState2=2;}
      else if(bitRead(value,1)==0){digitalWrite(relay2,LOW);decState2=0;}
      if(bitRead(value,2)==1){digitalWrite(relay3, LOW);decState3=4;}
      else if(bitRead(value,2)==0){digitalWrite(relay3, HIGH);decState3=0;}
      if(bitRead(value,3)==1){digitalWrite(relay4, LOW);decState4=8;}
      else if(bitRead(value,3)==0){digitalWrite(relay4, HIGH);decState4=0;}
      if(bitRead(value,4)==1){digitalWrite(relay5, LOW);decState5=16;}
      else if(bitRead(value,4)==0){digitalWrite(relay5, HIGH);decState5=0;}
      if(bitRead(value,5)==1){digitalWrite(relay6, LOW);decState6=32;}
      else if(bitRead(value,5)==0){digitalWrite(relay6, HIGH);decState6=0;}
      if(bitRead(value,6)==1){digitalWrite(relay7, LOW);decState7=64;}
      else if(bitRead(value,6)==0){digitalWrite(relay7, HIGH);decState7=0;}
      if(bitRead(value,7)==1){digitalWrite(relay8, LOW);decState8=128;}
      else if(bitRead(value,7)==0){digitalWrite(relay8, HIGH);decState8=0;}
    
      selected=1;
      
     }
  
  serialReceive();
}
