#include <Stepper.h>
#include <LiquidCrystal.h> // se incluye la librería de la LCD


const int LedVerdePin=13;    //Led Verde
const int LedRojoPin=12;     //Led Rojo

LiquidCrystal milcd(6, 7, 5, 4, 3, 2);      // se ulitilizan los pines ( RS, EN, d4, d5, d6, d7)
float datos[2];                             //vector con los datos a enviar

const int sensorPin = A0;                    //se declara una constante entera en donde llega el dato del sensor
int TM1 = A1;
int Tem1;
float humedad;

//----------------------------------------------
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution,8,9,10,11);
//----------------------------------------------

void setup() {
  milcd.begin(16, 2);                       // Fijar el numero de caracteres y de filas
  milcd.print("Humedad (%)=");              // Enviar el mensaje
  milcd.setCursor(0,1);                     //se posiciona el cursor en la fila 1 columna 0
  milcd.print("Temperatura=");             // Enviar el mensaje
  //radio.begin();                            //inicializamos el NRF24L01 
  Serial.begin(9600);                       // se establece la comunicación serial
  //radio.openWritingPipe(direccion);         //Abrimos un canal de escritura 
  pinMode(LedVerdePin,OUTPUT);
  pinMode(LedRojoPin,OUTPUT);
  
}

void loop() {
   digitalWrite(LedVerdePin, LOW);
   digitalWrite(LedRojoPin, LOW);
   humedad = analogRead(sensorPin);     // se hace lectura de la entrada análoga y se carga a la variable humedad
   Tem1= analogRead(TM1);
   float mv1=(Tem1/1024.0)*5000;
   float C1=mv1/10;
   humedad= 100-(humedad*100/1023);           // se hace la conversión de humedad en porcentaje
   milcd.setCursor(12, 0);                    // se posiciona el cursor en la fila 0 columna 12
   milcd.print(humedad);                      // se imprime en la LCD el porcentaje de humedad
   milcd.setCursor(12, 1);
   milcd.print(C1);
   
  datos[0]=C1;                               //cargamos los datos en la variable datos[]
  datos[1]=humedad;

  if(humedad>=50)
    {
      digitalWrite(LedVerdePin,HIGH);
      myStepper.step(-5); 
    }
  else
    {
        if(humedad<50)
        {
          digitalWrite(LedRojoPin,HIGH);
          myStepper.step(5);
        }
    }
  delay(500);
  
}
