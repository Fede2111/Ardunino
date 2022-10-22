#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales para comunicacion serie
#include <Servo.h> // libreria para controlar el servo 

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX
Servo servoMotor;

char DATO = 0;      // variable para almacenar caracter recibido
//int VELOCIDAD = 0;
int IN1 = 6;
int IN2 = 4;
int IN3 = 3;
int IN4 = 2;
int ENA1 = 5;
int ENA2 = 7;
int TRIG = 8;      // trigger en pin 8
int ECO = 12;      // echo en pin 12
int DURACION;
int DISTANCIA;


void setup(){
  miBT.begin(9600);    // comunicacion serie entre Arduino y el modulo a 9600 bps
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA1,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA2,OUTPUT);
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  Serial.begin(9600);     // inicializacion de comunicacion serial a 9600 bps
    // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
  servoMotor.write(90);
}

void loop(){ // Es posible enviar una senal continua y asignarla como valor pwm por lo tanto seria viable controlar por bluethoot los 4 motores
  
  //control del sensor ultrasonico
  digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
  delay(1);       // al pin conectado al trigger
  digitalWrite(TRIG, LOW);    // del sensor
  
  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
            // alto en Echo
  DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
  Serial.println(DISTANCIA);    // envio de valor de distancia por monitor serial 
  
//Control por medio de bluethoot de los motores
if (miBT.available()){      // si hay informacion disponible desde modulo
  DATO = miBT.read();// almacena en DATO el caracter recibido desde modulo
  Serial.println(DATO);
if (DATO == '8'){// adelante
    analogWrite(ENA1,0);
    analogWrite(ENA2,0);
    delay(500);
    analogWrite(ENA1,200);
    analogWrite(ENA2,200);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    }
if (DATO == '2'){  // atras
    analogWrite(ENA1,0);
    analogWrite(ENA2,0);
    delay(500);
    analogWrite(ENA1,200);
    analogWrite(ENA2,200);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);  
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    }
if (DATO == '5'){//detenerse
    analogWrite(ENA1,0);
    analogWrite(ENA2,0);
    delay(500);
    servoMotor.write(90);
      }
if (DATO == '4'){//girar izquierda
    analogWrite(ENA1,0);
    analogWrite(ENA2,0);
    delay(500);
    analogWrite(ENA2,200);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);  
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
      }
if (DATO == '6'){//derecha 
    analogWrite(ENA1,0);
    analogWrite(ENA2,0);
    delay(500);
    analogWrite(ENA1,200);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);  
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
      }
  //control del servomotor
if (DATO == '7') servoMotor.write(45);
if (DATO == '9') servoMotor.write(135);
    }
  }
