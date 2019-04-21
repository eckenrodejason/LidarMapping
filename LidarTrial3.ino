

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


//
//radians = (degrees * 71) / 4068
//
//degrees = (radians * 4068) / 71






#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <math.h>
#include <SPI.h>



// ********************** Variable Declaration/Initilization *******************************************
int pos = 0;// variable for servo position
int hpos=0;
int vertPos = 0; //
int i =0;

//float rho, theta, phi;


int horizontalOriginPos=0;

Servo verticalServo;
Servo horizontalServo;

LIDARLite lidarLite;

float dist;
int cal_cnt = 0;




float getXdata(float rho, float phi, float theta){

  phi = (phi * 71)/4068;

  theta = (theta*71)/4068;

  float x = rho*cos(phi)*sin(theta);

  return x;
 
}

float getYdata(float rho, float phi, float theta){
  phi = (phi * 71)/4068;

  theta = (theta*71)/4068;

  float y = rho*sin(phi)*sin(theta);

  return y; 
  
}


float getZdata(float rho, float phi){
  phi = (phi * 71)/4068;

   float z= rho*cos(phi);
    return  z;

}


// ************************End Variable Declaration/Initilization****************************************


//*************************Function Declarations*********************************************************


//Vertical servo control
void verticalPan(){
   //lidarScan();

int panCount =0;

while ( panCount < 25){

for (vertPos = 0; vertPos <= 90; vertPos ++){
    //delay(50);
    //writeVerticalToSd();
    //Serial.print("Vertical Angle: ");
    Serial.print(getXdata(lidarScan(),vertPos,hpos));
    //Serial.print(vertPos);
    Serial.print(",");
   // Serial.print(" Horizontal Angle: ");
    Serial.print(getYdata(lidarScan(),vertPos,hpos));
    Serial.print(",");
    Serial.print(getZdata(lidarScan(), vertPos));
    Serial.println("");
    
    verticalServo.write(vertPos);
   
    panCount++;
    
    delay(50);
    
  }
//  vertPos= 15;
horizontalServo.write(hpos);

hpos++;

for (vertPos; vertPos>1; vertPos--){
    //Serial.print("Vertical Angle: ");
    Serial.print(getXdata(lidarScan(),vertPos,hpos));
    //Serial.print(vertPos);
    Serial.print(",");
    //Serial.print(" Horizontal Angle: ");
    Serial.print(getYdata(lidarScan(),vertPos,hpos));
    Serial.print(",");
    Serial.print(lidarScan());
    Serial.println("");
    verticalServo.write(vertPos);

    delay(50);
  
}

  
}
   
  

}



//Horizontal Servo Control 


void horizontalPan(){


  horizontalServo.write(hpos);
  
  delay(20);
    
   if (hpos <= 90){
    horizontalServo.write(hpos);
    hpos= hpos+5;
    verticalPan();
  }
  
  
}

// Lidar Scanning Function
float lidarScan(){

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
  //Serial.print(dist);
  //Serial.println(" cm");
  delay(10);
    return dist;
}

//End Lidar Section 


void setup() {
  
  Serial.begin(9600);
  delay(100);
  verticalServo.attach(6);  // vertical panning servo attached to pin 6
  horizontalServo.attach(7);  //horizontal panning Servo attached to pin 7

  hpos = 0;
  vertPos=0;

  verticalServo.write(vertPos);
  horizontalServo.write(hpos);


  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidarLite.configure(0); // Change this number to try out alternate configurations

  


}

void loop() {
horizontalPan();

}



