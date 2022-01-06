//Libraries//
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
//Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 

void setup() {
  
//Serial.begin(115200);
// Start I2C Communication SDA = 5 and SCL = 4 on Wemos Lolin32 ESP32 with built-in SSD1306 OLED
Wire.begin(5, 4);
//Initialize display 
// if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
//    Serial.println(F("SSD1306 allocation failed"));
// for(;;);
//  }
////////////////////////////////  
// delay(2000); // adding delay so that OLED has enough time for initialization
display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false);
display.clearDisplay(); //clear display 
display.setTextSize(1); //font size
display.setTextColor(WHITE); //text colour
int y = 0;
for(int i=1; i<=8; i++)//8 columns in oled 
{     
display.setCursor(0,y); //specifying x and y coordinates  
display.println("!!!!!Hello World!!!!!"); // Drawing Display at specified x and y coordinations
y+=8; //
}
/*
display.setCursor(0,9); //specifying x and y coordinates  
display.println("!!Hello World!!"); // Drawing Display at specified x and y coordinations
display.setCursor(0,45); //specifying x and y coordinates  
display.println("!!Hello World!!"); // Drawing Display at specified x and y coordinations
*/
display.display(); // Display Content
}

void loop() {
  // put your main code here, to run repeatedly:

}
