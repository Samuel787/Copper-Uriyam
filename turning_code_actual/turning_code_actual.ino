#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <stdbool.h>
#include <MeMCore.h>
MeDCMotor motor_9(9);
MeDCMotor motor_10(10);
MeUltrasonicSensor ultrasonic_4(4);
MeLineFollower linefollower_2(2);
//turn left 
void left_turn(){ 
  move(3, 100);
  delay(600);     
  move(1,0);
}
// turn right
void right_turn(){ 
  move(4, 100);
  delay(600);     
  move(1,0);
}
//turn 180 right
void right_turn_turn(){ 
  move(4, 100);
  delay(600);     
  move(4,100);
  delay(600); 
  move(1,0);
}

//turn 180 left 
void left_turn_turn(){ 
  move(3, 100);
  delay(500);     
  move(3,100);
  delay(500); 
  move(1,0);
}
//turn succ_right_turn
void succ_right_turn(){ 
  move(4, 100);
  delay(600);  
  move(1, 0);
  while((ultrasonic_4.distanceCm()) > (8)){ 
    move(1,100);
  }
  
  move(1,0); 
  
  move(4,100);
  delay(600); 
  move(1,0);
}
void succ_left_turn(){ 
  move(3, 100);
  delay(500);  
  move(1, 0);
  while((ultrasonic_4.distanceCm()) > (8)){ 
    move(1,100);
  }
  move(1,0); 
  move(3,100);
  delay(500); 
  move(1,0);
}
void move(int direction, int speed)
{
      int leftSpeed = 0;
      int rightSpeed = 0;
      if(direction == 1){
          leftSpeed = speed;
          rightSpeed = speed;
      }else if(direction == 2){
          leftSpeed = -speed;
          rightSpeed = -speed;
      }else if(direction == 3){
          leftSpeed = -speed;
          rightSpeed = speed;
      }else if(direction == 4){
          leftSpeed = speed;
          rightSpeed = -speed;
      }
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
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
//this is the sound_sensing code, that will check for the sound. 
void sound_sensor(){ 
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
void setup() {
  // put your setup code here, to run once:
  //succ_left_turn;  
}

void loop() {
  //once a black strip has been identified, we stop. 
  if(((linefollower_2.readSensors())==(0))){
          move(1,0); 
          //call the color_detection_function. If not then, we go to the sound_sensor part. 
          succ_left_turn();
          //move(4,100);
          //delay(100);
          //move(1,0);
      }
//  // put your main code here, to run repeatedly:
//    if((0^(analogRead(A7)>10?0:1)) && !isButtonPressed){
//        move(1,100);
//        isButtonPressed = true;
//    } else {
//        move(1, 0);  
//        isButtonPressed = false;
//    }
}
