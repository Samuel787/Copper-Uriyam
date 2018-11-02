#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMCore.h>

MeUltrasonicSensor ultrasonic_4(PORT_4);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
/*
  // put your main code here, to run repeatedly:
  if((ultrasonic_4.distanceCm()) < 5){
    Serial.print("Less than 5 cm\n");  
  } else {
    Serial.print("More or equal to 5cm\n");  
  }
  */

  //read the ultrasonic value
  Serial.print(ultrasonic_4.distanceCm());
  Serial.print("\n");
  delay(200);
}
