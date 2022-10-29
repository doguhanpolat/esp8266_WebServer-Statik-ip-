/*
 * Created by Doğuhan POLAT
 * 
 * Github: https://github.com/doguhanpolat
 *
*/


//Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid     = "Polat2";      // Replace with SSID
const char* password = "/-polat9562/-";  // Replace with WiFi Password


IPAddress gateway(192, 168, 1, 1);                  // Default Gateway
IPAddress local_IP(192, 168, 1, 184);             // Static IP Address for ESP8266
IPAddress subnet(255, 255, 0, 0);                 // Subnet Mask

ESP8266WebServer server(80); // Set web server port number to 80.

uint8_t LED1pin = D2;
bool LED1status = LOW; //We define situations.
uint8_t LED2pin = D3;
bool LED2status = LOW;
uint8_t LED3pin = D5;
bool LED3status = LOW;               
uint8_t LED4pin = D6;
bool LED4status = LOW;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);   
  pinMode(LED3pin, OUTPUT);
  pinMode(LED4pin, OUTPUT);           

  Serial.println("connecting to wifi ");
  Serial.println(ssid);

  if (WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Static IP Configured");
  }
  else {
    Serial.println("Static IP Configuration Failed");
  }
  
  //command required to connect to your local network
  WiFi.begin(ssid, password);
  
 
  //We check that the connection is established.
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print("."); //"." on the screen until the connection is established. We get it out.(Loading)
  }
  Serial.println("");
  Serial.println("WiFi Connected..!");
  Serial.print("Your IP Address: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect); //Server controls after connection is established.
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.on("/led3on", handle_led3on);
  server.on("/led3off", handle_led3off);
  server.on("/led4on", handle_led4on);
  server.on("/led4off", handle_led4off);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server Started");

}
void loop() {
  
  server.handleClient(); 
   if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}
    if(LED3status)
  {digitalWrite(LED3pin, HIGH);}
  else
  {digitalWrite(LED3pin, LOW);}
    if(LED4status)
  {digitalWrite(LED4pin, HIGH);}
  else
  {digitalWrite(LED4pin, LOW);}
}

void handle_OnConnect() {

  LED1status = LOW;
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,LED4status)); 
}
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("D2 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status,LED3status,LED4status)); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("D2 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status,LED3status,LED4status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("D3 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true,LED3status,LED4status)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("D3 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false,LED3status,LED4status)); 
}
void handle_led3on() {
  LED3status = HIGH;
  Serial.println("D5 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,true,LED4status)); 
}

void handle_led3off() {
  LED3status = LOW;
  Serial.println("D5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,false,LED4status)); 
}
void handle_led4on() {
  LED4status = HIGH;
  Serial.println("D6 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,true)); 
}

void handle_led4off() {
  LED4status = LOW;
  Serial.println("D6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status,false)); 
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat,uint8_t led3stat,uint8_t led4stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  
  ptr +="<title>Web Server</title>\n";
  
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  
  ptr +="body{margin-top: 50px;background-image: url('https://img.freepik.com/free-vector/network-mesh-wire-digital-technology-background_1017-27428.jpg?w=2000&t=st=1666631373~exp=1666631973~hmac=16d284cb25630daf0cf2b97358d888edc4bbda780368991243e4faf89485f865');} h1 {color: black;margin: 30px auto 50px;}\n";
  
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c ;border: none;color: white;padding-left: 13px; padding-right: 13px;text-decoration: none;font-size: 28px;margin: 0px auto 25px;cursor: pointer;border-radius: 5px;}\n";
  
  ptr +=".button-on {background-color: #0095c7;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  
  ptr +="p {font-size: 16px;color:black;margin-bottom: 10px;}\n";
  
  ptr +="p1 {font-size: 28px;color: black;}\n";
  ptr +="p2 {font-size: 12px;color: #3f3f3f;}\n";
  
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body bgcolor= efefef style=color:white>\n";
  
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP8266 NodeMCU WebServer</h1>\n";
  if(led1stat)
  {ptr +="<p>Status1: Open</p><a class=\"button button-off\" href=\"/led1off\">Close</a>\n";}
  else
  {ptr +="<p>Status1: Closed</p><a class=\"button button-on\" href=\"/led1on\">Open</a>\n";}

  if(led2stat)
  {ptr +="<p>Status2: Open</p><a class=\"button button-off\" href=\"/led2off\">Close</a>\n";}
  else
  {ptr +="<p>Status2: Closed</p><a class=\"button button-on\" href=\"/led2on\">Open</a>\n";}
  
  if(led3stat)
  {ptr +="<p>Status3: Open</p><a class=\"button button-off\" href=\"/led3off\">Close</a>\n";}
  else
  {ptr +="<p>Status3: Closed</p><a class=\"button button-on\" href=\"/led3on\">Open</a>\n";}

  if(led4stat)
  {ptr +="<p>Status4: Open</p><a class=\"button button-off\" href=\"/led4off\">Close</a>\n";}
  else
  {ptr +="<p>Status4: Closed</p><a class=\"button button-on\" href=\"/led4on\">Open</a>\n";}

  //social media Logo

  ptr +="<br/><br/><p1>Social Media</p1>";
  ptr += "<a target=”github” a href='https://github.com/doguhanpolat'>";
  ptr += "<br/><br/><img src= 'https://logos-world.net/wp-content/uploads/2020/11/GitHub-Logo.png' Z\" width=\"90\" height=\"45\" alt=\"logo\\\">\n";
  ptr += "<a target=”github” a href='https://www.linkedin.com/in/doguhan-polat/'>";
  ptr += "<img src= 'https://logos-world.net/wp-content/uploads/2020/04/Linkedin-Symbol.png' Z\" width=\"85\" height=\"45\" alt=\"logo\\\"></a>\n";
  ptr +="<br/><br/><p2>Copyright (c) 2020 Doguhan POLAT</p2>\n";
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
