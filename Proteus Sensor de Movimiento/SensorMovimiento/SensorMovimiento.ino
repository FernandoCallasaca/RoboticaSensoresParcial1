#include <Stepper.h>
// Constantes que no cambian
// Se usan para establecer los pines

const int HCpin = 7;     //Conectamos el pin central del sensor de movimiento
const int LedVerdePin=2;    //Led Verde
const int LedRojoPin=4;     //Led Rojo

//----------------------------------------------
const int stepsPerRevolution = 500;
Stepper myStepper(stepsPerRevolution,9,8,10,11);

//Configuracion
void setup(){
  Serial.begin(9600);  
  pinMode(HCpin, INPUT);

  pinMode(LedVerdePin, OUTPUT);
  pinMode(LedRojoPin, OUTPUT);
}

//Bucle que se repite
void loop(){
  int lectura=digitalRead(HCpin);//lectura  
  //lectura=LOW;
  Serial.print("Lectura: ");
  Serial.println(lectura);     //se muestra si hay movimiento
  
  if(lectura==HIGH){
     digitalWrite(LedVerdePin,LOW);
     digitalWrite(LedRojoPin,HIGH);
     Serial.println("Se activa LED rojo");
     //----------------------------------------------
     //Gira o motor no sentido antihorario      
     myStepper.step(5); 
     Serial.println("Se mueve anti-Horario");
    
  }
  else{
    digitalWrite(LedVerdePin,HIGH);
    digitalWrite(LedRojoPin,LOW);
    Serial.println("Se activa LED verde");
    //----------------------------------------------
    //Gira o motor no sentido horario
    myStepper.step(-5);
    Serial.println("Se mueve Horario");
  
    //----------------------------------------------    
  }
  delay(500);                      
}
