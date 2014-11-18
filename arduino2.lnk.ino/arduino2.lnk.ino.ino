#include <AFMotor.h>
AF_DCMotor motor1(2);
AF_DCMotor motor2(3);
int i, op, vel;
char c;

void setup()
{
  Serial.begin(9600);
  Serial.println("Arduino2: Serial Monitor Connected");
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);
}

void loop()
{
  
  if (Serial.available() > 0){
    i = Serial.parseInt();
    op = i/1000;
    //Serial.println(op);
    switch (op) {
     case 1:
         motor1.run(FORWARD);
         //Serial.println("FORWARD 1");
         break;
     case 2:
         motor2.run(FORWARD);
         //Serial.println("FORWARD 2"); 
         break;
     case 3:
         motor1.run(BACKWARD);
         //Serial.println("BACKWARD 1");
         break;
     case 4:
         motor2.run(BACKWARD);
         //Serial.println("BACKWARD 2");
         break;
     case 5:
         motor1.run(RELEASE);
         //Serial.println("RELEASE 1");
         break;
     case 6:
         motor2.run(RELEASE);
         //Serial.println("RELEASE 2");
         break;
     case 7:
         vel = i%1000;       
         motor1.setSpeed(vel);
         //Serial.print("Speed 1: ");
         //Serial.println(vel);
         break;
     case 8:
         vel = i%1000;
         motor2.setSpeed(vel);
         //Serial.print("Speed 2: ");
         //Serial.println(vel);         
         break;
     case 9:
         Serial.println("OBSTACULO DETECTADO!!!!!!");
         break;
     case 10:{
         int p1 = Serial.parseInt();
         int p2 = Serial.parseInt();
         int p3 = Serial.parseInt();
         Serial.print("Distancia Frontal: ");
         Serial.println(p1);
         Serial.print("Distancia Derecha: ");
         Serial.println(p2);
         Serial.print("Distancia Izquierda: ");
         Serial.println(p3);
         break;
     }
     case 11:
         /*int p1 = Serial.parseInt();
         int p2 = Serial.parseInt();
         int p3 = Serial.parseInt();*/
         int p4 = Serial.parseInt();
        /* Serial.print("Eje X: ");
         Serial.println(p1);
         Serial.print("Eje Y: ");
         Serial.println(p2);
         Serial.print("Eje Z: ");
         Serial.println(p3);*/
         Serial.print("Grados: ");         
         Serial.println(p4);
         break;
         
    }
  }
}
