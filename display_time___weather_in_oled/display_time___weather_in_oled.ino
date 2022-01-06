#include <WiFi.h>
#include "time.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
//Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// using Wifi hotspot of mobile
/*
const char* ssid     = "esp32";  
const char* password = "12345678";
*/
// using Wifi of RND
const char* ssid     = "esp32";  
const char* password = "12345678";


//for getting time from internet
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 18000;
const int   daylightOffset_sec = 3600;

//to get temperature from internet
const char server[] = "api.openweathermap.org";

// Replace the next line to match your city and 2 letter country code
//String nameOfCity = "Islamabad, PK"; 
// How your nameOfCity variable would look like for Lagos on Nigeria
//String nameOfCity = "Lagos,NG"; 

// Replace the next line with your API Key
const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=Islamabad,PK&APPID=";
const String apiKey = "88f8afcd447b042445199049b91679fb"; 

String text;

int jsonend = 0;
boolean startJson = false;

#define JSON_BUFF_DIMENSION 2500

#define max_h 127
#define min_screen 0
#define max_v 63

int val=0;
void intro_screen();
void display_digital_value();
void printLocalTime();
void add_design();
void get_weather();


void setup() {
  // put your setup code here, to run once:
Wire.begin(5, 4);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false);
display.clearDisplay();


    Serial.begin(115200);
    pinMode(2, OUTPUT);      // set the LED pin mode

    delay(10);
    text.reserve(JSON_BUFF_DIMENSION);
    // We start by connecting to a WiFi network
// to get MAC address of device
   WiFi.mode(WIFI_MODE_STA);
 Serial.println(WiFi.macAddress());

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    display.setTextSize(1); //  font size
display.setTextColor(WHITE); // text colour
display.setCursor(0,0);
display.println("Connecting to");
display.display();
display.setCursor(0,8);
display.println(ssid);
display.display();
delay(1000);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

display.setCursor(0,16);
display.println("WiFi Connected");
display.display();
delay(1000);

display.setCursor(0,24);
display.println("IP Address: \n");
display.println(WiFi.localIP());
display.display();
delay(1000);

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

     display.clearDisplay();
     delay(1000);
//init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
   
}

void loop() {
  // put your main code here, to run repeatedly:
  display.clearDisplay();
  
  printLocalTime();   

 // get_weather();


  
}


void intro_screen()
{
  display.clearDisplay();
delay(1000);
display.setTextSize(2); //  font size
display.setTextColor(WHITE); // text colour
display.setCursor(0,0);
display.println("Web\nServer");
display.display();
delay(2000);
display.clearDisplay();
delay(1000);
return;
}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    display.setTextSize(1); //  font size
display.setTextColor(WHITE); // text colour
display.setCursor(0,0);
display.println("Failed to obtain time");
display.display();
    return;
  }
Serial.println(&timeinfo, "%a, %b %d %y %H:%M:%S");  //a, b, d, y are day, month , date , year respectively. H, M, S represents time.
display.setTextSize(1); //  font size
display.setTextColor(WHITE); // text colour
  add_design();
display.setCursor(40,16);
display.println(&timeinfo, "%A"); //A represents day.
display.display(); 

display.setCursor(31,24);
display.println(&timeinfo, "%d-%b-%y"); //d, b and y represents date-month-year respectively.
display.display(); 

display.setCursor(45,32);
display.println(&timeinfo, "%H:%M"); //represents time.
display.display(); 
delay(30000);      //adding 1 minute delay.
return; 
}


void add_design(){
 
//outside boundary
display.drawLine(0, 0, 127, 0, WHITE);//drawLine(x1, y1, x2, y2, color) //vertical l1
display.display();
display.drawLine(0, 63, 127, 63, WHITE);//drawLine(x1, y1, x2, y2, color) //vertical l2
display.display();
display.drawLine(0, 0, 0, 63, WHITE);//drawLine(x1, y1, x2, y2, color) //horizontal l1
display.display();
display.drawLine(127, 0, 127, 63, WHITE);//drawLine(x1, y1, x2, y2, color) //vertical l1
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
  

//inside boundary
display.drawLine(23, 8, 23, 48, WHITE);//drawLine(x1, y1, x2, y2, color) //vertical l1
display.display();
display.drawLine(95, 8, 95, 48, WHITE);//drawLine(x1, y1, x2, y2, color) //vertical l2
display.display();
display.drawLine(23, 8, 95, 8, WHITE);//drawLine(x1, y1, x2, y2, color) //horizontal l1
display.display();
display.drawLine(23, 48, 95, 48, WHITE);//drawLine(x1, y1, x2, y2, color) //horizontal l2
display.display();
return;  
}


/*
void get_weather(){

  HTTPClient http;
  http.begin(endpoint + apiKey);
  int httpCode = http.GET();
  
  if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
DynamicJsonBuffer jsonBuffer(512);
// Parse JSON object
JsonObject& root = jsonBuffer.parseObject(payload);
if (!root.success()) {
Serial.println(F("Parsing failed!"));
return; 
    
}

float temp = (float)(root["main"]["temp"]) - 273.15; // get temperature in °C
int humidity = root["main"]["humidity"]; // get humidity in %
float pressure = (float)(root["main"]["pressure"]) / 1000; // get pressure in bar
float wind_speed = root["wind"]["speed"]; // get wind speed in m/s
int wind_degree = root["wind"]["deg"]; // get wind degree in °

// print data
Serial.printf("Temperature = %.2f°C\r\n", temp);
Serial.printf("Humidity = %d %%\r\n", humidity);
Serial.printf("Pressure = %.3f bar\r\n", pressure);
Serial.printf("Wind speed = %.1f m/s\r\n", wind_speed);
Serial.printf("Wind degree = %d°\r\n\r\n", wind_degree);

display.clearDisplay();
delay(1000);
display.setCursor(0, 24);
display.printf("Temperature: %5.2f C\r\n", temp);
display.printf("Humidity : %d %%\r\n", humidity);
display.printf("Pressure : %.3fbar\r\n", pressure);
display.printf("Wind speed : %.1f m/s\r\n", wind_speed);
display.printf("Wind degree: %d", wind_degree);
display.drawRect(109, 24, 3, 3, WHITE); // put degree symbol ( ° )
display.drawRect(97, 56, 3, 3, WHITE);
display.display();
      
}

http.end(); //Free the resources 

delay(60000); // wait 1 minute
return;
}

*/
