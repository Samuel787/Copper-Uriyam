#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <stdbool.h>
#include <MeMCore.h>
MeDCMotor motor_9(9);
MeDCMotor motor_10(10);
bool isButtonPressed = false;
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
void setup() {
  // put your setup code here, to run once:
  //succ_left_turn;
  Serial.println(linefollower_2.readSensors());
  
}

void loop() {
  if(((linefollower_2.readSensors())==(0))){
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
