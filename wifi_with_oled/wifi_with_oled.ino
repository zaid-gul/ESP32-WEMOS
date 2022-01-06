#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "WiFi.h"
//Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
// Start I2C Communication SDA = 5 and SCL = 4 on Wemos Lolin32 ESP32 with built-in SSD1306 OLED
Wire.begin(5, 4);
//Initialize display 
 /*if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
 for(;;);
  }
*/
display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false); 
display.clearDisplay();
WiFi.mode(WIFI_STA);
WiFi.disconnect();
delay(100);
display.setTextSize(2); //font size
display.setTextColor(WHITE); //text colour
display.setCursor(0,0);
display.println("Setup done");
display.display();
delay(1000);
display.clearDisplay();

display.setTextSize(1); //font size
display.setTextColor(WHITE); //text colour
// WiFi.scanNetworks will return the number of networks found
int n = WiFi.scanNetworks();
display.setCursor(0,0);
display.println("scan done");
display.display();
if (n == 0) {
display.setCursor(0,8);
display.println("scan done");
display.display();
    } 
    else {
      display.setCursor(0,16);
      display.println(n);
      display.display();
      display.setCursor(9,16);
      display.println(" networks found");
      display.display();
}
}


void loop() {
  // put your main code here, to run repeatedly:
     display.clearDisplay(); 
     int n = WiFi.scanNetworks();
     int b=0;  
      // while(n!=0){
    for (int i = 1; i < n; ++i) {
      // Print SSID and RSSI for each network found
            display.setCursor(0,(i*8));
            display.println(i);
            display.display();
            if(i==7){
            display.clearDisplay();
            display.setCursor(0,(i/8));
            display.println(i);
            display.display();
            }
//            display.setCursor(8,(i+8));
//            display.println(": ");
//            display.display();
//            display.setCursor(16,(i+8));
//            display.println(WiFi.SSID(i));
//            display.display();
      }
      
    // Wait a bit before scanning again
    delay(5000);
}
