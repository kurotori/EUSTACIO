
//Motor Derecho

int MDerAc=9; //ENA
int MDer1=2;  //IN1
int MDer2=3;  //IN2

//Motor Izquierdo

int MIzqAc=10; //ENb
int MIzq1=4;  //IN1
int MIzq2=5;  //IN2


//Funciones de Control


//Activar y Desactivar Motores
void Motores(int valor){
  digitalWrite(MDerAc,valor);
  digitalWrite(MIzqAc,valor);
}

//Moverse Hacia Adelante
void Adelante(int tiempo){
  //Activamos motores
  Motores(1);
//  digitalWrite(MDerAc,HIGH);
//  digitalWrite(MIzqAc,HIGH);
  //Motor Derecho hacia adelante
  digitalWrite(MDer1,HIGH);
  digitalWrite(MDer2,LOW);
  //Motor Izquierdo hacia adelante
  digitalWrite(MIzq1,HIGH);
  digitalWrite(MIzq2,LOW);
  //Tiempo de Espera
  delay(tiempo);
  //Detener Motores y Señales
  Motores(0);
//  digitalWrite(MDerAc,LOW);
//  digitalWrite(MIzqAc,LOW);
  digitalWrite(MDer1,LOW);
  digitalWrite(MIzq1,LOW);
}



void setup() {
  // put your setup code here, to run once:
  pinMode(MDerAc,OUTPUT);
  pinMode(MDer1,OUTPUT);
  pinMode(MDer2,OUTPUT);
  pinMode(MIzqAc,OUTPUT);
  pinMode(MIzq1,OUTPUT);
  pinMode(MIzq2,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}
  
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  //delay(1000);
  Adelante(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
