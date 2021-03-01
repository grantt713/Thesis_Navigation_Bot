#include <Servo.h>

// For Servos 
Servo LEFTSERVO;  // Gives the servos different names
Servo RIGHTSERVO;

int LSet=90, RSet=90;  // designates servo center value or balance point using a variable
int LForward=-30, RForward=+30;

int FRS=2, FLS=3, RS=4, LS=5, BRS=7, BLS=8;
int VFRS, VFLS, VRS, VLS, VBRS, VBLS;
int LED1=13, LED2=A0;
int LTrig=A1, LEcho=A2, RTrig=A3, REcho=A4;

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
}

void loop() {
  // put your main code here, to run repeatedly:

VFRS=digitalRead(FRS);
VFLS=digitalRead(FLS);
VRS=digitalRead(RS);
VLS=digitalRead(LS);
VBRS=digitalRead(BRS);
VBLS=digitalRead(BLS);

while((VFRS==HIGH)||(VFLS==HIGH)||(VRS==HIGH)||(VLS==HIGH)||(VBRS==HIGH)||(VBLS==HIGH)){
  digitalWrite(LED1,HIGH);

  VFRS=digitalRead(FRS);
  VFLS=digitalRead(FLS);
  VRS=digitalRead(RS);
  VLS=digitalRead(LS);
  VBRS=digitalRead(BRS);
  VBLS=digitalRead(BLS);
}
digitalWrite(LED1,LOW);

LEFTSERVO.write(LSet);
RIGHTSERVO.write(RSet);
}
