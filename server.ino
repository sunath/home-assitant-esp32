#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

/* Put your SSID & Password */
const char* ssid = "Galaxy M21EFD8PUBUDU";  // Enter SSID here
const char* password = "wqqm2001";  //Enter Password here


Servo servo1;
/* Put IP Address details */
// IPAddress local_ip(192,168,1,1);
// IPAddress gateway(192,168,1,1);
// IPAddress subnet(255,255,255,0);

WebServer server(80);

// uint8_t LED1pin = 4;
// bool LED1status = LOW;

// uint8_t LED2pin = 5;
// bool LED2status = LOW;

uint8_t light1 = 4;
uint8_t light2 = 5;
uint8_t light3 = 13;

// servo motors
uint8_t servoPin1= 15;


// dc motor dor
uint8_t dc_motor_1_1 = 32;
uint8_t dc_motor_1_2 = 33;
uint8_t motor_open_time = 1;


// dc motor fan
uint8_t dc_motor_2_1 = 13;

void setup() {

// setting led pins
  pinMode(light1,OUTPUT);
  pinMode(light2,OUTPUT);
  pinMode(light3,OUTPUT);
  
  // setting dc motor pins
  pinMode(dc_motor_1_1,OUTPUT);
  pinMode(dc_motor_1_2,OUTPUT);

  // setting dc motor fan pins
  pinMode(dc_motor_2_1,OUTPUT);

  servo1.attach(servoPin1);
  Serial.begin(9600);

  Serial.println("Connecting....");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting");
 while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  // WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);

  // lights 
  server.on("/light1on", handle_led1on);
  server.on("/light1off", handle_led1off);

  server.on("/light2on",h_l2on);
  server.on("/light2off",h_l2off);

  server.on("/light3on",h_l3on);
  server.on("/light3off",h_l3off);

  server.on("/door1on",h_door1_on);
  server.on("/door1off",h_door1_of);


  server.on("/door2on",h_door2_on);
  server.on("/door2off",h_door2_off);

  server.on("/fan1on",h_fan_on);
  server.on("/fan1off",h_fan_off);

  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  String welcomeText = "";
  server.send(200, "text/plain",welcomeText); 
}

// lights control handling

void handle_led1on() {
  digitalWrite(light1,HIGH);
  server.send(200, "text/plain","okay"); 
}

void handle_led1off() {
  digitalWrite(light1,LOW);
  server.send(200, "text/plain","okay"); 
}

void h_l2on(){
    digitalWrite(light2,HIGH);
    server.send(200,"text/plain","okay");
}  

void h_l2off(){
  digitalWrite(light2,LOW);
  server.send(200,"text/plain","okay");
}

void h_l3on(){
  digitalWrite(light3,HIGH);
  server.send(200,"text/plain","okay");
}

void h_l3off(){
  digitalWrite(light3,LOW);
  server.send(200,"text/plain","okay");
}

void h_door1_on(){
  servo1.write(0);
  delay(1000);
  server.send(200,"text/plain","true");
}

void h_door1_of(){
  servo1.write(90);
  delay(1000);
  server.send(200,"text/plain","true");
}


void h_door2_on(){
  digitalWrite(dc_motor_1_1,HIGH);
   digitalWrite(dc_motor_1_2,LOW);
  delay(motor_open_time * 1000);
  digitalWrite(dc_motor_1_1,LOW);
  server.send(200,"text/plain","okay");
}

void h_door2_off(){
  digitalWrite(dc_motor_1_1,LOW);
  digitalWrite(dc_motor_1_2,HIGH);
  delay(motor_open_time * 1000);
  digitalWrite(dc_motor_1_2,LOW);
  server.send(200,"text/plain","okay");
}



// handle fan
void h_fan_on(){
  digitalWrite(dc_motor_2_1,HIGH);
  server.send(200,"text/plain","okay");
}

void h_fan_off(){
  digitalWrite(dc_motor_2_1,LOW);
  server.send(200,"text/plain","okay");
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}
