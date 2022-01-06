

/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>
//  #include "time.h"
//  #include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
//Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// using Wifi hotspot of mobile

const char* ssid     = "esp32";  
const char* password = "12345678";

/*
// using Wifi of RND
const char* ssid     = "RND";  
const char* password = "y2kinnexiv2";
*/

//for getting time from internet
//const char* ntpServer = "pool.ntp.org";
//const long  gmtOffset_sec = 3600;
//const int   daylightOffset_sec = 3600;


WiFiServer server(80);

int val=0;
void intro_screen();
void display_digital_value();
//void printLocalTime();

void setup()
{
  Wire.begin(5, 4);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false);
display.clearDisplay();


    Serial.begin(115200);
    pinMode(2, OUTPUT);      // set the LED pin mode

    delay(10);

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

//init and get the time
//  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//  printLocalTime();
  
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
    
    server.begin();

   // Serial.begin(9600);
// Start I2C Communication SDA = 5 and SCL = 4 on Wemos Lolin32 ESP32 with built-in SSD1306 OLED

//  Initialize display 
// if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
//    Serial.println(F("SSD1306 allocation failed"));
// for(;;);
//  }
//  delay(2000);



}

int value = 0;

void loop(){

  //delay(1000);
  //printLocalTime();
      intro_screen();
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

   

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(2, HIGH);               // GET /H turns the LED on
          display_digital_value();
          
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(2, LOW);                // GET /L turns the LED off
          display_digital_value();
          
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
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

void display_digital_value()
{
display.setTextSize(1); //  font size
display.setTextColor(WHITE); // text colour
val = digitalRead(2);     
display.setCursor(0,0); //  specifying x and y coordinates  
display.println("Digital value at pin 2 is"); // Drawing Display at specified x and y coordinations
display.println(val);
// y+=32; 
display.display(); // Display Content
delay(1000);
display.clearDisplay();
delay(1000);
return;
}

//void printLocalTime()
//{
//  struct tm timeinfo;
//  if(!getLocalTime(&timeinfo)){
//    Serial.println("Failed to obtain time");
//    return;
//  }
//  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
//}


/*
int y = 0;
for(int i=1; i<=2; i++)//8 columns in oled 
{
digitalWrite(led,!digitalRead(led));
delay(500);
*/
