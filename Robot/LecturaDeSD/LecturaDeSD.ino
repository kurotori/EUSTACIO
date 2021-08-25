#include <Ticker.h>

#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <WiFi.h>


#define LED_PIN_R 14
#define LED_PIN_G 12
#define LED_PIN_B 13

String datosW[2];

Ticker ledRojoOK( parpadeoLed(LED_PIN_R), 500 );

//Función para controlar el parpadeo de los LEDs
void parpadeoLed(int pinLed){
  digitalWrite(pinLed, !digitalRead(pinLed));
}

//Función para escanear las redes WiFi cercanas
bool escanearWifi(){
  Serial.println("Escaneando redes WiFi...");
    bool res = false;
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("Escaneo completo");
    if (n == 0) {
        Serial.println("ERROR: No se encuentran redes WiFi");
        return res;
    } else {
        Serial.print(n);
        Serial.println(" redes disponibles.");
        Serial.print("Buscando red ");
        Serial.print(datosW[0]);
        Serial.println(" de la configuración.");
        
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            datosW[0].trim();
            if( WiFi.SSID(i) == datosW[0] ){
              Serial.print("Red registrada: ");
              res = true;
              }
              else{
                Serial.print("Red desconocida: ");
              }
            Serial.println(WiFi.SSID(i));
        }
    }
    Serial.println("");
    return res;
}



bool conectarWifi(const char* ssid, const char* pass){
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
        parpadeoLed(LED_PIN_B);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    return WiFi.status();
}



bool leerArchivoWiFi(fs::FS &fs, const char * path){
    
    Serial.printf("Accediendo al archivo: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return false;
    }
    int lineas = 0;
    char ch;
    while(file.available()){
        ch=file.read();
        if(ch == '\n'){
          lineas++;
        }
        else{
          datosW[lineas] = datosW[lineas] + ch;
        }
    }
    file.close();
    return true;
}


//Función para inicializar al módulo lector de tarjetas SD
bool inicializarSd(){
  if(!SD.begin()){
        Serial.println("Error: No se pudo montar tarjeta SD");
        return false;
    }
    
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("Error: No hay tarjeta SD en el lector");
        return false;
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("Tamaño de tarjeta SD: %lluMB\n", cardSize);
    return true;
}

void inicializarWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
      
  Serial.begin(115200);
  Serial.println("Inicializando");
 
  
    // WiFi - Fase 1: Pasar a modo cliente y prepararse para la conexión a la red
    //  de la configuración
    digitalWrite(LED_PIN_R, HIGH);
    inicializarWifi();
    
    //Variables para los datos de la configuración de red
    const char* ssid;
    const char* pass;

    //Inicializando SD
    digitalWrite(LED_PIN_G, HIGH);
    
    if( !inicializarSd() ){
      while(true){
          digitalWrite(LED_PIN_G, !digitalRead(LED_PIN_R));
          delay(250);
        }
    }
    else{
        if( leerArchivoWiFi(SD,"/wifi.txt" )){
          ssid = datosW[0].c_str();
          pass = datosW[1].c_str();
          digitalWrite(LED_PIN_G, HIGH);
        }
    }

    
    //WiFi - Fase 2 - Conexión a la red obtenida de la configuración
    digitalWrite(LED_PIN_B, HIGH);
    if( escanearWifi() ){
      conectarWifi(ssid, pass);
    }
    else{
        while(true){
          digitalWrite(LED_PIN_B, !digitalRead(LED_PIN_B));
          delay(250);
        }
    }

}



void loop() {
  // put your main code here, to run repeatedly:


}
