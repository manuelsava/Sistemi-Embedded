#include <Servo.h> 
#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <NewPing.h>
Servo myservo;

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ); 
AF_DCMotor motor4(4, MOTOR34_1KHZ);

NewPing sonar(A4, A5, 100); //Triger, ECHO, Max distanza in cm

bool isFwd = false;
int SPEED = 180;
int BTSpeed = 180;

SoftwareSerial bt(9, 10);

int mode; //0: BT, 1: Schiva Ostacoli

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bt.begin(9600);

  motor1.setSpeed(SPEED);
  motor2.setSpeed(SPEED);
  motor3.setSpeed(SPEED);
  motor4.setSpeed(SPEED);
  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
  myservo.attach(10);  
  myservo.write(90); 

  mode = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(mode == 0){
    SPEED = BTSpeed;
    int dFront = readPing();
    if(dFront < 30 && isFwd == true){
      stopMotors();
    }
    else if(bt.available() > 0){
    char data = bt.read();
    switch(data){
      case 'N':
        goForward();
        break;
       case 'S':
        goBackward();
         break;
        case 'W':
          turnLeft();
          break;
        case 'E':
          turnRight();
          break;
        case 'X':
          stopMotors();
          break;
        case 'P':
          if(SPEED < 245)
            BTSpeed += 10;
           else {
            BTSpeed = 255;
           }
          break;
        case 'D':
          if(SPEED > 110){
            BTSpeed -= 10; 
          }
          else {
            BTSpeed = 100;
          }
          break;
        case 'M':
          mode = 1;
          break;
       }
     }
  }
  else if(mode == 1){
    if(SPEED != 180){
      SPEED = 180;
    }
    if(bt.available()){
      char data = bt.read();
      if(data == 'M'){
        mode = 0;
        stopMotors();
      }
    }
    else{
      int dFront = readPing();
      if(dFront > 30){
        goForward();
      }
      else{
        stopMotors();
        delay(500);
        int dl = lookLeft();
        Serial.println(dl);
        delay(500);
        int dr = lookRight();
        Serial.println(dr);
        delay(500);
        if(dr >= dl){
          turnRight();
          delay(650);
          stopMotors();
          delay(100);
        }
        else {
          turnLeft();
          delay(650);
          stopMotors();
          delay(100);
        }
      }
    }
  }
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm == 0)
    cm = 100;
  return cm;
}

void turnLeft(){
  isFwd = false;
  motor1.setSpeed(180);
  motor2.setSpeed(180);
  motor3.setSpeed(180);
  motor4.setSpeed(180);
  
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
}

void turnRight(){
  isFwd = false;
  motor1.setSpeed(180);
  motor2.setSpeed(180);
  motor3.setSpeed(180);
  motor4.setSpeed(180);
  
  motor1.run(FORWARD);
  motor4.run(BACKWARD);
}

void goForward(){
  isFwd = true;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  for(int i = 100; i < SPEED; i+=2){
    motor1.setSpeed(i);
    motor2.setSpeed(i);
    motor3.setSpeed(i);
    motor4.setSpeed(i);  
    delay(5);
  }
}

void goBackward(){
  isFwd = false;
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for(int i = 100; i < SPEED; i+=2){
    motor1.setSpeed(i);
    motor2.setSpeed(i);
    motor3.setSpeed(i);
    motor4.setSpeed(i);  
    delay(5);
  }
}

int lookLeft(){
  for(int i = 90; i > 0; i-= 4){
    myservo.write(i);
    delay(10);
  }
  delay(500);
  int distance = readPing();
  delay(100);
  for(int i = 0; i < 90; i+=4){
    myservo.write(i);
    delay(10);
  }
  myservo.write(90);
  return distance;
}

int lookRight(){
  for(int i = 90; i < 180; i+=4){
    myservo.write(i);
    delay(10);
  }
  delay(500);
  int distance = readPing();
  delay(100);
  for(int i = 180; i > 90; i-=4){
    myservo.write(i);
    delay(10);
  }
  myservo.write(90);
  return distance;
}


void stopMotors(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  isFwd = false;
}
