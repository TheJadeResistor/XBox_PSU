#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h> //Hardware-specific library
TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
#define BLYNK_PRINT Serial
#define BLYNK_USE_DIRECT_CONNECT
#include <BlynkSimpleEsp32_BLE.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include "voltageCurrentRead.h"

static bool blynk= false;

//------------------------------------------------------------------------------------------
void moreTemp(){
  //get values of temp and send them back
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.drawRoundRect(224, 179, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(225, 180, 80, 45, 5, TFT_SILVER);//17
  tft.setCursor(237, 186); //22
  tft.println("Back");

  tft.fillRoundRect(9, 2, 302, 166, 5, TFT_DARKGREY);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(1);
  tft.drawRoundRect(11, 4, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(12, 5, 145, 50, 5, TFT_ORANGE);//+7
  tft.setCursor(15, 8);
  tft.println("Channel 1: MC33167T");
  tft.setTextSize(2);
  tft.setCursor(15, 23);//+15
  tft.println("000.0");
  tft.setCursor(110, 23);
  tft.println("F");
  tft.drawCircle(100, 30, 4, TFT_BLACK); //x,y,radius,color degree symbol
  
  tft.setTextSize(1);
  tft.drawRoundRect(161, 4, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(162, 5, 145, 50, 5, TFT_BLUE);
  tft.setCursor(165, 8);
  tft.println("Channel 2: MC33167T");
  tft.setTextSize(2);
  tft.setCursor(165, 23);
  tft.println("000.0");
  tft.setCursor(255, 23); //make letter and degree symbol
  tft.println("F");
  tft.drawCircle(245, 30, 4, TFT_BLACK); //x,y,radius,color degree symbol
  
  tft.setTextSize(1);
  tft.drawRoundRect(11, 59, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(12, 60, 145, 50, 5, TFT_GREEN);
  tft.setCursor(15, 63);
  tft.println("Channel 3: LM317T");
  tft.setTextSize(2);
  tft.setCursor(15, 78);
  tft.println("000.0");
  tft.setCursor(110, 78);
  tft.println("F");
  tft.drawCircle(100, 85, 4, TFT_BLACK); //x,y,radius,color degree symbol

  tft.setTextSize(1);
  tft.drawRoundRect(161, 59, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(162, 60, 145, 50, 5, TFT_MAGENTA);
  tft.setCursor(165, 63);
  tft.println("Channel 4: 3.3/5V");
  tft.setTextSize(2);
  tft.setCursor(165, 78);
  tft.println("COLD");
  tft.setTextSize(1);

  tft.drawRoundRect(11, 114, 298, 52, 5, TFT_BLUE);
  tft.fillRoundRect(12, 115, 296, 50, 5, TFT_SILVER);
  tft.setCursor(15, 117);
  tft.println("Temperature sensors: ");
  tft.setCursor(15, 131);
  tft.println("No sensor on 5V regulator, not high power");
  tft.setCursor(15, 145);
  tft.println("I'm not sure what to write here...");
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void moreBLE(){
  //connect to blynk via bluetooth low energy, give status queues
  tft.setTextColor(TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextSize(3);
  tft.setCursor(60, 80);
  tft.println("Connected");
  blynk= true;
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
int seconds=0;
int minutes=0;
void dataPrintTime(int spot, int timeVal){
  seconds= timeVal/1000; //esp_log_timestamp() / 1000;
  minutes = seconds / 60;
  seconds %= 60;
  minutes %= 60;
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(1);
  switch (spot){
    case 1:
      tft.setCursor(284, 35);
      tft.print(minutes);tft.print(":");tft.print(seconds);tft.print(" ");
      break;
    case 2:
      tft.setCursor(284, 53); //y+18
      tft.print(minutes);tft.print(":");tft.print(seconds);tft.print(" ");
      break;
    case 3:
      tft.setCursor(284, 71);
      tft.print(minutes);tft.print(":");tft.print(seconds);tft.print(" ");
      break;
    case 4: 
      tft.setCursor(284, 89);
      tft.print(minutes);tft.print(":");tft.print(seconds);tft.print(" ");
      break;
    case 5:
      tft.setCursor(284, 107);
      tft.print(minutes);tft.print(":");tft.print(seconds);tft.print(" ");
      break;
    case 6:
      tft.setCursor(284, 125);
      tft.print(minutes);tft.print(":");tft.print(seconds);tft.print(" ");
      break;
    case 7:  
      tft.setCursor(284, 143);
      tft.print(minutes);tft.print(":");tft.print(seconds);tft.print(" ");
      break;
    default:
      break;
  }
  
}

void dataSetup(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.drawRoundRect(224, 179, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(225, 180, 80, 45, 5, TFT_SILVER);
  tft.setCursor(237, 186);
  tft.println("Back");

  tft.fillRect(0, 51, 320, 2, TFT_DARKGREY);
  tft.fillRect(0, 69, 320, 2, TFT_DARKGREY);//y+18
  tft.fillRect(0, 87, 320, 2, TFT_DARKGREY);
  tft.fillRect(0, 105, 320, 2, TFT_DARKGREY);
  tft.fillRect(0, 123, 320, 2, TFT_DARKGREY);
  tft.fillRect(0, 141, 320, 2, TFT_DARKGREY);
  //tft.fillRect(0, 159, 320, 2, TFT_DARKGREY); last row
  
  tft.fillRect(0, 0, 320, 32, TFT_SILVER);
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(283, 2);
  tft.println("Since");
  tft.setCursor(286, 15);
  tft.println("boot");

  tft.setTextColor(TFT_BLACK, TFT_ORANGE);
  tft.setCursor(22, 2);
  tft.println(" Ch1 ");
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(14, 15);
  tft.println("V     A");
  tft.fillRect(83, 0, 2, 165, TFT_SILVER);
  
  tft.setTextColor(TFT_BLACK, TFT_BLUE);
  tft.setCursor(118, 2);
  tft.println(" Ch2 ");
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(110, 15);
  tft.println("V     A");
  tft.fillRect(177, 0, 2, 165, TFT_SILVER);

  tft.setTextColor(TFT_BLACK, TFT_GREEN);
  tft.setCursor(212, 2);
  tft.println(" Ch3 ");
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(204, 15);
  tft.println("V     A");
  tft.fillRect(272, 0, 2, 165, TFT_SILVER);


  tft.setTextColor(TFT_WHITE);
  tft.setCursor(7, 180);
  tft.println("Delay");
  tft.setCursor(9, 193);
  tft.println("time: ");
  
  tft.setTextColor(TFT_BLACK); //up and down arrows, adjust delay time
  tft.setTextFont(2);
  tft.setTextSize(4);
  tft.drawRoundRect(64, 179, 47, 47, 5, TFT_BLUE);
  tft.fillRoundRect(65, 180, 45, 45, 5, TFT_SILVER);
  tft.fillTriangle(69, 215, 87, 185, 105, 215, TFT_BLACK);
  tft.fillTriangle(74, 215, 87, 195, 100, 215, TFT_SILVER);

  tft.drawRoundRect(129, 179, 47, 47, 5, TFT_BLUE);
  tft.fillRoundRect(130, 180, 45, 45, 5, TFT_SILVER);
  tft.fillTriangle(134, 185, 152, 217, 170, 185, TFT_BLACK);
  tft.fillTriangle(139, 185, 152, 207, 165, 185, TFT_SILVER);
}

void dataPlot(int channel, String var, float value, int timeSpot, int valTime){
  int y=0;
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(1);

  if(timeSpot==1){
    y=35;
  }
  if(timeSpot==2){
    y=53;
  }
  if(timeSpot==3){
    y=71;
  }
  if(timeSpot==4){
    y=89;
  }
  if(timeSpot==5){
    y=107;
  }
  if(timeSpot==6){
    y=125;
  }
  if(timeSpot==7){
    y=143;
  }
  
  if(channel==1){ //ch1
    if(var.equalsIgnoreCase("V")){
      tft.setCursor(2, y); //32
      tft.println(value); //00.00 V
      dataPrintTime(timeSpot, valTime);
    }
    else if(var.equalsIgnoreCase("A")){
      tft.setCursor(50, y);
      tft.println(value); //0.00 A
      dataPrintTime(timeSpot, valTime);
    }
  }

  else if(channel==2){//ch1
    if(var.equalsIgnoreCase("V")){
      tft.setCursor(92, y); //32
      tft.println(value); //00.00 V
      dataPrintTime(timeSpot, valTime);
    }
    else if(var.equalsIgnoreCase("A")){
      tft.setCursor(140, y);//+48
      tft.println(value); //0.00 A
      dataPrintTime(timeSpot, valTime);
    }
  }

  else if(channel==3){//ch1
    if(var.equalsIgnoreCase("V")){
      tft.setCursor(185, y); //32
      tft.println(value); //00.00 V
      dataPrintTime(timeSpot, valTime);
    }
    else if(var.equalsIgnoreCase("A")){
      tft.setCursor(233, y);
      tft.println(value); //0.00 A
      dataPrintTime(timeSpot, valTime);
    }
  }
  
}

static float values[7];
static float values1[7];
static float values2[7];
static float values3[7];
static float values4[7];
static float values5[7];
static float values6[7];
int counterD=1;

void dataArray(){
  switch (counterD){
    case 1: //row 1
      values[0]= getV1();
      values[1]= getA1();
      values[2]= getV2();
      values[3]= getA2();
      values[4]= getV3();
      values[5]= getA3();
      values[6]= esp_log_timestamp();
      counterD++;
      break;
    case 2: //row 2
      values1[0]= getV1();
      values1[1]= getA1();
      values1[2]= getV2();
      values1[3]= getA2();
      values1[4]= getV3();
      values1[5]= getA3();
      values1[6]= esp_log_timestamp();
      counterD++;
      break;
    case 3:
      values2[0]= getV1();
      values2[1]= getA1();
      values2[2]= getV2();
      values2[3]= getA2();
      values2[4]= getV3();
      values2[5]= getA3();
      values2[6]= esp_log_timestamp();
      counterD++;
      break;
    case 4: 
      values3[0]= getV1();
      values3[1]= getA1();
      values3[2]= getV2();
      values3[3]= getA2();
      values3[4]= getV3();
      values3[5]= getA3();
      values3[6]= esp_log_timestamp();
      counterD++;
      break;
    case 5:
      values4[0]= getV1();
      values4[1]= getA1();
      values4[2]= getV2();
      values4[3]= getA2();
      values4[4]= getV3();
      values4[5]= getA3();
      values4[6]= esp_log_timestamp();
      counterD++;
      break;
    case 6:
      values5[0]= getV1();
      values5[1]= getA1();
      values5[2]= getV2();
      values5[3]= getA2();
      values5[4]= getV3();
      values5[5]= getA3();
      values5[6]= esp_log_timestamp();
      counterD++;
      break;
    case 7:  
      values6[0]= getV1();
      values6[1]= getA1();
      values6[2]= getV2();
      values6[3]= getA2();
      values6[4]= getV3();
      values6[5]= getA3();
      values6[6]= esp_log_timestamp();
      counterD++;
      break;
    default:
      counterD=1;
      break;
  }
}

int i=0;
void moreData(){
  //have a spreadchart or something to display history of values
  //tft.setCursor(8, 208);
  //tft.println("10 Min");//30 min max
  //min delay delay(3*60*1000); //3min
  i++;
  switch(i){
    case 1:
      dataPlot(1, "v", values[0], i, values[6]);
      dataPlot(1, "a", values[1], i, values[6]);
      dataPlot(2, "v", values[2], i, values[6]);
      dataPlot(2, "a", values[3], i, values[6]);
      dataPlot(3, "v", values[4], i, values[6]);
      dataPlot(3, "a", values[5], i, values[6]);
      break;
    case 2:
      dataPlot(1, "v", values1[0], i, values1[6]);
      dataPlot(1, "a", values1[1], i, values1[6]);
      dataPlot(2, "v", values1[2], i, values1[6]);
      dataPlot(2, "a", values1[3], i, values1[6]);
      dataPlot(3, "v", values1[4], i, values1[6]);
      dataPlot(3, "a", values1[5], i, values1[6]);
      break;
    case 3:
      dataPlot(1, "v", values2[0], i, values2[6]);
      dataPlot(1, "a", values2[1], i, values2[6]);
      dataPlot(2, "v", values2[2], i, values2[6]);
      dataPlot(2, "a", values2[3], i, values2[6]);
      dataPlot(3, "v", values2[4], i, values2[6]);
      dataPlot(3, "a", values2[5], i, values2[6]);
      break;
    case 4:
      dataPlot(1, "v", values3[0], i, values3[6]);
      dataPlot(1, "a", values3[1], i, values3[6]);
      dataPlot(2, "v", values3[2], i, values3[6]);
      dataPlot(2, "a", values3[3], i, values3[6]);
      dataPlot(3, "v", values3[4], i, values3[6]);
      dataPlot(3, "a", values3[5], i, values3[6]);
      break;
    case 5:
      dataPlot(1, "v", values4[0], i, values4[6]);
      dataPlot(1, "a", values4[1], i, values4[6]);
      dataPlot(2, "v", values4[2], i, values4[6]);
      dataPlot(2, "a", values4[3], i, values4[6]);
      dataPlot(3, "v", values4[4], i, values4[6]);
      dataPlot(3, "a", values4[5], i, values4[6]);
      break;
    case 6:
      dataPlot(1, "v", values5[0], i, values5[6]);
      dataPlot(1, "a", values5[1], i, values5[6]);
      dataPlot(2, "v", values5[2], i, values5[6]);
      dataPlot(2, "a", values5[3], i, values5[6]);
      dataPlot(3, "v", values5[4], i, values5[6]);
      dataPlot(3, "a", values5[5], i, values5[6]);
      break;
    case 7:
      dataPlot(1, "v", values6[0], i, values6[6]);
      dataPlot(1, "a", values6[1], i, values6[6]);
      dataPlot(2, "v", values6[2], i, values6[6]);
      dataPlot(2, "a", values6[3], i, values6[6]);
      dataPlot(3, "v", values6[4], i, values6[6]);
      dataPlot(3, "a", values6[5], i, values6[6]);
      break;
    default:
      i=0;
      break;
  }
  
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void moreStats(){
  //show stats of all channels (i.e voltage and current ranges, IC's, CC)
  //also add personal info...website
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.drawRoundRect(224, 179, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(225, 180, 80, 45, 5, TFT_SILVER);
  tft.setCursor(237, 186);
  tft.println("Back");

  tft.fillRoundRect(9, 2, 302, 166, 5, TFT_DARKGREY);
  
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(1);
  tft.drawRoundRect(11, 4, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(12, 5, 145, 50, 5, TFT_ORANGE);//+7
  tft.setCursor(15, 8);
  tft.println("Channel 1: MC33167T");
  tft.setCursor(15, 23);//+15
  tft.println("4.5-20VDC; 5A");
  tft.setCursor(15, 36);//+16
  tft.println("CC: 10mA-1.2A");

  tft.drawRoundRect(161, 4, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(162, 5, 145, 50, 5, TFT_BLUE);
  tft.setCursor(165, 8);
  tft.println("Channel 2: MC33167T");
  tft.setCursor(165, 23);
  tft.println("4.5-20VDC; 5A");
  tft.setCursor(165, 36);
  tft.println("CC: 10mA-1.2A");

  tft.drawRoundRect(11, 59, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(12, 60, 145, 50, 5, TFT_GREEN);
  tft.setCursor(15, 63);
  tft.println("Channel 3: LM317T");
  tft.setCursor(15, 78);
  tft.println("0-10.5V; 8A");
  tft.setCursor(15, 91);
  tft.println("CC: 10mA-1.2A");

  tft.drawRoundRect(161, 59, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(162, 60, 145, 50, 5, TFT_MAGENTA);
  tft.setCursor(165, 63);
  tft.println("Channel 4: 3.3/5V");
  tft.setCursor(165, 78);
  tft.println("3.3V/5V; 1.5A");
  tft.setCursor(165, 91);
  tft.println("CC: None");

  tft.drawRoundRect(11, 114, 298, 52, 5, TFT_BLUE);
  tft.fillRoundRect(12, 115, 296, 50, 5, TFT_SILVER);
  tft.setCursor(15, 117);
  tft.println("Firmware: 8/28/2021");
  tft.setCursor(15, 131);
  tft.println("Created by Sage Magras, TheJadeResistor");
  tft.setCursor(15, 145);
  tft.println("https://magrassage.wixsite.com/thejaderesistor");

  tft.drawXBitmap(2, 190, logo, logoWidth, logoHeight, TFT_BLUE);
}
//------------------------------------------------------------------------------------------
