#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <stdbool.h>
#include <MeMCore.h>

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);

bool isButtonPressed = false;

void move(int direction, int speed){
  int leftSpeed = 0;
  int rightSpeed = 0;
  //to stop, pass in a speed val of 0
  if(direction == 1){ //go forward
    leftSpeed = speed;
    rightSpeed = speed;  
  } else if(direction == 2){ //go reverse
    leftSpeed = -speed;
    rightSpeed = -speed;  
  } else if(direction == 3){//turn left
    leftSpeed = -speed;
    rightSpeed = speed;  
  } else if(direction == 4){//turn right
    leftSpeed = speed;
    rightSpeed = -speed;
  }
  motor_9.run((9)==M1?(-leftSpeed):(leftSpeed));
  motor_10.run((10)==M1?(-rightSpeed):(rightSpeed));
}
void setup() {
  // put your setup code here, to run once:
  pinMode(A7, INPUT);
      move(3, 100);
    delay(1000);
    move(1, 60);
}

void loop() {
//  // put your main code here, to run repeatedly:
//    if((0^(analogRead(A7)>10?0:1)) && !isButtonPressed){
//        move(1,100);
//        isButtonPressed = true;
//    } else {
//        move(1, 0);  
//        isButtonPressed = false;
//    }
}
