//sensors
#include "MeMCore.h"

//Define time dely before the next RGB color turns ON to allow LDR to stablise
#define RGBWait 200 //in milliseconds

//Define time delay before taking another LDR reading
#define LDRWait 100 //in milliseconds !!!(Remember to change this value)


MeLightSensor lightSensor(PORT_6); //light sensor
//led one will be color emitter (right side)
//led two will be check indicator - to signal calibration completed (left side)
MeRGBLed led(0,30); //initialise the led


//placeholders for colors detected
int red = 0;
int green = 0;
int blue = 0;

//floats to hold color arrays
int colorArray[] = {0,0,0};
int whiteArray[] = {0,0,0};
int blackArray[] = {0,0,0};
int greyDiff[] = {0,0,0};

char colorStr[3][6] = {" R = ", " G = ", " B = "};

void setup() {
  // put your setup code here, to run once:
  //begin serial communication
  Serial.begin(9600);

  //set the pins and switch them on
  led.setpin(13); //set LED pin
  //lightSensor.lightOn();
  
  setBalance(); //calibration
  
  //indicate that calibration is done
  led.setColorAt(0, 255, 157, 0);
  led.setColorAt(1, 255, 157, 0);
  led.show();
  delay(500);
  led.setColorAt(1, 0,0,0);
  led.show();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay for another 5 seconds for getting ready color objects
  Serial.println("Color sensor is ready.");
  delay(5000);
  readColor();
  for(int i = 0; i < 3; i ++){
    Serial.print(colorStr[i]);
    Serial.print(colorArray[i]); 
  }
  Serial.println("");
}

void readColor(){
//  Serial.println("BlackArray data:");
//  for(int i =0; i <3; i ++){
//    Serial.print(i);
//    Serial.print(" ");
//    Serial.print(blackArray[i]);  
//  }
//
//    Serial.println("\nWhite array data:");
//  for(int i =0; i <3; i ++){
//    Serial.print(i);
//    Serial.print(" ");
//    Serial.print(whiteArray[i]);  
//  }
  int tempReading;
  //red light
  led.setColorAt(0,255,0,0); 
  led.setColorAt(1,255,0,0);
  led.show();
  delay(RGBWait);
  tempReading = getAvgReading(5); //scan 5 times and return the average value
//  Serial.println("Temp reading: ");
//  Serial.print(tempReading);
  colorArray[0] = (tempReading - blackArray[0])/(greyDiff[0])*255; //set it upon 255
  led.setColorAt(0,0,0,0); led.setColorAt(1,0,0,0);
  led.show();
  delay(RGBWait);

  //green light
  led.setColorAt(0,0,255,0);
  led.setColorAt(1,0,255,0);
  led.show();
  delay(RGBWait);
  tempReading = getAvgReading(5); //scan 5 times and return the average value
//  Serial.println("Temp reading: ");
//  Serial.print(tempReading);
  colorArray[1] = (tempReading - blackArray[1])/(greyDiff[1])*255; //set it upon 255
  led.setColorAt(0,0,0,0); 
  led.setColorAt(1,0,0,0);
  led.show();
  delay(RGBWait);

  //blue light
  led.setColorAt(0,0,0,255);
  led.setColorAt(1,0,0,255); 
  led.show();
  delay(RGBWait);
  tempReading = getAvgReading(5); //scan 5 times and return the average value
//  Serial.println("Temp reading: ");
//  Serial.print(tempReading);
//  Serial.print("\t");
//  Serial.print(blackArray[2]);
//  Serial.print("\t");
//  Serial.print(greyDiff[2]);
  
  colorArray[2] = ((tempReading - blackArray[2])/(greyDiff[2]))*255; //set it upon 255
  led.setColorAt(0,0,0,0); led.setColorAt(1,0,0,0);
  led.show();
  delay(RGBWait);
}

void setBalance(){
  //set white balance
  Serial.println("Put White Sample For Calibration ...");
  delay(5000); //delay for 5 seconds for getting sample ready
  //off check indicator during calibration
  led.setColorAt(1,0,0,0);
  led.setColorAt(0,0,0,0);
  led.show();

  //scan the white sample
  //go through one color at a time, set the maximum reading for each color -- red, green and blue to the white array
  scanWhite();

  //done scanning white, time for the black sample
  //set black balance
  Serial.println("Put Black Sample for Calibration ...");
  delay(5000); //delay for 5 seconds for getting sample ready
  //go through one color at a time, set the minimum reading for read, green and blue to the black array
  scanBlack();
  
  //set greyDiff
  setGreyDiff();
}

void scanWhite(){
  //red light
  led.setColorAt(0,255,0,0); led.setColorAt(1,255,0,0);
  led.show();
  delay(RGBWait);
  whiteArray[0] = getAvgReading(5); //scan 5 times and return the average value
  led.setColorAt(0,0,0,0); led.setColorAt(1,0,0,0);
  led.show();
  delay(RGBWait);

  //green light
  led.setColorAt(0,0,255,0); led.setColorAt(1,0,255,0);
  led.show();
  delay(RGBWait);
  whiteArray[1] = getAvgReading(5); //scan 5 times and return the average value
  led.setColorAt(0,0,0,0); led.setColorAt(1,0,0,0);
  led.show();
  delay(RGBWait);

  //blue light
  led.setColorAt(0,0,0,255); led.setColorAt(1,0,0,255);
  led.show();
  delay(RGBWait);
  whiteArray[2] = getAvgReading(5); //scan 5 times and return the average value
  led.setColorAt(0,0,0,0); led.setColorAt(1,0,0,0);
  led.show();
  delay(RGBWait);
}

void scanBlack(){
  //red light
  led.setColorAt(0,255,0,0); led.setColorAt(1,255,0,0);
  led.show();
  delay(RGBWait);
  blackArray[0] = getAvgReading(5); //scan 5 times and return the average value
  led.setColorAt(0,0,0,0); led.setColorAt(1,0,0,0);
  led.show();
  delay(RGBWait);

  //green light
  led.setColorAt(0,0,255,0); led.setColorAt(1,0,255,0);
  led.show();
  delay(RGBWait);
  blackArray[1] = getAvgReading(5); //scan 5 times and return the average value
  led.setColorAt(0,0,0,0); 
  led.setColorAt(1,0,0,0);
  led.show();
  delay(RGBWait);

  //blue light
  led.setColorAt(0,0,0,255); led.setColorAt(1,0,0,255);
  led.show();
  delay(RGBWait);
  blackArray[2] = getAvgReading(5); //scan 5 times and return the average value
  led.setColorAt(0,0,0,0); 
  led.setColorAt(1,0,0,0);
  led.show();
  delay(RGBWait);
}

void setGreyDiff(){
  Serial.println("BlackArray data:");
  for(int i =0; i <3; i ++){
    //Serial.print(i);
    Serial.print(" ");
    Serial.print(blackArray[i]);  
  }

    Serial.println("\nWhite array data:");
  for(int i =0; i <3; i ++){
    //Serial.print(i);
    Serial.print(" ");
    Serial.print(whiteArray[i]);  
  }
  Serial.println("GreyDiff");
  for(int i = 0; i < 3; i ++){
    greyDiff[i] = whiteArray[i] - blackArray[i]; 
    Serial.println(greyDiff[i]); 
  }  
}

//find the average reading for the requested number of times of scanning LDR
int getAvgReading(int times){
  int reading;
  int total = 0;
  int avg = 0;
  
  //take the reading as many times as requested and add them up
  for(int i = 0; i < times; i++){
    reading =  lightSensor.read(); 
    total += reading;
    delay(LDRWait);
  }

  //calculate the avg and return it
  avg = total/times;
  return avg;
}
