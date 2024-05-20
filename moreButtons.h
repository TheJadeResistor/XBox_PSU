#include "bitmaps.h"
#include "evenMoreButtons.h"

//https://www.iotstarters.com/controlling-esp32-via-bluetooth-using-blynk/

static int counter=0;
extern int mins=3;
extern unsigned long previousMillis = 0;
static unsigned long currentMillis = 0;

int MUX_A= 17;
int MUX_B= 16; 
int MUX_C= 13; 
int COM= 21;
/*Multiplexer pinout: 2N3904 Transistors
 * Pin 3 (COM)= D21
 * Pin 13 (X0)= A0 B0 C0- LED upper left
 * Pin 14 (X1)= A1 B0 C0- LED lower right
 * Pin 15 (X2)= A0 B1 C0- LED lower left
 * Pin 12 (X3)= A1 B1 C0- LED upper right
 * Pin 1 (X4)= A0 B0 C1- Ch1 (Buck boost 1)
 * Pin 5 (X5)= A1 B0 C1- Ch3 (LM317)
 * Pin 2 (X6)= A0 B1 C1- NC
 * Pin 4 (X7)= A1 B1 C1- Ch2 (Buck boost 2)
 */

void multiplex(int pos){
  digitalWrite(COM, HIGH);
  if(pos== 0){ 
    digitalWrite(MUX_A, LOW);
    digitalWrite(MUX_B, LOW);
    digitalWrite(MUX_C, LOW);
  }
  else if(pos== 1){ 
    digitalWrite(MUX_A, HIGH);
    digitalWrite(MUX_B, LOW);
    digitalWrite(MUX_C, LOW);
  }
  else if(pos== 2){ 
    digitalWrite(MUX_A, LOW);
    digitalWrite(MUX_B, HIGH);
    digitalWrite(MUX_C, LOW);
  }
  else if(pos== 3){ 
    digitalWrite(MUX_A, HIGH);
    digitalWrite(MUX_B, HIGH);
    digitalWrite(MUX_C, LOW);
  }
  else if(pos== 4){ 
    digitalWrite(MUX_A, LOW);
    digitalWrite(MUX_B, LOW);
    digitalWrite(MUX_C, HIGH);
  }
  else if(pos== 5){ 
    digitalWrite(MUX_A, HIGH);
    digitalWrite(MUX_B, LOW);
    digitalWrite(MUX_C, HIGH);
  }
  else if(pos== 6){ 
    digitalWrite(MUX_A, LOW);
    digitalWrite(MUX_B, HIGH);
    digitalWrite(MUX_C, HIGH);
  }
  else if(pos== 7){ 
    digitalWrite(MUX_A, HIGH);
    digitalWrite(MUX_B, HIGH);
    digitalWrite(MUX_C, HIGH);
  }
}

void ledPWM(int led, int dutyCycle){ //0-255
  ledcSetup(0, 5000, 8);
  ledcAttachPin(21, 1); //ledcWrite(0, dutyCycle);
  
}

//------------------------------------------------------------------------------------------
void buttonArray(){
  tft.fillScreen(TFT_BLACK);
  tft.fillRoundRect(215, 5, 100, 230, 8, TFT_DARKGREY); //180 x,y,length, width, radius, color TFT_DARKGREY
  tft.drawRoundRect(224, 14, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(225, 15, 80, 45, 5, TFT_SILVER);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setCursor(256, 19);
  tft.println("All");
  tft.setCursor(239, 31);
  tft.println("channels");
  tft.setCursor(256, 43);
  tft.println("on");
  
  tft.drawRoundRect(224, 69, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(225, 70, 80, 45, 5, TFT_SILVER);
  tft.setCursor(256, 73);
  tft.println("All");
  tft.setCursor(239, 85);
  tft.println("channels");
  tft.setCursor(256, 97);
  tft.println("off");
  
  tft.setTextSize(2);
  tft.drawRoundRect(224, 124, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(225, 125, 80, 45, 5, TFT_SILVER);
  tft.setCursor(248, 132);
  tft.println("CC");
  tft.drawRoundRect(224, 179, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(225, 180, 80, 45, 5, TFT_SILVER);
  tft.setCursor(235, 186);
  tft.println("More");
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void morePage(){
  uint16_t x, y;
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.drawRoundRect(16, 179, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(17, 180, 80, 45, 5, TFT_SILVER);
  tft.setCursor(29, 186);
  tft.println("Back");

  //tft.fillRoundRect(15, 5, 290, 156, 7, TFT_DARKGREY); //backdrop for buttons, flashes a lot
  tft.drawRoundRect(19, 9, 132, 67, 7, TFT_BLUE);
  tft.fillRoundRect(20, 10, 130, 65, 7, TFT_SILVER); //button: xmax:150 xmin:20 ymax:75 ymin:10
  tft.setCursor(50, 27);
  tft.println("Temp");
  
  tft.drawRoundRect(169, 9, 132, 67, 7, TFT_BLUE);    
  tft.fillRoundRect(170, 10, 130, 65, 7, TFT_SILVER); //button: xmax:300 xmin:170 ymax:75 ymin:10
  tft.setCursor(207, 27); //200,27
  tft.println("BLE");  
  
  tft.drawRoundRect(19, 89, 132, 67, 7, TFT_BLUE);
  tft.fillRoundRect(20, 90, 130, 65, 7, TFT_SILVER);  //button: xmax:150 xmin:20 ymax:155 ymin:90
  tft.setCursor(30, 108); //50,108
  tft.println("Data Log"); 

  tft.drawRoundRect(169, 89, 132, 67, 7, TFT_BLUE);
  tft.fillRoundRect(170, 90, 130, 65, 7, TFT_SILVER);  //button: xmax:300 xmin:170 ymax:155 ymin:90
  tft.setCursor(198, 108); //200, 108
  tft.println("Stats"); 

  tft.setTextColor(TFT_BLUE);
  tft.setTextSize(1);
  tft.setCursor(175, 196);
  tft.println("TheJadeResistor"); 
  tft.setCursor(186, 210);
  tft.println("Sage Magras"); 
  // Draw bitmap with top left corner at x,y with foreground only color
  // Bits set to 1 plot as the defined color, bits set to 0 are not plotted
  //              x  y  xbm   xbm width  xbm height  color
  tft.drawXBitmap(270, 185, logo, logoWidth, logoHeight, TFT_BLUE);
  // Erase old one by drawing over with background colour
  //tft.drawXBitmap(x, y, logo, logoWidth, logoHeight, TFT_BLACK);
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void runInBackground(){ //Run data chart and BLE in background looped
  currentMillis = esp_log_timestamp();
  if (currentMillis - previousMillis >= (mins*60*1000)){ //charts data every 3mins (default) (mins*60*1000)
    Serial.println("Mins more data");
    dataArray();
    previousMillis = currentMillis;
  }
  
  if(blynk){
    Blynk.run();
    Blynk.virtualWrite(V1, getV1()); //Channel 1 voltage graphed
    Blynk.virtualWrite(V2, getV2()); //Channel 2 voltage
    Blynk.virtualWrite(V3, getV3()); //Channel 3 voltage

    Blynk.virtualWrite(V4, getA1()); //Channel 1 Amperage graphed
    Blynk.virtualWrite(V5, getA2()); //Channel 2 Amperage
    Blynk.virtualWrite(V6, getA3()); //Channel 3 Amperage
  }
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void Temp(){
  Serial.println("Temp");
  uint16_t x, y;
  moreTemp();
  while(true){
    if (tft.getTouch(&x, &y)){
        if(x>225 && x<305 && y>180 && y<225){ //17 to 97
          break;
        }
    }
    runInBackground();
  }
  morePage();
}

void BLE(){
  Serial.println("BLE");
  uint16_t x, y;
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.drawRoundRect(224, 179, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(225, 180, 80, 45, 5, TFT_SILVER);
  tft.setCursor(237, 186);
  tft.println("Back");
  
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.setCursor(5, 5);
  tft.println(">Restart PSU");
  tft.setCursor(5, 20);
  tft.println(">BLYNK app, BLE module");
  tft.setCursor(5, 35);
  tft.println(">Connect XBox PSU");

  if(counter==0){
    char auth[] = "7hnpeYFITYj9Z5U-30HcC7CNB3PWiivk";
    Serial.println("Waiting for connections...");
    Blynk.setDeviceName("XBOX-PSU");
    Blynk.begin(auth);
    counter++;
  }
  while(true){
    if (tft.getTouch(&x, &y)){
        if(x>225 && x<305 && y>180 && y<225){
          break;
        }
    }
    moreBLE();
    runInBackground();
  }
  morePage();
}

void Data(){
  Serial.println("Data");
  uint16_t x, y;
  dataSetup();
  tft.setTextFont(2);
  int counter1=0;
  int counter2=0;
  while(true){
    if (tft.getTouch(&x, &y)){
        if(x>225 && x<305 && y>180 && y<225){
          break;
        }
        else if(x>65 && x<110 && y>180 && y<225){
          Serial.println("min++");
          if(mins<9){
            mins+=2;
          }
        }
        else if(x>130 && x<175 && y>180 && y<225){
          Serial.println("min--");
          if(mins>2){
            mins-=2;
          }
        }
    }
    moreData();
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.setCursor(8, 208);
    tft.print(mins);tft.print(" Min  "); //3min default
    runInBackground();
  }
  morePage();
}

void Stats(){
  Serial.println("Stats");
  uint16_t x, y;
  moreStats();
  while(true){
    if (tft.getTouch(&x, &y)){
        if(x>225 && x<305 && y>180 && y<225){
          break;
        }
    }
    runInBackground();
  }
  morePage();
}
//------------------------------------------------------------------------------------------

 //Pin 1 (X4)= A0 B0 C1- Ch1 (Buck boost 1)
 //Pin 5 (X5)= A1 B0 C1- Ch3 (LM317)
 //Pin 4 (X7)= A1 B1 C1- Ch2 (Buck boost 2)
 
void moreCC(){
  uint16_t x, y;
  static float CCvals[2];
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  while(true){
    if (tft.getTouch(&x, &y)){
          if(x>17 && x<97 && y>180 && y<225){
            break;
          }
          if(x>115 && x<175 && y>180 && y<225){//test ch1
            Serial.println("Test1");
            multiplex(4); //Test buck boost 1
            CCvals[0]= getA1();
            //delay(50);
            //multiplex(6); //NC
          }
          if(x>185 && x<245 && y>180 && y<225){//test ch2
            Serial.println("Test2");
            multiplex(7); //Test buck boost 2
            CCvals[1]= getA2();
            //delay(50);
            //multiplex(6);
          }
          if(x>255 && x<315 && y>180 && y<225){//test ch3
            Serial.println("Test3");
            multiplex(5); //Test LM317
            CCvals[2]= getA3();
            //delay(50);
            //multiplex(6);
          }
     }
    tft.setTextColor(TFT_BLACK, TFT_ORANGE);
    tft.setCursor(20, 78);
    tft.print(CCvals[0]);//ch1
    tft.setTextColor(TFT_BLACK, TFT_BLUE);
    tft.setCursor(170, 78);
    tft.println(CCvals[1]);//ch2
    tft.setTextColor(TFT_BLACK, TFT_GREEN);
    tft.setCursor(20, 133);
    tft.println(CCvals[2]);//ch3
    tft.setTextColor(TFT_BLACK);
  }
}

void CCsetup(){
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.drawRoundRect(16, 179, 82, 47, 5, TFT_BLUE);
  tft.fillRoundRect(17, 180, 80, 45, 5, TFT_SILVER);
  tft.setCursor(29, 186);
  tft.println("Back");

  tft.fillRoundRect(9, 2, 302, 166, 5, TFT_DARKGREY);
  
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.drawRoundRect(11, 4, 298, 52, 5, TFT_BLUE);
  tft.fillRoundRect(12, 5, 296, 50, 5, TFT_SILVER);//tft.fillRoundRect(12, 115, 296, 50, 5, TFT_SILVER);
  tft.setCursor(25, 15);
  tft.println("CC, C-lim: 10mA-1.2A");

  tft.setTextSize(1);
  tft.drawRoundRect(11, 59, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(12, 60, 145, 50, 5, TFT_ORANGE);//+7  tft.fillRoundRect(12, 5, 145, 50, 5, TFT_ORANGE);
  tft.setCursor(15, 63); //tft.setCursor(15, 8);
  tft.println("Channel 1");
  tft.setTextSize(2);
  //tft.setCursor(20, 78);//+15 tft.setCursor(15, 23);
  //tft.println("0.00");
  tft.setCursor(90, 78);
  tft.println("A");
  
  tft.setTextSize(1);
  tft.drawRoundRect(161, 59, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(162, 60, 145, 50, 5, TFT_BLUE);//tft.fillRoundRect(162, 5, 145, 50, 5, TFT_BLUE);
  tft.setCursor(165, 63);
  tft.println("Channel 2");
  tft.setTextSize(2);
  //tft.setCursor(170, 78);
  //tft.println("0.00");
  tft.setCursor(240, 78);
  tft.println("A");
  
  tft.setTextSize(1);
  tft.drawRoundRect(11, 114, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(12, 115, 145, 50, 5, TFT_GREEN);//tft.fillRoundRect(12, 60, 145, 50, 5, TFT_GREEN);
  tft.setCursor(15, 118);//tft.setCursor(15, 63);
  tft.println("Channel 3");
  tft.setTextSize(2);
  //tft.setCursor(20, 133);//tft.setCursor(15, 78);
  //tft.println("0.00");
  tft.setCursor(90, 133);
  tft.println("A");

  tft.setTextSize(1);
  tft.drawRoundRect(161, 114, 147, 52, 5, TFT_SILVER);
  tft.fillRoundRect(162, 115, 145, 50, 5, TFT_MAGENTA);//tft.fillRoundRect(162, 60, 145, 50, 5, TFT_MAGENTA);
  tft.setCursor(165, 118);
  tft.println("Channel 4");
  tft.setTextSize(2);
  tft.setCursor(170, 133);
  tft.println("None");
  
  tft.drawRoundRect(114, 179, 62, 47, 5, TFT_SILVER);
  tft.fillRoundRect(115, 180, 60, 45, 5, TFT_ORANGE);
  tft.setTextSize(2);
  tft.setCursor(118, 186);
  tft.println("Test");

  tft.drawRoundRect(184, 179, 62, 47, 5, TFT_SILVER);
  tft.fillRoundRect(185, 180, 60, 45, 5, TFT_BLUE);
  tft.setCursor(188, 186);
  tft.println("Test");

  tft.drawRoundRect(254, 179, 62, 47, 5, TFT_SILVER);
  tft.fillRoundRect(255, 180, 60, 45, 5, TFT_GREEN);
  tft.setCursor(258, 186);
  tft.println("Test");
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
/*unsigned int color = 120 << 11; //red << 11
  unsigned int color1 = 120 << 11; //red << 11
  color = 255 << 11 | 0 << 5 | 255; //Create custom colormax 255  
  color1 = 255 << 11 | 255 << 5 | 255;*/  //Colour order is RGB 5+6+5 bits each
void barsAndCh(){
  tft.fillRect(0, 0, 205, 3, TFT_ORANGE); //tft.drawRect for non-filled 320x240   x,y,length, width
  tft.fillRect(0, 0, 10, 50, TFT_ORANGE);
  tft.fillRect(0, 60, 205, 3, TFT_BLUE); //60, 320
  tft.fillRect(0, 60, 10, 50, TFT_BLUE);
  tft.fillRect(0, 120, 205, 3, TFT_GREEN); //120
  tft.fillRect(0, 120, 10, 50, TFT_GREEN);
  tft.fillRect(0, 180, 205, 3, TFT_MAGENTA); //180
  tft.fillRect(0, 180, 10, 50, TFT_MAGENTA);
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(2, 2); 
  tft.println("1");
  tft.setCursor(2, 62);
  tft.println("2");
  tft.setCursor(2, 122); 
  tft.println("3");
  tft.setCursor(2, 182); 
  tft.println("4");
}
//------------------------------------------------------------------------------------------

/*switch(var) {
  case 1:
    //do something when var equals 1
    break;
  case 2:
    //do something when var equals 2
    break;
  default:
    break;
}*/

// Default color definitions
//#define TFT_BLACK       0x0000      /*   0,   0,   0 */
//#define TFT_NAVY        0x000F      /*   0,   0, 128 */
//#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
//#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
//#define TFT_MAROON      0x7800      /* 128,   0,   0 */
//#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
//#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
//#define TFT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
//#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
//#define TFT_BLUE        0x001F      /*   0,   0, 255 */
//#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
//#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
//#define TFT_RED         0xF800      /* 255,   0,   0 */
//#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
//#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
//#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
//#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
//#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
//#define TFT_PINK        0xFE19      /* 255, 192, 203 */    
//#define TFT_BROWN       0x9A60      /* 150,  75,   0 */
//#define TFT_GOLD        0xFEA0      /* 255, 215,   0 */
//#define TFT_SILVER      0xC618      /* 192, 192, 192 */
//#define TFT_SKYBLUE     0x867D      /* 135, 206, 235 */
//#define TFT_VIOLET      0x915C      /* 180,  46, 226 */
