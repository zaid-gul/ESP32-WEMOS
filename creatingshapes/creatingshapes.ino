#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
//Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//global variables




//function prototype
void intro_screen();
void scroll_text();
void lines();
void rectangle();
void circle();
void triangle();
void invert_display();


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
}

void loop() {
  // put your main code here, to run repeatedly:

//call required functions
//intro_screen();
//lines();
//rectangle();  
circle();
//triangle();
//invert_display();

display.clearDisplay();
}


void intro_screen()
{
display.setTextSize(2); //font size
display.setTextColor(WHITE); //text colour
display.setCursor(0,0);
display.println("Loading");
display.display();
display.setTextSize(1); //font size   
display.setCursor(0,16);
display.println("Please Wait");
display.display(); 

for(int i=0; i<=127; i++)
{
display.drawPixel(i, 32, WHITE);
display.display();
delay(20);
}

for (int j=127; j>=0; j--)
{
display.drawPixel(j, 40, WHITE);
display.display();
delay(20);
}

display.drawLine(0, 63, 127, 63, WHITE);//drawLine(x1, y1, x2, y2, color)
display.display();
delay(500);

//initializing array
int array_1[16];
int m,ip;
m=0;
array_1[0]=array_1[1]=array_1[2]=array_1[3]=array_1[4]=array_1[5]=array_1[6]=array_1[7]=16; // setting array elements to value of 16
array_1[8]=array_1[9]=array_1[10]=array_1[11]=array_1[12]=array_1[13]=array_1[14]=array_1[15]=17; // setting array elements to value of 17

for (ip=0; ip<=15; ip++){
if(m<=127){
display.setCursor(m,48);  
display.write(array_1[ip]);
display.display();
delay(100);
m+=8;
}
}

delay(2000);
return;
}

void scroll_text(){
  display.clearDisplay();
  display.setTextSize(1); //font size
  display.setTextColor(WHITE); //text colour
  display.setCursor(0,0);
  display.println("Loading");
  display.println("Please Wait");
  display.display();
  display.startscrollright(0x00, 0x1e);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x1e);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000); 
return;
}

void lines(){
display.clearDisplay();
delay(1000);
display.drawLine(0, 0, 127, 63, WHITE);//drawLine(x1, y1, x2, y2, color)
display.display();
display.drawLine(0, 63, 127, 0, WHITE);//drawLine(x1, y1, x2, y2, color)
display.display();
display.drawLine(63, 0, 63, 63, WHITE);//drawLine(x1, y1, x2, y2, color)
display.display();
display.drawLine(0, 31, 31, 127, WHITE);//drawLine(x1, y1, x2, y2, color)
display.display();
delay(2000);
return;
}

void rectangle(){
display.clearDisplay();
delay(1000);
display.drawRect(7, 8, 50, 30, WHITE);//drawRect(x, y, width, height, color)
display.display();
display.drawRect(0, 0, 127, 63, WHITE);//drawRect(x, y, width, height, color)
display.display();
delay(2000);
return;
}

void circle(){
display.clearDisplay();
delay(1000);
display.drawCircle(63, 31, 30, WHITE);//drawCircle(x, y, radius, color)
display.display();
display.drawCircle(33, 31, 30, WHITE);//drawCircle(x, y, radius, color)
display.display();
display.drawCircle(93, 31, 30, WHITE);//drawCircle(x, y, radius, color)
display.display();
delay(2000);
return;
}

void triangle(){
display.clearDisplay();
delay(1000);
display.drawTriangle(10, 10, 55, 20, 5, 40, WHITE);//drawTriangle(x1, y1, x2, y2, x3, y3, color)
display.display();
delay(2000);
return;
}

void invert_display(){  
display.invertDisplay(true);
delay(2000);
display.invertDisplay(false);
delay(2000);
return;
}
