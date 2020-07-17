#include <Stepper.h>
// Constantes que no cambian
// Se usan para establecer los pines

const int LM35pin = A0;     //Conectamos el pin central
const int LedVerdePin=2;    //Led Verde
const int LedAmarilloPin=3; //Led Amarillo
const int LedRojoPin=4;     //Led Rojo

//----------------------------------------------
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution,8,9,10,11);
int stepCount=0;
//----------------------------------------------

//Variables globales que cambian
float temperatura= 0;       // almacena la temperatura medida

//Configuracion
void setup(){
  Serial.begin(9600);   //
  pinMode(LM35pin, INPUT);
  myStepper.setSpeed(1);
  pinMode(LedVerdePin, OUTPUT);
  pinMode(LedAmarilloPin, OUTPUT);
  pinMode(LedRojoPin, OUTPUT);
}

//Bucle que se repite
void loop(){
  int lectura=analogRead(LM35pin);//lectura
  
  float voltaje=(lectura/1024.0)*5000; //Voltaje entre 0 y 5V
  
  temperatura = voltaje/10; //Temperatura en Celsius
  
  Serial.print("Temperatura: ");
  Serial.print(temperatura);     //se muestra el valor de la temperatura
  Serial.println("C");
 //*********

 //myStepper.step(5);  

 //*********
  
  if(temperatura>20){
    digitalWrite(LedVerdePin,HIGH);
    digitalWrite(LedAmarilloPin,LOW);
    digitalWrite(LedRojoPin,LOW);
    Serial.println("Se activa LED verde");
    //----------------------------------------------
     //Gira o motor no sentido anti-horario a 120 graus
 
    myStepper.step(5);
    Serial.println("Se mueve antiHorario");
  
    //----------------------------------------------
  }
  if(temperatura>=10 && temperatura<=20){
    digitalWrite(LedVerdePin,LOW);
    digitalWrite(LedAmarilloPin,HIGH);
    digitalWrite(LedRojoPin,LOW);
    Serial.println("Se activa LED amarillo");
    Serial.println("No hay movimiento");
  }
  if(temperatura<10){
    digitalWrite(LedVerdePin,LOW);
    digitalWrite(LedAmarilloPin,LOW);
    digitalWrite(LedRojoPin,HIGH);
    Serial.println("Se activa LED rojo");
    //----------------------------------------------
     //Gira o motor no sentido horario a 90 graus

    myStepper.step(-5); 
    Serial.println("Se mueve Horario");
  
    //----------------------------------------------
  }
  delay(1000);                      
}
