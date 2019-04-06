
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
#include <math.h>

int pos = 0;
int vertPos = 0;
int posArray[180];
int i =0;

int originPos=0;

Servo verticalServo;
Servo horizontalServo;

LIDARLite lidarLite;

float dist;
int cal_cnt = 0;

float vap =0; // verticalangle position
float hap=0; // horizontal angle position


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


void horizontalPan(){



  horizontalServo.write(pos);
  
  delay(20);
  hap ++;
  pos = pos +10; 
   if (pos >= 180){
    pos = 0;
    horizontalServo.write(pos);
  }
  verticalPan();
  originPos++;
  
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
  


