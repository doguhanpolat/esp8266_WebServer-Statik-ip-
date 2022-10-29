
# **ESP8266 NodeMCU WebServer Statik Ip**

It is made to control led remotely with Web Server.I used ESP8266 NodeMCU, but it can be used in other versions.

    
## Arduino IDE Settings
I assume you have Arduino IDE on your system. However, the ESP8266 we will be using does not come in the standard installation of the IDE, so we will have to do some additional processing.

Let's add the following address to the `Additional Circuit Boards Manager URLs` section from the `File>Preferences` menu.

http://arduino.esp8266.com/stable/package_esp8266com_index.json    
    
Then find and install ESP8266 from `Tools>Card>Card` Manager:

<img src="https://user-images.githubusercontent.com/109466846/198565319-19e2d64e-f06d-45c4-9466-2b85cd11ef6f.png" width="720" height="415" />

    
Next we need to add ESP8266WebServer, the only library we will use. `Draft > add library > manage libraries`
    
<img src="https://user-images.githubusercontent.com/109466846/198567317-30eaa4e2-0a3d-4f4b-a474-1445bd58a2e7.png" width="720" height="415" />
    
    
 ## Usage
 
## We load the Wi-Fi library
        
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    
    
## Enter the local network information

>You need to modify the following two variables with your network credentials, so that your ESP8266 can establish a connection with your router. 

    const char* ssid = "REPLACE_WITH_YOUR_SSID"; 
    const char* password = "REPLACE_WITH_YOUR_PASSWORD";  

## Setting ESP8266 Static IP Address   
    
    IPAddress gateway(192, 168, 1, 1);                 // Default Gateway
    IPAddress local_IP(192, 168, 1, 184);             // Static IP Address for ESP8266
    IPAddress subnet(255, 255, 0, 0);                // Subnet Mask

**Important:** You need to use an available IP address in your local network and the corresponding gateway.


## Command required to connect to your local network
        
    WiFi.begin(ssid, password);
    
## We check that the connection is established

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print("."); //"." on the screen until the connection is established. We get it out.(Loading)
      }
      
## HTML code

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

      ptr +="<br/><p1>Social Media</p1>";

      ptr += "<a target=”github” a href='https://github.com/doguhanpolat'>";
      ptr += "<br/><br/><img src= 'https://logos-world.net/wp-content/uploads/2020/11/GitHub-Logo.png' Z\" width=\"90\" height=\"45\" alt=\"logo\\\">\n";

      ptr += "<a target=”github” a href='https://www.linkedin.com/in/doguhan-polat/'>";
      ptr += "<img src= 'https://logos-world.net/wp-content/uploads/2020/04/Linkedin-Symbol.png' Z\" width=\"85\" height=\"45\" alt=\"logo\\\">\n";

      ptr +="</div>\n";
      ptr +="</body>\n";
      ptr +="</html>\n";
      return ptr;
    }
    
    
## Finding the ESP IP Address
     
>Press the ESP8266 RESET button, and it will output the ESP IP address on the Serial Monitor

<img src="https://user-images.githubusercontent.com/109466846/198067660-79227588-d5c4-4eff-89eb-1bf0fbac7299.png" width="600" height="325" />

>Copy that IP address, because you need it to access the web server.    
    
## Accessing the Web Server
>Open your browser, type the ESP IP address, and you’ll see the following page. This page is sent by the ESP8266 when you make a request on the ESP IP address.
<img src="https://user-images.githubusercontent.com/109466846/198544867-6b7e2a91-abfc-48e6-a23e-b4fd0b639886.png" width="600" height="325" />

## Mobile view
<img src="https://user-images.githubusercontent.com/109466846/198545875-edf8de3b-8260-4879-a033-714e23194138.png" width="225" height="450" />





## Wiring diagram

<img src="https://user-images.githubusercontent.com/109466846/198069891-f49db3b2-084f-4560-96e1-961bac935cda.png" width="600" height="325" />
    
    
    
    
    
    
    


