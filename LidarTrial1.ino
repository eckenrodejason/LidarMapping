



/*
 * 2048 = 1/2 rotation (pi/2)
 * 1024 = 1/4 rotation (pi/4)
 * 512 = 1/8
 * 256 = 1/16
 * 128 = 1/32
 * 64 = 1/64
 * 32 = 1/128
 * 16 = 1/256
 * 8 = 1/512
 * 4 = 1/1024
 * 2 = 1/2048
 * 1 = 1/4096

*/

#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <SPI.h>
#include <SD.h>
 

int pos = 0;
int vertPos = 0;
int posArray[180];
int i =0;

Servo verticalServo;
Servo horizontalServo;

LIDARLite lidarLite;
float dist;
float distanceAry[50];
int cal_cnt = 0;

float vap =0; // verticalangle position
float hap=0; // horizontal angle position



File dataLog;



// make the log file dynamic so you can add new log files if one exists r5t 
void verticalPan(){
  int panCount=0;
  
  //changed from 180 to 90 due to incompatible mounting brackets
  for (vertPos =0; vertPos <= 90; vertPos ++){
    //delay(50);
    lidarScan();
    
  //Write to SD Card: vertical angle
  dataLog = SD.open("log2.txt", FILE_WRITE);
  dataLog.println("");
  dataLog.print("Vertical Angle: ");
  dataLog.close();  
  //This is just to double check in the serial monitor (same as sd card data)  
  Serial.println("");
  Serial.print("Vertical Angle: ");
  //If the angle is over 90 degrees add to the count and set the angle back to 0
  if (vap>90){
    panCount= panCount+1;
    //keeps tracks of how many vertical pans we have done
    dataLog = SD.open("log2.txt", FILE_WRITE);
    dataLog.print(panCount);
    dataLog.println(" Pan(s) have been exectuted.");
    dataLog.close();
    
    Serial.print(panCount);
    Serial.println(" Pan(s) have been exectuted.");
    vap=0;
  }
  
  dataLog = SD.open("log2.txt", FILE_WRITE);
  dataLog.print(vap);
  dataLog.println(" Degrees.");
  dataLog.println("");
  dataLog.close();
  
  Serial.print(vap);
  Serial.println(" Degrees.");
  Serial.println("");
  
    verticalServo.write(vertPos);
    vap ++;
    
    delay(50);
    
  }
  vertPos= 0;
}
 

void horizontalPan(){
  int rotCount=0;
  //writing the horizontal angle to the sd card
  dataLog = SD.open("log2.txt", FILE_WRITE);
  dataLog.println("");
  dataLog.print("Horizontal Angle: ");
  dataLog.close();
  
  Serial.println("");
  Serial.print("Horizontal Angle: ");
  //Reset horizontal angle once a rotation has been made
  if(hap>180){
     rotCount++;
     // keeping track of horizontal angle (this is redundant)
    dataLog = SD.open("log2.txt", FILE_WRITE);
    dataLog.print(rotCount);
    dataLog.println(" Rotation(s) as been made.");
    dataLog.close();
     
    Serial.print(rotCount);
    Serial.println(" Rotation(s) as been made.");
    hap=0;
   
  }
  
  dataLog = SD.open("log2.txt", FILE_WRITE);
  dataLog.print(hap);
  dataLog.print(" Degrees");
  dataLog.println("");
  dataLog.close();
  
  
  Serial.print(hap);
  Serial.print(" Degrees");
  Serial.println("");
  horizontalServo.write(pos);
 //lidarScan();
  delay(20);
  hap ++;
  // not executing full 180 degrees here. executing 
  pos = pos +5;  
  
   if (pos >= 180){
    pos = 0;
    horizontalServo.write(pos);
  }
  verticalPan();
  
  
}


void lidarScan(){
  int counter=0;
  
  while(counter<1){
  
  
   if ( cal_cnt == 0 ) {
    dist = lidarLite.distance();      // With bias correction
  } else {
    dist = lidarLite.distance(false); // Without bias correction
  }
  cal_cnt++;
  cal_cnt = cal_cnt % 100;
  float distArray[1000];
  int i = 0;
  distArray[i]=dist;
  distanceAry[i]=dist;
  i++;

  //display Distance and wrtie it to the sd card. 
  dataLog = SD.open("log2.txt", FILE_WRITE);
  dataLog.print("Distance: ");
  dataLog.print(dist);
  dataLog.println(" cm");
  dataLog.close();
  
  
  // serial monitor printing
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  delay(10);
    
    counter++;
}

}
//This is not being used as of now. Going t write this in python instead
void convertToCartesian(float vangle, float hangle, float dist){
  
    float temp;
  
    float radius = dist;

    float xpos = radius*cos(hangle);
    float ypos = radius* sin(vangle);
    float zpos = temp;

  
}


void setup() {

    
  Serial.begin(9600);

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  
  verticalServo.attach(6);
  //horizontalServo.attach(7);

      lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
      lidarLite.configure(0); // Change this number to try out alternate configurations


  
  Serial.println("Initializing SD Card...");
  if(!SD.begin(10)){
   Serial.println("Card Failed or not present.");
  return; 
  }
  Serial.println("Card Initialized.");
  
  

}

void loop() {
//  
//  if (isDone = false){
//    
horizontalPan();


  
}

