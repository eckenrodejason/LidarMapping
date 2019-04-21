import peasy.*;
PeasyCam cam;

float x_axis, y_axis, z_axis;

BufferedReader reader;

String line;



float[] x_vals = new float[20000];
float[] y_vals = new float[20000];
float[] z_vals = new float[20000];

String[] newArray = new String[7000]; 

float[] tempArray= new float[10000];

void setup ()
{
  size(2048, 1024, P3D);
  cam = new PeasyCam(this, 512);
  cam.setFreeRotationMode();
  x_axis = width/2;
  y_axis = height;
  z_axis = height/2;
   
 read();
  
}


void read(){
  
  
  String[] dataLog = loadStrings("DataLog8");
  
    if (dataLog != null){
    dataLog = trim(dataLog);
    
    
    for (int i =0; i < dataLog.length; i++){
      String temp;
      temp = trim(dataLog[i]); 
      tempArray= float(split(temp,","));
      
      x_vals[i]= tempArray[0];
      y_vals[i] =tempArray[1];
      //z_vals[i]= tempArray[2];
      
      println(x_vals[i] + " " + y_vals[i] + "end" );
      
    }

}

}


void draw()
{
  background(128);
  axis();

  for (int i = 0; i < x_vals.length; i++)
  {   
    pushMatrix();
    translate(x_vals[i], y_vals[i], z_vals[i]);
    stroke(mapColor(x_vals[i], y_vals[i], z_vals[i]));
    sphere(2);   
    popMatrix();
  }
}

color mapColor(float _x, float _y, float _z)
{
  int r = int(map(_x, 0, x_axis, 0, 255));
  int g = int(map(_y, 0, y_axis, 0, 255));
  int b = int(map(_z, 0, z_axis, 0, 255));
  return color(r, g, b);
}

void axis()
{
  strokeWeight(2);
  stroke(255, 0, 0);
  line(0, 0, 0, x_axis, 0, 0);
  stroke(0, 255, 0);
  line(0, 0, 0, 0, y_axis, 0); 
  stroke(0, 0, 255);
  line(0, 0, 0, 0, 0, z_axis);
}
