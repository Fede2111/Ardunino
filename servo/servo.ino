#include <Servo.h> 

Servo myservo;

void setup() 
{ 
  myservo.attach(9);
  myservo.write(90);  // set servo to mid-point
} 

void loop() {
  myservo.write(10);
  delay(5000);
  myservo.write(165);
  delay(5000);
  } 
