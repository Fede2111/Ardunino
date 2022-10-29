#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales para comunicacion serie
#include <Servo.h>           // libreria para controlar el servo

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX
Servo servoMotor;

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
long time0;
int i;


void setup() {
  miBT.begin(9600);  // comunicacion serie entre Arduino y el modulo a 9600 bps
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
  servoMotor.write(110);
}


void loop() {  // Es posible enviar una senal continua y asignarla como valor pwm por lo tanto seria viable controlar por bluethoot los 4 motores
  //Control por medio de bluethoot de los motores
  if (miBT.available() > 0) {  // si hay informacion disponible desde modulo
    DATO = miBT.read();        // almacena en DATO el caracter recibido desde modulo
    Serial.println(DATO);
    if (DATO == '8') {  // adelante
      Serial.println("Adelante");
      analogWrite(ENA1, 0);
      analogWrite(ENA2, 0);
      delay(500);
      analogWrite(ENA1, 150);
      analogWrite(ENA2, 150);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    if (DATO == '2') {  // atras
      Serial.println("Atras");
      analogWrite(ENA1, 0);
      analogWrite(ENA2, 0);
      delay(500);
      analogWrite(ENA1, 150);
      analogWrite(ENA2, 150);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    if (DATO == '5') {  //detenerse
      Serial.println("Stop");
      analogWrite(ENA1, 0);
      analogWrite(ENA2, 0);
      delay(500);
      Serial.println("holi");
    }
    if (DATO == '4') {  //girar izquierda
      Serial.println("Izquierda");
      analogWrite(ENA1, 0);
      analogWrite(ENA2, 0);
      delay(500);
      analogWrite(ENA2, 150);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    if (DATO == '6') {  //derecha
      Serial.println("Derecha");
      analogWrite(ENA1, 0);
      analogWrite(ENA2, 0);
      delay(500);
      analogWrite(ENA1, 150);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    if (DATO == '7') {  //Prueba ultrasonido
      do {
        DISTANCIA = Ultrasonido();
        Serial.println(DISTANCIA);
      } while (miBT.available() <= 0);
    }
    if (DATO == '1') {
      analogWrite(ENA1, 100);
      analogWrite(ENA2, 100);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      do {
        if (miBT.available() > 0)
          return;
        servoMotor.write(85);
        for (i = 0; i <= 10; i++) {
          Dist = Ultrasonido();
          if ((Dist < 35) && (Dist >= 0)) {
            Retroceso();
            analogWrite(ENA1, 120);
            analogWrite(ENA2, 120);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
          }
        }
        if (miBT.available() > 0)
          return;
        servoMotor.write(120);
        for (i = 0; i <= 10; i++) {
          Dist = Ultrasonido();
          if ((Dist < 35) && (Dist >= 0)) {
            Retroceso();
            analogWrite(ENA1, 120);
            analogWrite(ENA2, 120);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
          }
        }
      } while (!(miBT.available() > 0));
      return;
    servoMotor.write(100);  
    }
  }
}



void Retroceso() {
  Serial.println("Pa tras");
  analogWrite(ENA1, 0);
  analogWrite(ENA2, 0);
  delay(100);
  analogWrite(ENA1, 150);
  analogWrite(ENA2, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
  analogWrite(ENA1, 0);
  analogWrite(ENA2, 0);
  delay(100);
  analogWrite(ENA1, 150);
  analogWrite(ENA2, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
}



int Ultrasonido() {
  digitalWrite(TRIG, LOW);
  delay(4);
  digitalWrite(TRIG, HIGH);       // generacion del pulso a enviar
  delay(10);                      // al pin conectado al trigger
  digitalWrite(TRIG, LOW);        // del sensor
  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
  DURACION = DURACION / 2;        // alto en Echo
  DISTANCIA = DURACION / 29.2;    // distancia medida en centimetros
  Serial.println(DISTANCIA);
  delay(50);
  return (DISTANCIA);
}