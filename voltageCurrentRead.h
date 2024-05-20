#include <driver/adc.h>

//------------------------------------------------------------------------------------------
float getV1(){ //MC33167T 1
  float hold=0;
  float v1=0;
  for(int i=0; i<100; i++){
    if(analogRead(25)==0){
      hold+=0;
    }
    else{
      hold += ((((analogRead(25) * 3.3 ) / (4096))*((10000+330)/330))+3.5); //max:?? min:??  ADC:max:?? min:??
      //hold += (map((analogRead(25)*10),40,750,455,2022))/1000;//((analogRead(25) * 3.3 ) / (4096))*((10000+330)/330); //D25 Channel 1 R1+R2/R2 4.557V: 40(37) min  20.22V:735(738) max
      //delay(1);
    }
    delayMicroseconds(100);
  }
  v1=hold/99;
  return v1;
}

float getV2(){ //MC33167T 2
  float hold=0;
  float v2=0;
  for(int i=0; i<100; i++){
    if(analogRead(27)==0){
      hold+=0;
    }
    else{
      hold += ((((analogRead(27) * 3.3 ) / (4096))*((10000+330)/330))+3.5); //max:19.48 min:4.52 ADC: 48 642
      //hold += (map((analogRead(27)*10),48,642,4.52,19.48))/1000;
      //delay(1);
    }
    delayMicroseconds(100);
  }
  v2=hold/99;
  return v2;
}

float getV3(){ //LM317T max:10.48 min:1.457 ADC:max:872 min:0
  float hold=0;
  float v3=0;
  for(int i=0; i<100; i++){
    if(analogRead(26)==0){
      hold+=0;
    }
    else{
      hold += ((((analogRead(26) * 3.3 ) / (4096))*((3300+250)/250))+1.6); //3000 LM317 1.437
      //hold += (((map((analogRead(26)*10),100,870,146,1055))/1000)+1.2)*1.2; //145 840
      //delay(1);
    }
    delayMicroseconds(100);
  }
  v3=hold/99;
  return v3;
}

float getV4(){ //5V/3.3V
  float hold=0;
  float v4=0;
  for(int i=0; i<100; i++){
    if(analogRead(32)==0){
      hold+=0;
    }
    else{
      hold += (((analogRead(32) * 3.3 ) / (4095))*((3300+250)/250))+1.95;
      //delay(1);
    }
    delayMicroseconds(100);
  }
  v4=hold/99;
  return v4;
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
float getA1(){ //MC33167T 1 //33, 34, 35, 14
  float hold=0;
  float a1=0;
  for(int i=0; i<100; i++){
    if(analogRead(33)==0){
      hold+=0;
    }
    else{
      hold += ((((analogRead(33) * 3.3 ) / (4095))*((330+150)/150)) / 100)*1000; //used voltage divider to step down to .78V
    }
    delayMicroseconds(100);
  }
  a1=hold/99;
  //Serial.print(a1);
  return a1;
}

float getA2(){ //MC33167T 2
  float hold=0;
  float a2=0;
  for(int i=0; i<100; i++){
    if(analogRead(34)==0){
      hold+=0;
    }
    else{
      hold += ((((analogRead(34) * 3.3 ) / (4095))*((330+150)/150)) / 100)*1000; //used voltage divider to step down to .78V
    }
    delayMicroseconds(100);
  }
  a2=hold/99;
  //Serial.print(a2);
  return a2;
}

float getA3(){ //LM317T max:10.48 min:1.457 ADC:max:872 min:0
  float hold=0;
  float a3=0;
  for(int i=0; i<100; i++){
    if(analogRead(33)==0){
      hold+=0;
    }
    else{
      hold += ((((analogRead(35) * 3.3 ) / (4095))*((330+150)/150)) / 100)*1000; //used voltage divider to step down to .78V
    }
    delayMicroseconds(100);
  }
  a3=hold/99;
  //Serial.print(a3);
  return a3;
}

float getA4(){ //5V/3.3V
  float hold=0;
  float a4=0;
  for(int i=0; i<100; i++){
    if(analogRead(33)==0){
      hold+=0;
    }
    else{
      hold += ((((analogRead(14) * 3.3 ) / (4095))*((330+150)/150)) / 100); //used voltage divider to step down to .78V
    }
    delayMicroseconds(100);
  }
  a4=hold/99;
  //Serial.print(a4);
  return a4;
}
//------------------------------------------------------------------------------------------
