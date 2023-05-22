//# espYraspi
//Scripts para ESP8266 y Raspberri
/**
Sci
**/

/****
Script para controlar unha placa ESP8266 e conectar a unha WiFi predeterminada que xenerara 
a placa Raspberri
*****/

#include <ESP8266WiFi.h>

//Wifi móbil
#define MAX_INTENTOS 50
#define WIFI_SSID "ssd"
#define WIFI_PASS "pass"

// Pins datos
// GPIO14: D5
#define LED 14
int tempo = 500;
bool conectado = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  conectado = conectarWiFi();
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

// Función que se encarga de xestionar a conexión á rede
bool conectarWiFi() { // cambiamos void por bool para que nos responda verdadeiro ou falso
  // put your main code here, to run repeatedly:
  WiFi.mode(WIFI_STA); //Indica modo Station (conexion a outro dispositivo)
  WiFi.disconnect(); // Desconecta unha posible conexion previa
  WiFi.begin(WIFI_SSID, WIFI_PASS); // Inicia a conexion
  Serial.print("\n\nAgardando pola WiFi ");
  int contador = 0; // Comproba estado da conexión e fai varias tentativas
  while(WiFi.status() != WL_CONNECTED and contador < MAX_INTENTOS) {
    contador++;
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  // Informa do estado da conexion e IP en caso de éxito
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
