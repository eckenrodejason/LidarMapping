

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


// ********************** Variable Declaration/Initilization *******************************************
int pos = 0;// variable for servo position
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



float vertDist_AngleAry[360];





// ************************End Variable Declaration/Initilization****************************************


//*************************Function Declarations*********************************************************


//Vertical servo control
void verticalPan(){
   lidarScan();
  for (vertPos =0; vertPos <= 180; vertPos ++){
    //delay(50);
    verticalServo.write(vertPos);
    vap ++;
    
    delay(50);
    
  }
  vertPos= 0;
}



//Horizontal Servo Control 








void horizontalPan(){


  horizontalServo.write(pos);
  
  delay(20);
  hap ++;
  
  pos = pos +10; 
   if (pos >= 180){
    pos = 0;// reset back to original position
    horizontalOriginPos = 0;
    horizontalServo.write(pos);
  }
  verticalPan();
  horizontalOriginPos++;
  Serial.println("Current distance from origin: "+ horizontalOriginPos);
  
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
  //Array that stores distacnes measured by lidar
  distArray[i]=dist;
  
  i++;

  //display Distance
  Serial.print(dist);
  Serial.println(" cm");

  delay(10);
    
}

//End Lidar Section 

//Converting distances from points to x,y, and z coordinates 
void convertToCartesian(float vangle, float hangle, float dist){

    float temp; 
    float radius = dist;

    float xpos = radius*cos(hangle);
    float ypos = radius* sin(vangle);
    float zpos = temp;

  
}


void setup() {
  verticalServo.attach(6);  // vertical panning servo attached to pin 6
  horizontalServo.attach(7);  //horizontal panning Servo attached to pin 7


  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidarLite.configure(0); // Change this number to try out alternate configurations

  
  Serial.begin(9600);

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
  






