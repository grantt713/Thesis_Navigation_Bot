#include <Servo.h>

// For Servos 
Servo LEFTSERVO;  // Gives the servos different names
Servo RIGHTSERVO;

int LSet=90, RSet=90;  // designates servo center value or balance point using a variable
int LForward=30, RForward=-20;

int FRS=2, FLS=3, RS=4, LS=5, BRS=7, BLS=8;
int VFRS, VFLS, VRS, VLS, VBRS, VBLS;
int LED1=13, LED2=A0;
int LTrig=A1, LEcho=A2, RTrig=A3, REcho=A4;

long LeftDuration, RightDuration;
int LeftDistance, RightDistance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(11,OUTPUT);   // leftservo - establishes pin 2 as output
  pinMode(10,OUTPUT);    // rightservo - establishes pin 3 as output
  LEFTSERVO.attach(11);  // tell the Arduino which servo belongs to each pin
  RIGHTSERVO.attach(10);

  pinMode(FRS,INPUT);  // tells Arduino that we will be listening to input of the Switch pin
  pinMode(FLS,INPUT);
  pinMode(RS,INPUT);
  pinMode(LS,INPUT);
  pinMode(BRS,INPUT);
  pinMode(BLS,INPUT);

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

  pinMode(LTrig,OUTPUT);
  pinMode(RTrig,OUTPUT);
  pinMode(LEcho,INPUT);
  pinMode(REcho,INPUT);
  
}


// &&&&&&&&&&&&&&&&&&&&&&& Functions &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
int SwitchRead(){
  VFRS=digitalRead(FRS);
  VFLS=digitalRead(FLS);
  VRS=digitalRead(RS);
  VLS=digitalRead(LS);
  VBRS=digitalRead(BRS);
  VBLS=digitalRead(BLS);
}

// ***********

int Forward(){
  SwitchRead();
  while((VFRS!=HIGH)||(VFLS!=HIGH)){
    LEFTSERVO.write(LSet+LForward);
    RIGHTSERVO.write(RSet+RForward);
    SwitchRead();

    if(VLS==HIGH){
      LEFTSERVO.write(LSet+LForward);
      RIGHTSERVO.write(RSet);
    }
     if(VRS==HIGH){
      LEFTSERVO.write(LSet);
      RIGHTSERVO.write(RSet+RForward);
    }
  }
  LEFTSERVO.write(LSet);
  RIGHTSERVO.write(RSet);
}

// **************

int Still(){
  LEFTSERVO.write(LSet);
  RIGHTSERVO.write(RSet);
  delay(2000);
}

// **************

int TurnRight(){
  SwitchRead();
  while((VBRS!=HIGH)||(VBLS!=HIGH)){
    LEFTSERVO.write(LSet);
    RIGHTSERVO.write(RSet-RForward);
    delay(500);
    LEFTSERVO.write(LSet-LForward);
    RIGHTSERVO.write(RSet-RForward);
    delay(500);
    SwitchRead();
  }
}

// ***************

int TurnLeft(){
  SwitchRead();
  while((VBRS!=HIGH)||(VBLS!=HIGH)){
    LEFTSERVO.write(LSet-LForward);
    RIGHTSERVO.write(RSet);
    delay(500);
    LEFTSERVO.write(LSet-LForward);
    RIGHTSERVO.write(RSet-RForward);
    delay(500);
    SwitchRead();
  }
}

// ****************

int DetectLeftSensor(){
  digitalWrite(LTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(LTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(LTrig, LOW);
  LeftDuration = pulseIn(LEcho, HIGH);
  LeftDistance = LeftDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Left Distance: ");
  Serial.print(LeftDistance);
  Serial.println(" cm");
}

// *******************

int DetectRightSensor(){
  digitalWrite(RTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(RTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(RTrig, LOW);
  RightDuration = pulseIn(REcho, HIGH);
  RightDistance = RightDuration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Right Distance: ");
  Serial.print(RightDistance);
  Serial.println(" cm");
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void loop() {
  // put your main code here, to run repeatedly:


Forward();

DetectLeftSensor();
DetectRightSensor();

if(RightDistance>LeftDistance){
  TurnRight();
}
if(LeftDistance>RightDistance){
  TurnLeft();
}

}
