#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
//Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define max_h 127
#define min_screen 0
#define max_v 63


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//function prototype
void continuous_screen();
void add_design();

void setup() {
  // put your setup code here, to run once:
Wire.begin(5, 4);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false);
display.clearDisplay();

Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(3000);
//display.clearDisplay();
// continuous_screen();
//serial_oled();

add_design();
}

void continuous_screen()
{
display.clearDisplay();  
int i,j,m;
i=0;
j=0;
m=0;
while(i<=128){
 if(j<7){  
display.setTextSize(1); //  font size
display.setTextColor(WHITE); // text colour   
display.setCursor(0,i);
display.println(i);
display.display();
delay(500);  
i+=8;
j++;}
if(j==7){
display.setTextSize(1); //  font size
display.setTextColor(WHITE); // text colour   
display.setCursor(0,i);
display.println(i);
display.display();
delay(500);  
display.clearDisplay();
i+=8;      
j++;
}
if(j>7){
display.setTextSize(1); //  font size
display.setTextColor(WHITE); // text colour   
display.setCursor(0,m);
display.println(i);
display.display();
delay(500);  
i+=8;
m+=8;  
  }
}
delay(1000);
return;
}

void serial_oled(){
Serial.println("Input something to display on oled");
  display.setTextSize(1); //  font size
  display.setTextColor(WHITE); // text colour   
  display.setCursor(0,0);
if(Serial.available()){
  display.clearDisplay();
  String data_serial;
  data_serial=Serial.readString();
  display.println(data_serial);
  display.display();
    display.println("\n");
  display.display();
   }
  delay(4000);  
}

void add_design(){
 
//outside boundary
display.drawLine(min_screen, min_screen, max_h, min_screen, WHITE);//drawLine(x1, y1, x2, y2, color) //vertical l1
display.display();
display.drawLine(min_screen, max_v, max_h, max_v, WHITE);//drawLine(x1, y1, x2, y2, color) //vertical l2
display.display();
display.drawLine(min_screen, min_screen, min_screen, max_v, WHITE);//drawLine(x1, y1, x2, y2, color) //horizontal l1
display.display();
display.drawLine(max_h, min_screen, max_h, max_v, WHITE);//drawLine(x1, y1, x2, y2, color) //horizontal l2
display.display();

//inside boundary
display.drawLine((min_screen+8), (min_screen+8), (min_screen+8), (max_v-8), WHITE);//drawLine(x1, y1, x2, y2, color) //vertical l1 (x contstant)
display.display();
display.drawLine((max_h-8), (min_screen+8), (max_h-8), (max_v-8), WHITE);//drawLine(x1, y1, x2, y2, color) //vertical l2 (x constant)
display.display();
display.drawLine((min_screen+8), (min_screen+8), (max_h-8), (min_screen+8), WHITE);//drawLine(x1, y1, x2, y2, color) //horizontal l1 (y constant)
display.display();
display.drawLine((min_screen+8), (max_v-8), (max_h-8), (max_v-8), WHITE);//drawLine(x1, y1, x2, y2, color) //horizontal l2 (y constant)
display.display();
return;  
}
