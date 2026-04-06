#include <Servo.h>
#include <Arduino.h>
int coi = 11;
int trigPin = 6;
int echoPin = 7;
long time = 0;
int sp = 0;
int pos = 0;
int ssp = 0;
Servo sv;

void setup() {
  sv.attach(4);
  pinMode(coi, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  sv.write(0);
}

void loop() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  time = pulseIn(echoPin, HIGH);
  sp = time * 0.034 / 2;
  
  Serial.println("khoang cach: " + String(sp) + " cm");

  if (sp > 0 && sp <= 12) {
    
    sv.write(180);
    digitalWrite(coi, HIGH); delay(50); digitalWrite(coi, LOW);
    delay(5000);

    for (pos = 180; pos >= 0; pos--) {
      sv.write(pos); 
      delay(20);

      digitalWrite(trigPin, LOW); delayMicroseconds(2);
      digitalWrite(trigPin, HIGH); delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      time = pulseIn(echoPin, HIGH, 15000); 
      ssp = time * 0.034 / 2;

      if (ssp > 0 && ssp <= 12) { 
        digitalWrite(coi, HIGH); delay(50); digitalWrite(coi, LOW); 
        sv.write(180); 
        delay(5000);   
        pos = 181;   
      }
    }
  } 
  
  delay(5);
}