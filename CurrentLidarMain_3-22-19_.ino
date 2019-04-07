
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


/*Logic behind the way the lidar scans are kept in order
 * 
 * Okay so here's my thoughts on how to deal with the mass amounts of numbers coming in as the lidr makes readings. 
 * 
 * We know that for every 1 horizontal angle there is 360 vertical readings. 
 *    Where 180values are distances and 180 values are angles. that means A[n+1] is always an angle and A[n] is a distance 
 *    This array only needs 360 floating point values at a time which = 1440bytes of total memory. of 32kb 
 *    Think of the 360 values in the reading as a buffer. 
 *    
 *    Next we need to calculate the actual coordinates of the each point. since we have have 180 sets (x values) of 360 values (y and z values)
 *    We can write each of these sets to a file and because we know the first 360value set starts at horizontal angle 0 and the last 360value set ends at 180
 *    We can infer the x,y and z cooridinates of each point, in relation to the origin. 
 * 
 */










#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <math.h>
#include <SPI.h>
#include <SD.h>


// ********************** Variable Declaration/Initilization *******************************************
int pos = 0;// variable for servo position
int hpos=0;
int vertPos = 0; //
int posArray[180];
int i =0;

int horizontalOriginPos=0;

Servo verticalServo;
Servo horizontalServo;

LIDARLite lidarLite;

float dist;
int cal_cnt = 0;


float vap =0; // verticalangle position
float hap=0; // horizontal angle position

int panCount=0;



//float vertDist_AngleAry[360];

File dataLog;



void writeVerticalToSd(){

  dataLog=SD.open("log3.txt", FILE_WRITE);
  dataLog.println("");
  dataLog.print("Vertical Angle: ");
  dataLog.close();  

  //This is just to double check in the serial monitor (same as sd card data)  
  Serial.println("");
  Serial.print("Vertical Angle: ");

  if (vap>90){
    panCount= panCount+1;
    //keeps tracks of how many vertical pans we have done
    dataLog = SD.open("log3.txt", FILE_WRITE);
    dataLog.print(panCount);
    dataLog.println(" Pan(s) have been exectuted.");
    dataLog.close();
    
    Serial.print(panCount);
    Serial.println(" Pan(s) have been exectuted.");
    vap=0;
  }

  dataLog = SD.open("log3.txt", FILE_WRITE);
  dataLog.print(vap);
  dataLog.println(" Degrees.");
  dataLog.println("");
  dataLog.close();
  
  Serial.print(vap);
  Serial.println(" Degrees.");
  Serial.println("");
  
}



void writeHorizontalToSd(){
  // start writing to the sd card log file
  int rotCount=0;
   dataLog = SD.open("log3.txt", FILE_WRITE);
  dataLog.println("");
  dataLog.print("Horizontal Angle: ");
  dataLog.close();
  
  Serial.println("");
  Serial.print("Horizontal Angle: ");
  //Reset horizontal angle once a rotation has been made
  if(hap>180){
     rotCount++;
     // keeping track of horizontal angle (this is redundant)
    dataLog = SD.open("log3.txt", FILE_WRITE);
    dataLog.print(rotCount);
    dataLog.println(" Rotation(s) as been made.");
    dataLog.close();
     
    Serial.print(rotCount);
    Serial.println(" Rotation(s) as been made.");
    hap=0;
   
  }

  dataLog = SD.open("log3.txt", FILE_WRITE);
  dataLog.print(hap);
  dataLog.print(" Degrees");
  dataLog.println("");
  dataLog.close();
  
  
  Serial.print(hap);
  Serial.print(" Degrees");
  Serial.println("");
}



void writeDistance(){
  dataLog = SD.open("log3.txt", FILE_WRITE);
  dataLog.print("Distance: ");
  dataLog.print(dist);
  dataLog.println(" cm");
  dataLog.close();
  
  
  // serial monitor printing
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");
}



// ************************End Variable Declaration/Initilization****************************************


//*************************Function Declarations*********************************************************


//Vertical servo control
void verticalPan(){
   //lidarScan();
  for (vertPos =0; vertPos <= 180; vertPos ++){
    //delay(50);
    writeVerticalToSd();
    lidarScan();
    verticalServo.write(vertPos);
    vap ++;
    
    delay(50);
    
  }
//  vertPos= 15;
horizontalServo.write(hpos);
hpos++;
}



//Horizontal Servo Control 








void horizontalPan(){


  horizontalServo.write(hpos);
  
  
  delay(20);
  hap ++;

    
   if (hpos <= 180){
//    pos = 0;// reset back to original position
    horizontalOriginPos = 0;
    horizontalServo.write(hpos);
    hpos++;
    Serial.println("i got here");
    verticalPan();
  }
  
  horizontalOriginPos++;
  //Serial.println("Current distance from origin: "+ horizontalOriginPos);
  

}

// Lidar Scanning Function
void lidarScan(){

   if ( cal_cnt == 0 ) {
    dist = lidarLite.distance();      // With bias correction
  } else {
    dist = lidarLite.distance(false); // Without bias correction
  }
  cal_cnt++;
  cal_cnt = cal_cnt % 100;
  float distArray[1000];
  int i = 0;
  //Array that stores distances measured by lidar
  distArray[i]=dist;
  i++;

  //display Distance
  Serial.print(dist);
  Serial.println(" cm");

  delay(10);
    
}

//End Lidar Section 


void setup() {
  
  Serial.begin(9600);
  verticalServo.attach(6);  // vertical panning servo attached to pin 6
  horizontalServo.attach(7);  //horizontal panning Servo attached to pin 7


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
horizontalPan();

}

  //Serial.println(posArray[18]);
//  for (pos= 0; pos<=180; pos++){
//    servo.write(pos);
//    delay(30); 
//   }
//   for (pos = 180; pos >= 0; pos --){
//    servo.write(pos);
//    delay(30);
//   }
//  
  


