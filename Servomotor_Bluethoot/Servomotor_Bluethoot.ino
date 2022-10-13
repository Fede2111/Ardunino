
// Incluímos la librería para poder controlar el servo
#include <Servo.h>
 
// Declaramos la variable para controlar el servo
Servo servoMotor;

int TRIG = 10;      // trigger en pin 10
int ECO = 9;      // echo en pin 9
int LED = 3;      // LED en pin 3
int DURACION;
int DISTANCIA;

void setup()
{
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  pinMode(LED, OUTPUT);   // LED como salida
  Serial.begin(9600);     // inicializacion de comunicacion serial a 9600 bps
  
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
}

void loop()
{
  
  digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
  delay(1);       // al pin conectado al trigger
  digitalWrite(TRIG, LOW);    // del sensor
  
  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
            // alto en Echo
  DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
  Serial.println(DISTANCIA);    // envio de valor de distancia por monitor serial
  delay(200);       // demora entre datos
  if (DISTANCIA < 20 and DISTANCIA > 0) digitalWrite(LED,HIGH);
  else digitalWrite(LED,LOW);
  
  // Desplazamos a la posición 10
  servoMotor.write(10); //Se pone 10 debido a que al llegar al maximo de 180 el servo comienza a trabarse
  // Esperamos 1 segundo
  delay(1000);
  
  // Desplazamos a la posición 90
  servoMotor.write(90);
  // Esperamos 1 segundo
  delay(1000);
  
  // Desplazamos a la posición 170
  servoMotor.write(170); //Se pone 170 debido a que al llegar al maximo de 180 el servo comienza a trabarse
  // Esperamos 1 segundo
  delay(1000);
   
}
