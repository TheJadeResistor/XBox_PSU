#include "moreButtons.h"

//TFT_eSPI tft = TFT_eSPI(); // Invoke custom library--invoked in "moreButtons.h"

// This is the file name used to store the touch coordinate
// calibration data. Cahnge the name to start a new calibration.
#define CALIBRATION_FILE "/TouchCalData3"

// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL false
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void setup(void){
  Serial.begin(9600);
  tft.init();
  tft.setRotation(1);  // Set the rotation before we calibrate
  touch_calibrate();   // call screen calibration

  buttonArray();

  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);

  pinMode(COM, OUTPUT);
  digitalWrite(COM, LOW);
  
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_7,ADC_ATTEN_DB_0);

  ledcSetup(0, 5000, 8); //LED PWM
  ledcAttachPin(1, 0); //GPIO1 (TX0), channel
  ledcWrite(0, 0);
  
  multiplex(6);
}
//------------------------------------------------------------------------------------------

float v1=0;
float v2=0;
float v3=0;
float v4=0;

float a1=0;
float a2=0;
float a3=0;
float a4=0;
  
//------------------------------------------------------------------------------------------
void loop(){
  runInBackground();    
  uint16_t x, y;
  if (tft.getTouch(&x, &y)){// See if there's any touch data for us
    /*Serial.println("");Serial.print("x:"); Serial.print(x); //print x and y touch value
    Serial.println("");Serial.print("y:"); Serial.print(y);*/
    if(x>225 && x<305){
      if(y>15 && y<60){
        Serial.println("btn1"); 
        allOn();
      }
      else if(y>70 && y<115){
        Serial.println("btn2");
        allOff();
      }
      else if(y>125 && y<170){
        Serial.println("btn3"); 
        CC();
      }
      else if(y>180 && y<225){
        Serial.println("btn4"); 
        More();
      }
    }
  }
  barsAndCh(); //Set up channel displays
  
  v1= getV1();
  v2= getV2();
  v3= getV3();
  v4= getV4();
  
  a1= getA1();
  a2= getA2();
  a3= getA3();
  a4= getA4();
  
  tft.setTextFont(2); //Ch1 MC33167T 1
  tft.setTextSize(1);
  tft.setTextColor(TFT_ORANGE);
  tft.setCursor(15, 5); //x,y
  tft.setTextSize(2);
  tft.setTextColor(TFT_ORANGE,TFT_BLACK); //Black background to erase previous data
  tft.print(v1, 2);tft.print("V  ");
  tft.setCursor(125, 5); 
  tft.print(a1, 2);tft.print("A ");
  tft.setTextSize(1);
  tft.setCursor(15, 35); 
  tft.print((v1*a1), 2);tft.print("W  ");

  tft.setTextSize(2); //Ch2 MC33167T 1
  tft.setCursor(15, 65); 
  tft.setTextColor(TFT_BLUE,TFT_BLACK);
  tft.print(v2, 2);tft.print("V  ");
  tft.setCursor(125, 65); 
  tft.print(a2, 2);tft.print("A ");
  tft.setTextSize(1);
  tft.setCursor(15, 95); 
  tft.print((v2*a2), 2);tft.print("W  ");

  tft.setTextSize(2); //Ch3 LM317T
  tft.setCursor(15, 125); 
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.print(v3, 2);tft.print("V  ");
  tft.setCursor(125, 125);  
  tft.print(a3, 2);tft.print("A ");
  tft.setTextSize(1);
  tft.setCursor(15, 155);
  tft.print((v3*a3), 2);tft.print("W  ");

  tft.setTextSize(2); //Ch4 5V/3.3V
  tft.setCursor(15, 185); 
  tft.setTextColor(TFT_MAGENTA,TFT_BLACK);
  tft.print(v4, 2);tft.print("V  ");
  tft.setCursor(125, 185);
  tft.print(a4, 2);tft.print("A ");
  tft.setTextSize(1);
  tft.setCursor(15, 215);
  tft.print((v4*a4), 2);tft.print("W  ");
}
//------------------------------------------------------------------------------------------


//Main buttons//------------------------------------------------------------------------------------------
void allOn(){
  digitalWrite(12, HIGH); //digital pin 12 (XBOX EN) HIGH
}

void allOff(){
  digitalWrite(12, LOW); //digital pin 12 (XBOX EN) low
}

void CC(){
  uint16_t x, y;
  CCsetup();
  while(true){
    if (tft.getTouch(&x, &y)){
        if(x>17 && x<97 && y>180 && y<225){
          break;
        }
      }
      moreCC();
      runInBackground();    
  }
  buttonArray();
}

void More(){
  uint16_t x, y;
  morePage();
  while(true){
    if (tft.getTouch(&x, &y)){
        if(x>17 && x<97 && y>180 && y<225){
          break;
        }
        if(x>20 && x<150 && y>10 && y<75){
          Temp();
        }
        if(x>170 && x<300 && y>10 && y<75){
          BLE();
        }
        if(x>20 && x<150 && y>90 && y<155){
          Data();
        }
        if(x>170 && x<300 && y>90 && y<155){
          Stats();
        }
    }
    runInBackground();    
  }
  buttonArray();
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void touch_calibrate(){
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}
//------------------------------------------------------------------------------------------
