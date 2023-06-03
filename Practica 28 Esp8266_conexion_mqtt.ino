/* Obxectivos:

Programar esp8266 con C++ de Arduíno

Identificar os parámetro necesarios para acceder a unha WiFi móbil desde dispositivos IoT

Familiarizarse cos parámetros básicos da comunicación MQTT

Crear un canal de comunicación MQTT entre un esp8266 e o dashboard dun móbil

Comprender a necesidade de comprobar a conexión e reconexionar en caso necesario, tanto á WiFi como ao servidor MQTT

Instalar e usar as librerías necesarias

Empregar comunicacións serie para obter informacións da placa esp8266

Descrición:

Revisa o video explicativo e segue os pasos indicados para: (a) completar o script da práctica 26 para engadir conectividade MQTT, (b) engadir as bibiliotecas necesarias, (c) codificar as funcións necesarias para o correcto funcionamento da conexión MQTT, (d) engadir o código necesario no loop() para que o servo funcione, (e) conectar o servo ao esp8266 para accionamento, (f) modificar o dashboard para poder interactuar co servo.

Realiza pequenos videos explicando coa túa voz cada un dos apartados anteriores.*/

#include <ESP8266WiFi.h>
#include <Servo.h>
#include <PubSubClient.h>

#define MAX_INTENTOS 50
#define WIFI_SSID "ssd"
#define WIFI_PASS "pass"
#define SERVOPIN 0 
Servo motor;
#define MQTT_PUB_SERVO "wemos/robotica/servo"
#define MQTT_NOME_CLIENTE "Cliente servo"
#define LED 14

int tempo = 500;
bool conectado = false;

void setup() {
 
  Serial.begin(9600); 
  pinMode(LED, OUTPUT);
  motor.attach(SERVOPIN);
  conectado = conectarWiFi();
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(callback);
}

void loop() {
  if(conectado) escintila(tempo);
  else escintila(tempo/10);
}

void escintila(int espera) {
  digitalWrite(LED, HIGH);
  delay(espera);
  digitalWrite(LED, LOW);
  delay(espera);
}


bool conectarWiFi() { 
  WiFi.mode(WIFI_STA); 
  WiFi.disconnect(); 
  WiFi.begin(WIFI_SSID, WIFI_PASS); 
  Serial.print("\n\nAgardando pola WiFi "); 
  int contador = 0; 
  while(WiFi.status() != WL_CONNECTED and contador < MAX_INTENTOS) {
    contador++;
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  if(contador < MAX_INTENTOS) {
    conectado = true;
    Serial.print("Conectado á WiFi coa IP: "); Serial.println(WiFi.localIP());
  }
  else{
    Serial.println("Non se puido conectar á WiFi");
    conectado = false;
  }
  return(conectado); 
}

void callback(String topic, byte* message, unsigned int len) {
  Serial.print("Nova mensaxe no topic: "); Serial.print(topic);
  Serial.print(". Mensaxe: ");
  String mensaxeTmp = "";
  for(int i=0; i < len; i++) {
    Serial.print((char)message[i]);
    mensaxeTmp += (char)message[i];
  }
  Serial.println();
  accionarServo(mensaxeTmp);
}

void reconnect() {
 
  while(!espClient.connected()) {
    Serial.print("Tentando conectar ao servidor MQTT...");
    if(mqttClient.connected(MQTT_NOME_CLIENTE)) {
      Serial.println(" Conectado"); 
  }
}

void accionarServo(String orde) {
 
    orde.toLowerCase();
    if(orde.equals("esquerda")) posicion = 180;
    else if(orde.equals("dereita")) posicion = 0;
    else if(orde.equals("centro")) posicion = 90;
    else {
      int tmp = orde.toInt();
      if(tmp >= 0 && tmp <= 180) posicion = tmp;
      else posicion = 0;
 
  }
motor.write(posicion);
delay(veloc);
}
