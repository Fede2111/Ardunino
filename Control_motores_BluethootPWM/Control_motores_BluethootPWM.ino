#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales
        // para comunicacion serie

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX

char DATO = 0;      // variable para almacenar caracter recibido
int VELOCIDAD = 0;
int IN1 = 2;
int IN2 = 3;
int ENA =5;


void setup(){
  miBT.begin(9600);    // comunicacion serie entre Arduino y el modulo a 38400 bps
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
}

void loop(){ // Es posible enviar una senal continua y asignarla como valor pwm por lo tanto seria viable controlar por bluethoot los 4 motores
if (miBT.available()){      // si hay informacion disponible desde modulo
  DATO = miBT.read();   // almacena en DATO el caracter recibido desde modulo

  if( DATO == '2' ){   // si el caracter recibido es el numero 2 Aumenta la velocidad del motor 
  VELOCIDAD = VELOCIDAD + 50;
  if (VELOCIDAD > 255)
  VELOCIDAD = 255;
  analogWrite(ENA, VELOCIDAD);  // asigna al motor la velocidad aumentada
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  }
  if( DATO == '3' ){   // si el caracter recibido es el numero 3 Detiene el motor
  VELOCIDAD = 0;
  analogWrite(ENA, VELOCIDAD);  // Detiene el motor
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  }  
}

}
