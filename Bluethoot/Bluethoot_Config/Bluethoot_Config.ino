#include <SoftwareSerial.h>

/* Programa el modulo bluetooth HC-06: 
CONEXIONES:
ARDUINO BLUETOOTH
   5V      VCC
   GND     GND
  PIN 2    TX
  PIN 3    RX
*/

char NOMBRE[21] = "My-hc06"; // Aquí puedes cambiarle el nombre a tu BLUETOOTH, solo puedes usar 20 caracteres como maximo
char BPS = '4'; // 1=1200 , 2=2400, 3=4800, 4=9600, 5=19200, 6=38400, 7=57600, 8=115200 , Selecciona un numero para definir los baudios
char PASS[5] = "0000"; /* PIN o CLAVE de 4 caracteres numéricos, no exceder los 4 caracteres, 
para mejor funcionamiento dejar la contraseña en "0000"*/

SoftwareSerial blue_hc06(10, 11); //Conexion al bluetooth - PIN 2 a TX y PIN 3 a RXvoid setup()
void setup(){
    blue_hc06.begin(9600); // Inicialmente la comunicacion serial a 9600 Baudios (velocidad de fabrica)
    
    pinMode(13,OUTPUT);
    digitalWrite(13,HIGH); // Enciende el LED 13 durante 4s antes de configurar el Bluetooth
    delay(4000);
    
    digitalWrite(13,LOW); // Apaga el LED 13 para iniciar la programación
    
    blue_hc06.print("AT");  // Inicializa comando AT
    delay(1000);
 
    blue_hc06.print("AT+NAME"); // Configura el nuevo nombre 
    blue_hc06.print(NOMBRE);
    delay(1000);                  // Espera 1 segundo
 
    blue_hc06.print("AT+BAUD");  // Configura la nueva velocidad 
    blue_hc06.print(BPS); 
    delay(1000);
 
    blue_hc06.print("AT+PIN");   // Configura el nuevo PIN
    blue_hc06.print(PASS); 
    delay(1000); 
}
void loop()
{
  digitalWrite(13, !digitalRead(13)); // Cuando termina de configurar el Bluetooth queda el LED 13 parpadeando
  delay(300);
}
