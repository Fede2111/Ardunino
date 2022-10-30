#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales para comunicacion serie
#include <Servo.h>           // libreria para controlar el servo

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX,
                              // se crea el objeto miBT para controlar el modulo bluethoot
Servo servoMotor;             // creamos un objeto servoMotor, que sera el servomotor utilizado por el auto

char DATO = 0;  // variable para almacenar caracter recibido
int IN1 = 7;    // Los pines 2 a 7 son utulizados por el modulo L298 encargado del control de motores
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
int i;


void setup() {       //asignacion del modo en que trabajara cada pin de arduino y alguna configuracion extra
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
  servoMotor.attach(9);   // servo en el 9 debido a que por lo leido solo puede trabajar con los pines 9 y 10
  servoMotor.write(110);  // servo a 110 grados que en nuestro caso es donde se encuentra centrado respecto al auto
}


void loop() {
  //Control por medio de bluethoot del auto para realizar cualquier actividad
  if (miBT.available() > 0) {  // si hay informacion disponible desde modulo
    DATO = miBT.read();        // almacena en DATO el caracter recibido desde modulo
    Serial.println(DATO);      // imprime por pantalla del puerto serie el valor leido de bluethoot

    if (DATO == '8') {  // control manual, asigna una velocidad del 60% hacia adelante al auto
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
    if (DATO == '2') {  // control manual, asigna una velocidad del 60% hacia atras al auto
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
    if (DATO == '5') {  // control manual, Detiene los motores del auto
      Serial.println("Stop");
      analogWrite(ENA1, 0);
      analogWrite(ENA2, 0);
      delay(500);
      Serial.println("holi");
    }
    if (DATO == '4') {  // control manual, activa los motores de un solo lado para que gire hacia la izquierda
      Serial.println("Izquierda");
      analogWrite(ENA1, 0);
      analogWrite(ENA2, 0);
      delay(500);
      analogWrite(ENA2, 150);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    if (DATO == '6') {  // control manual, activa los motores de un solo lado para que gire hacia la derecha
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
    if (DATO == '1') {                       // Activacion modo automatico del auto
      analogWrite(ENA1, 120);                //se enciendes los motores para que siga hacia adelante
      analogWrite(ENA2, 120);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      do {                                   //bucle que se repetira mientras la condicion final sea verdadera
        if (miBT.available() > 0)            // linea agregada para que la respuesta en casa de que llegue informacion
          return;                            // por bluethoot, sea mas rapida
        servoMotor.write(80);                // Mueve el servomotor a la pocision de 85 grados
        for (i = 0; i <= 10; i++) {          // bucle utilizado para que por movimiento de servo, se realicen 10 lecturas
          Dist = Ultrasonido();              //  de la distancia y asigandolas a una variable
          if ((Dist < 35) && (Dist >= 0)) {  //  Condicion donde se compara la distancia obtenida anterioremente
            Retroceso();                     // en caso de no cumplir la condicion se ejecuta la funcion retroceso
            analogWrite(ENA1, 120);          // por ultimo el auto vuelve a accionar sus motores hacia adelante
            analogWrite(ENA2, 120);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
          }
        }
        if (miBT.available() > 0)           // se realiza lo mismo que explicado anteriormente,
          return;                           //con la diferencia de mover el servomotor a la posicion de 120 grados
        servoMotor.write(130);
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
      } while (miBT.available() <= 0);  // la condicion de salida del bucle do es que halla llegado infromacion al receptor bluethoot
      servoMotor.write(110);              // se mueve el servo a su posicion centrada
    }
  }
}


void Retroceso() {  //Funcion utilizada para realizar un cambio de sentido del auto
  Serial.println("Pa tras");
  analogWrite(ENA1, 0);  // Detenemos los motores asignandoles el valor 0 a su velociadad,
  analogWrite(ENA2, 0);  //para que no sea tan brusco el cambio de sentido
  delay(100);
  analogWrite(ENA1, 150);  // Encendemos los motores, en este caso en para que haga reversa
  analogWrite(ENA2, 150);  //dutrante 0,3 segundos a una velocidad de 60% de la velocidad maxima de los motores
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
  analogWrite(ENA1, 0);  // volvemos a detener los motores para que el cambio de sentido no sea brusco
  analogWrite(ENA2, 0);
  delay(100);
  analogWrite(ENA1, 150);  // hacemos que una rudas giren hacia adelante y otras hacia atras
  analogWrite(ENA2, 150);  // para que se produzca un giro sobre el eje del auto
  digitalWrite(IN1, LOW);  // este giro se realiza durante 0,3 segunos a un 60% de velocidad
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(300);
}


int Ultrasonido() {  // funcion creada para medir la distancia desde el sensor hacia un objeto
  digitalWrite(TRIG, LOW);
  delay(4);
  digitalWrite(TRIG, HIGH);       // generacion del pulso a enviar
  delay(10);                      // al pin conectado al trigger
  digitalWrite(TRIG, LOW);        // del sensor
  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
  DURACION = DURACION / 2;        // alto en Echo
  DISTANCIA = DURACION / 29.2;    // distancia medida en centimetros
  Serial.println(DISTANCIA);      // se imprime por puerto serial la distancia medida
  delay(50);
  return (DISTANCIA);
}