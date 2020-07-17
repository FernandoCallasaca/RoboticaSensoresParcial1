#include <Stepper.h>
const int LedVerdePin=2;    //Led Verde
const int LedAmarilloPin=3; //Led Amarillo
const int LedRojoPin=4;     //Led Rojo
const int Trigger = 5;      //Pinj digital 5 para el Trigger del sensor
const int Echo = 6;         //Pinh digital 6 para el Echo del sensor

//----------------------------------------------
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution,8,9,10,11);
int stepCount=0;
//----------------------------------------------

void setup(){
  Serial.begin(9600); //Inicializamos la comunicacion
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);     //pin como entrada
  digitalWrite(Trigger, LOW);//inicializamos el pin con 0

  delayMicroseconds(4);
  pinMode(LedVerdePin, OUTPUT);
  pinMode(LedAmarilloPin, OUTPUT);
  pinMode(LedRojoPin, OUTPUT);
}
 void loop(){
  digitalWrite(LedVerdePin, LOW);
  digitalWrite(LedAmarilloPin, LOW);
  digitalWrite(LedRojoPin, LOW);
  long t; //tiempo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);    //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);

  t = pulseIn(Echo, HIGH);  //Obtenemos el ancho del pulso
  d = t/165;     //escalamos el tiempo a una distancia en cm

  Serial.print("Distancia: ");
  Serial.print(d); //enviamos serialmente el valor de la distancia
  Serial.println();

  if(d<10)
  {
    digitalWrite(LedRojoPin, HIGH);
    myStepper.step(5);
    Serial.println("Se mueve antiHorario");
  }
  else if(d>=10 && d<=15)
  {
    digitalWrite(LedAmarilloPin, HIGH);
    
    Serial.println("No hay Movimiento");
  }
  else
  {
    digitalWrite(LedVerdePin, HIGH);
    myStepper.step(-5); 
    Serial.println("Se mueve Horario");
  }
  delay(500); //hacemos una pausa de 0.5s
 }
