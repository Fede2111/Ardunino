#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales
        // para comunicacion serie

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX

char DATO = 0;      // variable para almacenar caracter recibido
//int VELOCIDAD = 0;
int IN1 = 2;
int IN2 = 3;
int IN3 = 7;
int IN4 = 8;
int ENA1 = 5;
int ENA2 = 6;


void setup(){
  miBT.begin(9600);    // comunicacion serie entre Arduino y el modulo a 9600 bps
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA1,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA2,OUTPUT);
}

void loop(){ // Es posible enviar una senal continua y asignarla como valor pwm por lo tanto seria viable controlar por bluethoot los 4 motores
if (miBT.available()){      // si hay informacion disponible desde modulo
  DATO = miBT.read();   // almacena en DATO el caracter recibido desde modulo
if (DATO == '8'){// adelante
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
if (DATO == '2'){  // atras
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
if (DATO == '5'){//detenerse
    analogWrite(ENA1,0);
    analogWrite(ENA2,0);
    delay(500);
      }
if (DATO == '4'){//girar izquierda
    analogWrite(ENA1,0);
    analogWrite(ENA2,0);
    delay(500);
    analogWrite(ENA2,200);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);  
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
      }
if (DATO == '6'){//derecha 
    analogWrite(ENA1,0);
    analogWrite(ENA2,0);
    delay(500);
    analogWrite(ENA1,200);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);  
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
      }
  /*default:
    analogWrite(ENA1,0);
    analogWrite(ENA2,0);*/    
    }
  }
