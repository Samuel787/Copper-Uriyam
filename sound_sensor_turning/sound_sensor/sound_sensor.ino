#include "MeMCore.h"
void setup() {
  Serial.begin(9600);
}
int getAvgReadingAo(int times){
  int reading;
  int total = 0;
  //take the reading as many times as requested and add them up
  for(int i = 0; i < times; i++){
    int sensorValue = analogRead(A0);
    total += sensorValue;
    delay(10); 
  }
  //calculate the avg and return it
  return total/times;
}
int getAvgReadingAone(int times){
  int reading;
  int total = 0;

  //take the reading as many times as requested and add them up
  for(int i = 0; i < times; i++){
    int sensorValue = analogRead(A1);
    total += sensorValue;
    delay(10); 
  }
  //calculate the avg and return it
  return total/times;
}
void loop() {
  // put your main code here, to run repeatedly:
  int three_hundred_frequency_voltage = getAvgReadingAo(5);
  int three_thousand_frequency_voltage = getAvgReadingAone(5);
  if(three_hundred_frequency_voltage > three_thousand_frequency_voltage){ 
    left_turn(); 
  }
  else if(three_thousand_frequency_voltage > three_hundred_frequency_voltage){ 
    right_turn(); 
  }
  else{ 
    right_turn_turn(); 
  }
  }
