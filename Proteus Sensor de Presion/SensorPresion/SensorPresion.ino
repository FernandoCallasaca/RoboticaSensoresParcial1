#include <Stepper.h>
#define kpa2atm 0.00986923267
// Constantes que no cambian
// Se usan para establecer los pines

const int Presionpin = A0;     //Conectamos el pin central
const int LedVerdePin=2;    //Led Verde
const int LedAmarilloPin=3; //Led Amarillo
const int LedRojoPin=4;     //Led Rojo

//----------------------------------------------
const int stepsPerRevolution = 500;
Stepper myStepper(stepsPerRevolution,9,8,10,11);

//----------------------------------------------

//Variables globales que cambian
// variables
int val;
float pkPa;
float pAtm;
//Configuracion
void setup(){
  Serial.begin(9600);   //
  pinMode(Presionpin, INPUT);

  pinMode(LedVerdePin, OUTPUT);
  pinMode(LedAmarilloPin, OUTPUT);
  pinMode(LedRojoPin, OUTPUT);
}

//Bucle que se repite
void loop(){
  val = analogRead(Presionpin);
  pkPa = ((float)val/(float)1023+0.095)/0.009;
  //pkPa = ((float)val*125/1031);  
  Serial.print("lectura: ");
  Serial.println(val); 
  
  Serial.print("Presion: ");
  Serial.print(pkPa);     //se muestra el valor de la temperatura
  Serial.println("kPa");
  
  if(pkPa<96){
    digitalWrite(LedVerdePin,HIGH);
    digitalWrite(LedAmarilloPin,LOW);
    digitalWrite(LedRojoPin,LOW);
    Serial.println("Se activa LED verde");
    //----------------------------------------------
    //Gira o motor no sentido horario
    myStepper.step(-5);
    Serial.println("Se mueve Horario");
  
    //----------------------------------------------
  }
  else{
    if(pkPa>=96 && pkPa<97){
          digitalWrite(LedVerdePin,LOW);
          digitalWrite(LedAmarilloPin,HIGH);
          digitalWrite(LedRojoPin,LOW);
          Serial.println("Se activa LED amarillo");
          Serial.println("No hay movimiento");
      }
    else{
          digitalWrite(LedVerdePin,LOW);
          digitalWrite(LedAmarilloPin,LOW);
          digitalWrite(LedRojoPin,HIGH);
          Serial.println("Se activa LED rojo");
          //----------------------------------------------
           //Gira o motor no sentido antihorario
      
          myStepper.step(5); 
          Serial.println("Se mueve anti-Horario");
      }
  }
  Serial.println("----------------");
  delay(500);                      
}
