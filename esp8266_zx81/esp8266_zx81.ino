/*

  ZX80 Emulator

  (c)joaquim.org
  
*/
extern "C" {
  #include "user_interface.h"
}

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ILI9163.h>
#include "zx81.h"
#include <Ticker.h>
#include "icons.h"

ILI9163   lcd;
ZX81      zx81;

Ticker tickerZX81;

ESP8266WebServer server(80);

#define EMULATOR_CYCLES 100

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

bool loadFromSpiffs(String path){
  String dataType = "text/plain";
  if(path.endsWith("/")) path += "index.html";

  if(path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if(path.endsWith(".html")) dataType = "text/html";
  else if(path.endsWith(".css")) dataType = "text/css";
  else if(path.endsWith(".js")) dataType = "application/javascript";
  else if(path.endsWith(".png")) dataType = "image/png";
  else if(path.endsWith(".gif")) dataType = "image/gif";
  else if(path.endsWith(".jpg")) dataType = "image/jpeg";
  else if(path.endsWith(".ico")) dataType = "image/x-icon";
  else if(path.endsWith(".xml")) dataType = "text/xml";
  else if(path.endsWith(".pdf")) dataType = "application/pdf";
  else if(path.endsWith(".zip")) dataType = "application/zip";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }

  dataFile.close();
  return true;
}

void handleNotFound(){
  if(loadFromSpiffs(server.uri())) return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " NAME:"+server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void readInputs() {
  if (server.hasArg("keyid") && server.hasArg("isshift") && server.hasArg("isfunction")){
    /*String message = "emulatorkey : ";
    message += "\nkeyid: " + server.arg("keyid");
    message += "\nisshift: " + server.arg("isshift");
    message += "\nisfunction: " + server.arg("isfunction");
    Serial.println(message);*/
    
    /*zx81.setKey(
      (unsigned char)atoi(server.arg("keyid").c_str()),
      (unsigned char)atoi(server.arg("isshift").c_str()),
      (unsigned char)atoi(server.arg("isfunction").c_str()));    
    */
    
    zx81.putKeyboard(
      (unsigned char)atoi(server.arg("keyid").c_str()),
      (unsigned char)atoi(server.arg("isshift").c_str()),
      (unsigned char)atoi(server.arg("isfunction").c_str()));
    
    server.send(200, "text/plain", "ok");

    //zx81.setKey(31, 0, 0);
    
  }
}

/* - - - - - - - - - - - - - - - - - - - - - - - */

unsigned char fetch(unsigned short adr) {
  return zx81.readByte(adr);
}

// 8bit memory write
void    store(unsigned short adr, unsigned char val) // 8bit memory write
{
  zx81.writeByte(adr, val);
}
                               
// 16bit memory write
void    store2b(unsigned short adr, unsigned char vh, unsigned char vl)
{
  store(adr, vl);
  store(adr+1, vh);
}

unsigned char  in(unsigned char reg, unsigned short adr)
{
  return zx81.readPort(reg, adr);
}

unsigned int  out(unsigned char reg, unsigned char adr, unsigned char val)
{
  zx81.writePort(adr, val);
  return (0);
}


void updateEmulatorScreen() {
  zx81.showScreen();
}

void runEmulator() {
  for(int i = 0; i <= EMULATOR_CYCLES; i++) {
    zx81.run();   
  }
  zx81.vid_hsync = 1; 
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
const char* ssid     = "xxxxxxx";
const char* password = "xxxxxxx";

void setup() {
  system_update_cpu_freq(160);
  SPIFFS.begin();
  
  lcd.begin();
  lcd.setRotation(lcd.ROT90);
  lcd.clearDisplay(BLACK);
  lcd.drawBitmap(10, 20, logoBitmap, 96, 31, RED);
  // text display tests
  lcd.setTextSize(1);
  lcd.setTextColor(WHITE, BLACK);
  lcd.setCursor(24, 60);
  lcd.println("joaquim.org");

  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
  Serial.println();
  Serial.println();
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/emulatorkey",  HTTP_POST,  [](){ readInputs(); }); 
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  zx81.reset();
  zx81.setLCD(&lcd);
  
  Serial.println();
  Serial.println("running... ");
  //delay(2000);
  lcd.clearDisplay(WHITE);

  //tickerZX81.attach_ms(20, runEmulator);
  //tickerZX81.attach_ms(25, updateEmulatorScreen);
}


/* - - - - - - - - - - - - - - - - - - - - - - - */

void loop() {
  
  server.handleClient();

  for(int i = 0; i <= EMULATOR_CYCLES; i++) {
    zx81.run();   
  }

  zx81.vid_hsync++;
  if ( zx81.vid_hsync > 50 ) {
    zx81.vid_hsync = 0; 
    updateEmulatorScreen();       
    if( zx81.key_sync > 8 ) {
      zx81.resetKey(0x0);
      zx81.key_sync = 0;
    }
  }  
        
  if (Serial.available()) {
    char c = Serial.read();
    if ( c == 'd' ) {          
      //zx81.debug();    
      debug();
    }
    if ( c == 'm' ) {   
      zx81.ShowMEM( Z80_RAM_BASE );      
    }
    if ( c == 'r' ) {   
      zx81.ShowMEM( 0x0 );      
    }
    if ( c == 'a' ) {   
      zx81.GetASM();      
    }
  }

}
