#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "homepage.h"
#include <Keypad.h>
#include <DFRobot_DHT11.h>
#include <HCSR04.h>
#define Buzzer 14
#define DHT11_PIN 12
DFRobot_DHT11 DHT;
const int Led = 27;
const int trigPin = 32;  
const int echoPin = 35; 
const int button = 22;

const char* ssid = "Anz";
const char* password = "Stink824";

float duration, cm;  

const byte row = 4; 
const byte col = 3; 

char hexaKeys[row][col] = {// keypad buttons matrix array
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[row] = {15,2,4,16}; 
byte colPins[col] = {17,5,18}; 

//initialize class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, row, col); //map out custom keypad 
int pin[4] = {2,5,8,0}, pinEntered[4], passwordCount;

char customKey;
String sensor();
void keypad();
void alarm();
void Password();
void buttonst();
void dht();

WebServer server(80);

void setup(){
  Serial.begin(115200); //baudwidth
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT); 
  pinMode(Buzzer, OUTPUT); 
  pinMode(Led, OUTPUT);   
  pinMode(button,INPUT);
  pinMode(DHT11_PIN, INPUT);

    Serial.begin(115200);
 

 
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
 
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
 
  server.on("/", handleRoot);
  server.on("/Ultrasonic", sensor);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works");
  });
  server.onNotFound(handleNotFound);
 
  server.begin();
  Serial.println("HTTP server started");
}
  

void loop() { 
    server.handleClient();
 //sensor(); 
 buttonst();
 if(cm < 15){
  Serial.print("Motion Detected\n");
 Password();
 }
 //dht();
}

void dht(){
  DHT.read(DHT11_PIN);
  float temperature = DHT.temperature; 
  Serial.print("temp:");
  Serial.print(temperature);
  delay(250);

  if(temperature > 27) {
    alarm();
  }
}
void buttonst(){
  if (digitalRead(button) == HIGH) {
    for(int x=1;x<3;x++){
    digitalWrite(Led, HIGH); 
  delay(50);
  for(int i=0; i<255; i++) { 
    analogWrite(Buzzer, i); //raise the voltage sent out of the pin by 1
    delay(10);  
  }
  digitalWrite(Led, LOW); 
  delay(50);
  for(int i=255; i>0; i--) { 
    analogWrite(Buzzer, i); //lower the voltage sent out of the pin by 1
    delay(10); 
  }
  }
  } 
}
void keypad(){
   customKey = customKeypad.getKey(); //get keypress
  if (customKey){
    Serial.println(customKey);
  }
}


String sensor() {  
	digitalWrite(trigPin, LOW);  
	delayMicroseconds(5);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  

  duration = pulseIn(echoPin, HIGH);  //waits for pulse to get back to rec

  cm = (duration*.0343)/2;  

  Serial.print("Distance: ");  
	Serial.println(cm);  
  Serial.println("cm");  
	delay(250);  

  return String(cm,2);
}  


void alarm(){ 
  for(int x=1;x<3;x++){
    digitalWrite(Led, HIGH); 
  delay(50);
  for(int i=0; i<255; i++) { 
    analogWrite(Buzzer, i); //raise the voltage sent out of the pin by 1
    delay(10);  
  }
  digitalWrite(Led, LOW); 
  delay(50);
  for(int i=255; i>0; i--) { 
    analogWrite(Buzzer, i); //lower the voltage sent out of the pin by 1
    delay(10); 
  }
  }
  
}

void Password(){
  static int pinIndex = 0; 
   
    while(pinIndex < 4) {
        customKey = customKeypad.getKey(); 
       
        if (customKey) {
            pinEntered[pinIndex] = customKey - '0'; // Convert char to integer           
            pinIndex++;  // Move to the next digit
    
        }
    }
        // Check if entered PIN matches the stored PIN
    if (pinEntered[0] == pin[0] && pinEntered[1] == pin[1] && pinEntered[2] == pin[2] && pinEntered[3] == pin[3]) {
        Serial.print("Correct PIN\n");
        for( int x=1; x<=3;x++){
          digitalWrite(Led, HIGH); 
          delay(100);
          digitalWrite(Led, LOW); 
          delay(100);
        }
 
    } else {
        Serial.print("Alarm System ON\n");
    alarm();
    }
   
    pinIndex = 0; // Reset

}

void handledistance() {
  server.send(200, "text/plain", sensor());
}

void handleRoot() {
  server.send(200, "text/html", homePagePart1); // Send the HTML page
}
 
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}