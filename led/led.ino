#define led 2
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
//Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int val = 0;
void intro_screen();
void display_digital_value();

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
// Start I2C Communication SDA = 5 and SCL = 4 on Wemos Lolin32 ESP32 with built-in SSD1306 OLED
Wire.begin(5, 4);
//Initialize display 
// if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
//    Serial.println(F("SSD1306 allocation failed"));
// for(;;);
//  }
//  delay(2000);

display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false);
display.clearDisplay();

////////////////////////////////  

/*
display.setCursor(0,9); //specifying x and y coordinates  
display.println("!!Hello World!!"); // Drawing Display at specified x and y coordinations
display.setCursor(0,45); //specifying x and y coordinates  
display.println("!!Hello World!!"); // Drawing Display at specified x and y coordinations
*/
pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

for (int j=0; j<=4; j++){
digitalWrite(led,!digitalRead(led));
val = digitalRead(led);
Serial.println("Digital value at pin 2 is");
Serial.println(val);
delay(500);
}

intro_screen();
display_digital_value();
display_digital_value();
}

void intro_screen()
{
display.setTextSize(2); //font size
display.setTextColor(WHITE); //text colour
display.setCursor(0,0);
display.println("Welcome\nto\nINNEXIV\nInc.");
display.display();
delay(2000);
display.clearDisplay();
delay(1000);
return;
}

void display_digital_value()
{
display.setTextSize(1); //font size
display.setTextColor(WHITE); //text colour
int y = 0;
for(int i=1; i<=2; i++)//8 columns in oled 
{
digitalWrite(led,!digitalRead(led));
delay(500);
val = digitalRead(led);     
display.setCursor(0,y); //specifying x and y coordinates  
display.println("Digital value at pin 2 is"); // Drawing Display at specified x and y coordinations
display.println(val);
y+=32; 
display.display(); // Display Content
delay(1000);
}
delay(1000);
display.clearDisplay();
delay(1000);
return;
}
