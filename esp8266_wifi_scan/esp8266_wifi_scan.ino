/*
    Scan WiFi networks.
    (c)joaquim.org
*/

extern "C" {
  #include "user_interface.h"
}

#include <ESP8266WiFi.h>
#include "Adafruit_GFX.h"
#include "icons.h"

#include "Adafruit_ILI9341.h"


extern "C" {
  uint16 readvdd33(void);
}

// LCD.
#define TFT_DC 4
#define TFT_CS 5
#define TFT_RST 16

// Use hardware SPI 
Adafruit_ILI9341 lcd = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

typedef struct {
  String SSID;
  uint8_t encryptionType;
  int32_t RSSI;
  int32_t Channel;
  uint8_t Active;
  uint8_t Update;
} NetInfo;

NetInfo networkInfo[30];

typedef struct {
  int32_t Total;
  int32_t RSSI;
} ChannelInfo;

ChannelInfo totalChannel[14],totalChannelOld[14];

#define TEXT_SIZE 10

int initclear = 1;

void setup() {
  system_update_cpu_freq(160);

  pinMode(A0, INPUT);

  Serial.begin(115200);
  lcd.begin();
  lcd.setRotation(1);
  lcd.setTextWrap(false);
  lcd.setTextSize(2);

  lcd.fillScreen(ILI9341_BLACK);
  lcd.drawBitmap(110, 10, wifiBitmap, 100, 70, ILI9341_WHITE);
  //lcd.setFont(&FreeMono9pt7b);
  lcd.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);
  lcd.setCursor(105, 100);
  lcd.print("Wifi Scan");
  lcd.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
  lcd.setCursor(95, 130);
  lcd.print("joaquim.org");
  //lcd.displayUpdate();
  lcd.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  Serial.println("esp8266 Wifi Scan ... ");

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(5000);
  Serial.println("running... ");
  //lcd.fillScreen(ILI9341_BLACK);
  lcd.setCursor(75, 200);
  lcd.println("Scanning WiFi...");
  //lcd.displayUpdate();
  memset( networkInfo, 0x0, sizeof(networkInfo) );
  memset( totalChannel, 0x0, sizeof(totalChannel) );
  memset( totalChannelOld, 0x0, sizeof(totalChannelOld) );
  lcd.setTextSize(1);
}


void showScreen1( int num ) {
  int pos = 0, col = 0, total = 0;
  
  for (int i = 0; i < num; ++i) {
    if (networkInfo[i].Active == 1) {
      
      lcd.fillRect(col, 2 + (TEXT_SIZE * pos), 160, TEXT_SIZE, ILI9341_BLACK);
      
      lcd.setCursor(col, 2 + (TEXT_SIZE * pos));      
      if (networkInfo[i].encryptionType == ENC_TYPE_NONE) {
        lcd.drawBitmap(col, (TEXT_SIZE * pos), unlockBitmap10, 10, 10, ILI9341_GREEN, ILI9341_BLACK);
      } else {
        lcd.drawBitmap(col, (TEXT_SIZE * pos), lockBitmap10, 10, 10, ILI9341_RED, ILI9341_BLACK);
      }
  
      lcd.setCursor(col + 14, 2 + (TEXT_SIZE * pos));
  
      lcd.setTextColor(ILI9341_WHITE, ILI9341_BLACK);

      if (networkInfo[i].RSSI <= -80) {
        lcd.setTextColor(ILI9341_RED, ILI9341_BLACK);
      } else if (networkInfo[i].RSSI >= -80 && networkInfo[i].RSSI < -70) {
        lcd.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);
      } else {
        lcd.setTextColor(ILI9341_GREEN, ILI9341_BLACK);
      }
      
      lcd.print(networkInfo[i].SSID);

      /*Serial.print(networkInfo[i].SSID);
      Serial.print(" : ");
      Serial.println(networkInfo[i].RSSI);*/
      
      //lcd.fillRect(0, (TEXT_SIZE * pos), 240, TEXT_SIZE, ILI9341_BLACK);
      /*if (networkInfo[i].RSSI <= -80) {
        lcd.drawBitmap(120, 20 + (TEXT_SIZE * pos), level1Bitmap, 8, 8, ILI9341_RED, ILI9341_BLACK);
      } else if (networkInfo[i].RSSI >= -80 && networkInfo[i].RSSI < -70) {
        lcd.drawBitmap(120, 20 + (TEXT_SIZE * pos), level2Bitmap, 8, 8, ILI9341_YELLOW, ILI9341_BLACK);
      } else {
        lcd.drawBitmap(120, 20 + (TEXT_SIZE * pos), level3Bitmap, 8, 8, ILI9341_GREEN, ILI9341_BLACK);
      }*/
      pos++;
      total++;
      if ( total > 21) break;
      if ( total == 11 ) {
        col = 160;
        pos = 0;
      }
    }
  }
}



void BubbleSort(NetInfo netInfo[], int numLength) {
  uint8_t i, j, flag = 1;    // set flag to 1 to start first pass
  NetInfo temp;             // holding variable

  for (i = 1; (i <= numLength) && flag; i++)
  {
    flag = 0;
    for (j = 0; j < (numLength - 1); j++)
    {
      if (abs(netInfo[j + 1].RSSI) < abs(netInfo[j].RSSI))    // ascending order simply changes to <
      {
        temp = netInfo[j];             // swap elements
        netInfo[j] = netInfo[j + 1];
        netInfo[j + 1] = temp;
        flag = 1;               // indicates that a swap occurred.
      }
    }
  }
  return;   //arrays are passed to functions by address; nothing is returned
}

void addToArray( NetInfo netInfo ) {
  uint8_t total = 0;
  
  for (int i = 0; i < 30; ++i) {
    if ( networkInfo[i].Active == 1 && (networkInfo[i].SSID == netInfo.SSID) ) {
      networkInfo[i] = netInfo;
      //Serial.print("Found :" + netInfo.SSID + " ");
      //Serial.println(i);
      return;
    } 
  }

  //
  for (int i = 0; i < 30; ++i) {    
    /*Serial.print(i);
    Serial.print(" ");    
    Serial.print(networkInfo[i].Active);
    Serial.println(" " + networkInfo[i].SSID + " ");*/
      
    if ( networkInfo[i].Active == 1 ) {
      total++;
    } 
  }
  
  if ( total < 30 ) {
    networkInfo[total] = netInfo;
    //Serial.print("New :" + netInfo.SSID + " ");
    //Serial.println(total);
  }
  
}


void drawGraphScreen() {
  lcd.drawRect(1, 120, 319, 105, ILI9341_DARKGREY);

  lcd.setCursor(50, 210);
  lcd.setTextColor(ILI9341_PURPLE, ILI9341_BLACK);
  lcd.print("01 02 03 04 05 06 07 08 09 10 11 12 13 14");
  lcd.drawFastHLine(40, 205, 265, ILI9341_ORANGE);
  
  lcd.setTextColor(ILI9341_PURPLE, ILI9341_BLACK);
  lcd.setCursor(15, 195);
  lcd.print("-99");

  lcd.setCursor(15, 185);
  lcd.print("-80");

  lcd.setCursor(15, 175);
  lcd.print("-70");

  lcd.setCursor(15, 165);
  lcd.print("-60");

  lcd.setCursor(15, 155);
  lcd.print("-50");

  lcd.setCursor(15, 145);
  lcd.print("-40");

  lcd.setCursor(15, 135);
  lcd.print("-30");

  lcd.setCursor(15, 125);
  lcd.print("-20");

  lcd.drawFastVLine(40, 125, 80, ILI9341_ORANGE);
  
}


void drawGraph() {

  for (int i = 0; i < 14; ++i) {
    lcd.drawFastVLine(55 + (i * 18), 125, 75, ILI9341_BLACK);

    if ( totalChannelOld[i].Total > 0) {
      lcd.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
      lcd.setCursor(60 + (i * 18), 200 - totalChannelOld[i].RSSI);
      lcd.print("  ");
    }  
    if ( totalChannel[i].Total > 0) {
      
      lcd.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
      lcd.setCursor(60 + (i * 18), 200 - totalChannel[i].RSSI);
      lcd.print(totalChannel[i].Total);
      
      lcd.drawFastVLine(55 + (i * 18), 200 - totalChannel[i].RSSI, totalChannel[i].RSSI, ILI9341_GREEN);
    } 

    totalChannelOld[i] = totalChannel[i];
  }
  
}

float readADC_avg() {
  float adc = 0;
  //Serial.print("read adc :");
  for (int i = 0; i < 10; ++i) {
    adc = adc + analogRead(A0);
  }
  adc = adc / 10;
  /*Serial.print( adc * 9 / 978 );
  Serial.print(" - ");
  Serial.println(adc);*/
  return adc;
}

void loop() {

  int n = WiFi.scanNetworks();
  int m = n;
  NetInfo netInfo;
  
  float value = readADC_avg();

  for (int i = 0; i < 30; ++i) {
    networkInfo[i].Update = 0;
  }

  for (int i = 0; i < 14; ++i) {
   totalChannel[i].Total = 0;
   totalChannel[i].RSSI = 0;
  }

  if ( initclear == 1 ) {
    initclear = 0;
    lcd.fillScreen(ILI9341_BLACK);
    drawGraphScreen();    
  }

  if (n == 0) {
    lcd.setTextSize(2);
    lcd.fillScreen(ILI9341_BLACK);
    lcd.setTextColor(ILI9341_BLUE, ILI9341_BLACK);
    lcd.setCursor(0, 10);
    lcd.println();
    lcd.println();
    lcd.print("No networks found...");
    lcd.println();
    lcd.println("Scanning...");
    lcd.setTextSize(1);
  } else {

    if ( m > 30 ) m = 30;
    for (int i = 0; i < m; ++i) {
      netInfo.SSID = WiFi.SSID(i);
      netInfo.encryptionType = WiFi.encryptionType(i);
      netInfo.RSSI = WiFi.RSSI(i);
      netInfo.Channel = WiFi.channel(i);
      netInfo.Active = 1;
      netInfo.Update = 1;
      addToArray(netInfo);
      totalChannel[netInfo.Channel - 1].Total = totalChannel[netInfo.Channel - 1].Total + 1;
      if ( (netInfo.RSSI + 100) > totalChannel[netInfo.Channel - 1].RSSI ) {
        totalChannel[netInfo.Channel - 1].RSSI = (netInfo.RSSI + 100);
      }
    }
    for (int i = 0; i < 30; ++i) {
      if ( networkInfo[i].Update == 0 ) {
        networkInfo[i].SSID = "";
        networkInfo[i].RSSI = 255;
        networkInfo[i].Active = 0;
      }
    }

    BubbleSort(networkInfo, 30);

    lcd.setCursor(5, 230);
    lcd.setTextColor(ILI9341_CYAN, ILI9341_BLACK);
    lcd.print(n);
    lcd.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    lcd.print(" networks found");
    
    //lcd.fillRect(0, 20, 240, 320, ILI9341_BLACK);

    showScreen1(30);

    drawGraph();
    
    lcd.drawBitmap(235, 228, battBitmap10, 20, 10, ILI9341_BLUE, ILI9341_BLACK);
    lcd.setCursor(260, 230);
    lcd.setTextColor(ILI9341_BLUE, ILI9341_BLACK);    
    lcd.print(value * 9 / 945);
    lcd.print(" V");
       
  }

}
