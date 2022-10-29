#include <Servo.h>  // libreria para controlar el servo
#include <SoftwareSerial.h>
Servo servoMotor;
SoftwareSerial mibt(10, 11);

char DATO = 0;  // variable para almacenar caracter recibido
//int VELOCIDAD = 0;
int IN1 = 7;
int IN2 = 4;
int IN3 = 3;
int IN4 = 2;
int ENA1 = 5;
int ENA2 = 6;
int TRIG = 8;  // trigger en pin 8
int ECO = 12;  // echo en pin 12
int DURACION;
int DISTANCIA;
int Dist;


void setup() {
  mibt.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA1, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  Serial.begin(9600);     // inicializacion de comunicacion serial a 9600 bps
    // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);  // servo en el 9 debido a que por lo leido solo puede trabajar en algunos pines solamente
  servoMotor.write(100);
}

void loop() {
  do {
    if (mibt.available())
      break;
    analogWrite(ENA1, 100);
    analogWrite(ENA2, 100);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    servoMotor.write(85);
    Dist = Ultrasonido();
    if ((Dist < 35) || (Dist <= 0))
      break;
    delay(400);
    servoMotor.write(120);
    Dist = Ultrasonido();
    if (Dist < 35 || Dist <= 0)
      break;
    delay(400);
  } while (Ultrasonido() > 35 || Ultrasonido() <= 0);
  Retroceso();
  if (mibt.available())
    break;
}

void Retroceso() {
  analogWrite(ENA1, 0);
  analogWrite(ENA2, 0);
  delay(100);
  analogWrite(ENA1, 150);
  analogWrite(ENA2, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(500);
  analogWrite(ENA1, 0);
  analogWrite(ENA2, 0);
  delay(100);
  analogWrite(ENA1, 150);
  analogWrite(ENA2, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(500);
}

int Ultrasonido() {
  digitalWrite(TRIG, HIGH);  // generacion del pulso a enviar
  delay(1);                  // al pin conectado al trigger
  digitalWrite(TRIG, LOW);   // del sensor

  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
                                  // alto en Echo
  DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
  Serial.println(DISTANCIA);
  delay(200);
  return (DISTANCIA);
}