#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales
        // para comunicacion serie

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX

char DATO = 0;      // variable para almacenar caracter recibido
int LEDROJO = 2;    // LED rojo a pin digital numero 2
int LEDVERDE = 3;   // LED verde a pin digital numero 3
int BRILLO = 0;

void setup(){
  miBT.begin(9600);    // comunicacion serie entre Arduino y el modulo a 38400 bps
  pinMode(LEDROJO, OUTPUT); // pin 2 como salida
  pinMode(LEDVERDE, OUTPUT);  // pin 3 como salida
}

void loop(){
if (miBT.available()){      // si hay informacion disponible desde modulo
  DATO = miBT.read();   // almacena en DATO el caracter recibido desde modulo

  if( DATO == '1' )   // si el caracter recibido es el numero 1
  digitalWrite(LEDROJO, !digitalRead(LEDROJO));  // enciende LED rojo

  if( DATO == '2' )   // si el caracter recibido es el numero 2
  { BRILLO = BRILLO + 10;
    if (BRILLO > 255)
    BRILLO = 255;
    analogWrite(LEDVERDE,BRILLO);
    }
  if (DATO == '3')
   {BRILLO = BRILLO - 10;
    if (BRILLO < 0)
    BRILLO = 0;
    analogWrite(LEDVERDE,BRILLO);
   }  
}
}
