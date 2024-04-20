#include <max6675.h>
#include <Arduino.h>
#include "../include/PID.h"

#define pinoSO 8
#define pinoCS  9 
#define pinoCLK 10
#define dimmer 4

MAX6675 termoK(pinoCLK, pinoCS, pinoSO);

volatile double pv, lasTime, potShoot;
double Kp,Ki,Kd;
int alignTime;

PID control(Kp,Ki,Kd);

void zeroCross()
{
  alignTime++;
  if (alignTime>24){//tempo de amostragem do MAX6675

    potShoot = control.getControlSignal();
    Serial.println(potShoot);
    alignTime=0;
  }
    delayMicroseconds(potShoot);
    digitalWrite(dimmer, HIGH);
    delayMicroseconds(1000);
    digitalWrite(dimmer, LOW);
}

void sP(){
  
  int set = 0;
  while(Serial.available()>0){
    static char message[3];
    static unsigned int message_pos = 0;

    char inByte = Serial.read();

    if ( inByte != '\n' && (message_pos < 3 - 1) ){
      message[message_pos] = inByte;
      message_pos++;
    }
    else {
      message[message_pos] = '\0';
      set = atoi(message);
      message_pos = 0;
    }
      delayMicroseconds(1000000);
  }
  if(set<=100) control.setPoint(set);
  Serial.println("Novo setpoint: " + set);
  delayMicroseconds(5000000);
}

void setup() {
  Serial.begin(9600);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  potShoot = 0;
  lasTime = millis();
  alignTime=0;
  control.setConstants(100,0,0);
  control.setPoint(50);
  pinMode(dimmer, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(2),zeroCross,RISING);
  //attachInterrupt(digitalPinToInterrupt(3),sP, RISING);
}

void loop() {
  
  //if (millis()-lasTime>1000){
    lasTime = millis();
    pv = termoK.readCelsius();
  //} 
    Serial.println(pv);
    control.loadSample(pv);
    delay(1000);
}