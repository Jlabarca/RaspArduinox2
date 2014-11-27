#define trigRPin 13 //Ultrasonico Derecho Out
#define echoRPin 12 //Ultrasonico Derecho In
#define trigLPin 11 //Ultrasonico Izquierdo Out
#define echoLPin 10 //Ultrasonico Izquierdo In
#define trigFPin 9 //Ultrasonico Frontal Out
#define echoFPin 8 //Ultrasonico Frontal Int
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
#define TAM 5

struct data{
  double distL;
  double distR;
  double distF;
  float Degrees;
};

//*Variables*//
double distF[TAM],distR[TAM],distL[TAM]; 
int j=0;
int i, op, vel;
data lecturas;



void setup()
{
  Serial.begin(9600);
  //Serial.println("Arduino1: Serial Monitor Connected");
  pinMode(trigRPin, OUTPUT);
  pinMode(echoRPin, INPUT);
  pinMode(trigLPin, OUTPUT);
  pinMode(echoLPin, INPUT);
  pinMode(trigFPin, OUTPUT);
  pinMode(echoFPin, INPUT);
  /*distanceL=getLeftDistance();
  distanceR=getRightDistance();
  distanceF=getFrontDistance();*/
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
}

void loop()
{
   //*Magnetometro/////////////////
   
  sensors_event_t event; 
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);    
  float declinationAngle = 0.5;
  heading += declinationAngle;
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  lecturas.Degrees = heading * 180/M_PI; 
  
  //Calculos Sensores distancia
  
  //Serial.print(getLeftDistance());
  //Serial.print(", ");
  //Serial.print(getRightDistance());
  //Serial.print(", ");
  //Serial.println(getFrontDistance());
  //delay(1000);
 
  distF[j]=getFrontDistance();
  distR[j]=getRightDistance();
  distL[j++]=getLeftDistance();
  if(j==TAM)
    j = 0;
  
  // Reactivos
  
  if(isBlocked()){
    Serial.println(5000);
    Serial.println(6000);
    Serial.println(9000);
    
  }
  
  //Casessss
  if (Serial.available() > 0){
    i = Serial.parseInt();
    
    op = i/1000;
    switch (op) {
       case 1:
           Serial.println(1000);
           Serial.println(2000);
           break;
       case 2:
           Serial.println(3000);
           Serial.println(4000);
           break;
       case 3:
           Serial.println(5000);
           Serial.println(6000);
           break;
       case 4:
           vel = i%1000;
           Serial.println(7000 + vel);
           Serial.println(8000 + vel);
           break;
       case 5:
           Serial.println(1000);
           Serial.println(4000);
           break;
       case 6:
           Serial.println(2000);
           Serial.println(3000);
           break;
       case 7:
           {double promF=0,promL=0,promR=0;
           for(int x=0;x<TAM;x++){
             promF=promF+distF[x];
             promR=promR+distR[x];
             promL=promL+distL[x];
           }
           char t[100]; //* s1,s2,s3;
           int prom1=promF/5;
           int prom2=promR/5;
           int prom3=promL/5;
           sprintf(t, "10000,%d,%d,%d", prom1, prom2, prom3);
           Serial.println(t);
           break;
           }
       case 8:
           char f[100]; //* s1,s2,s3;
          /* Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
           Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
           Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
           Serial.print("Heading (degrees): "); Serial.println(headingDegrees);*/
           /*int x = event.magnetic.x;
           int y = event.magnetic.y;
           int z = event.magnetic.z;*/
           int h = lecturas.Degrees;
           sprintf(f, "11000,%d",h);
           Serial.println(f);
           break;
    }
  }
}

double getLeftDistance(){
  long duration, distance;
  digitalWrite(trigLPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigLPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigLPin, LOW);
  duration = pulseIn(echoLPin, HIGH);
  lecturas.distL = (duration/2) / 29.1;
  return lecturas.distL;
}
double getRightDistance(){
  long duration, distance;
  digitalWrite(trigRPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigRPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigRPin, LOW);
  duration = pulseIn(echoRPin, HIGH);
  lecturas.distR = (duration/2) / 29.1;
  return lecturas.distL;
}
double getFrontDistance(){
  long duration, distance;
  digitalWrite(trigFPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigFPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigFPin, LOW);
  duration = pulseIn(echoFPin, HIGH);
  lecturas.distF = (duration/2) / 29.1;
  return lecturas.distF;
}

boolean isBlocked(){
  if((int)lecturas.distF<15 && (int)lecturas.distF>5){
    return true;
  }else
    return false;
}
