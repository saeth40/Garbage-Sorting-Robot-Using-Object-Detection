//Servo setup
//remote destop:run, mstsc, ip 
//user: pi, pass : service
//rasp gpio : 12(al),26(others),15(paper),7(plastic)
#include <Servo.h>
Servo myservo;
// defines pins numbers, pwm: 2-13
const int LedPlas = 31; //d1, 7 to 31
const int LedAl = 35; //d2, 12 to 35
const int LedPaper = 39; //d3, 15 to 39
const int LedOthers = 43; //d4, 26 to 43
const int  servo = 2; //d5
const int Lim1 = 47; //d6, cw
const int Lim2 = 51; //d7, ccw
const int Ir1 = 4; //d8
const int Ir2 = 6; //d9
const int Hb1 = 8; //d10
const int Hb2 = 10; //d11
const int HbPwm = 12;//pwm1 
const int Relay = 26; //d12
//for while true loop
int assume=0;
int assume2=0;
int tohome = 1200;
void setup() {
  // put your setup code here, to run once:
  pinMode(LedPlas, INPUT);
  pinMode(LedAl, INPUT);
  pinMode(LedPaper, INPUT);
  pinMode(LedOthers, INPUT);
  myservo.attach(servo);
  pinMode(Lim1, INPUT);
  pinMode(Lim2, INPUT);
  pinMode(Ir1, INPUT);
  pinMode(Ir2, INPUT);
  pinMode(Hb1, OUTPUT);
  pinMode(Hb2, OUTPUT);
  pinMode(HbPwm, OUTPUT);
  pinMode(Relay, OUTPUT);

}

void loop() {
  //set initial position
  digitalWrite(Relay,HIGH);//led off
  while (assume<=0){//while true
    if (digitalRead(Lim1)==LOW){
      //cw,lim1
      digitalWrite(Hb1,LOW);
      digitalWrite(Hb2,HIGH);
      analogWrite(HbPwm,255);
    }
    if (digitalRead(Lim1)==HIGH){
      //ccw,lim2
      analogWrite(HbPwm,0);
      //delay(500);
      digitalWrite(Hb1,HIGH);
      digitalWrite(Hb2,LOW);
      analogWrite(HbPwm,255);
      delay(tohome);//to home 90 deg
      analogWrite(HbPwm,0);
      assume=assume+1;//break while true
      break;
    }
  }
  myservo.write(80);//servo normal level
  
  //if ir 1 and ir 2 notfound an object -> led off
  while ((digitalRead(Ir2)==HIGH ) and (digitalRead(Ir1)==HIGH)){
    digitalWrite(Relay,HIGH);//led off
  }
  //if ir1 or 2 found an object (exit from loop while)
  digitalWrite(Relay,LOW);//led on
  while (assume2<=0){
    if (digitalRead(LedPlas)==HIGH){
      digitalWrite(Relay,HIGH);//led off
      myservo.write(125);
      delay(500);
      myservo.write(80);
      break;
    }
    if (digitalRead(LedOthers)==HIGH){
      digitalWrite(Relay,HIGH);//led off
      myservo.write(0);
      delay(500);
      myservo.write(80);
      break;
    }
    if (digitalRead(LedAl)==HIGH){
      digitalWrite(Relay,HIGH);//led off
      while (digitalRead(Lim1)==LOW){
        //cw,lim1
        digitalWrite(Hb1,LOW);
        digitalWrite(Hb2,HIGH);
        analogWrite(HbPwm,255);
      }
      analogWrite(HbPwm,0);
      myservo.write(125);
      delay(500);
      digitalWrite(Hb1,HIGH);
      digitalWrite(Hb2,LOW);
      analogWrite(HbPwm,255);
      delay(tohome); //to home
      analogWrite(HbPwm,0);
      myservo.write(80);
      break;
    }
    if (digitalRead(LedPaper)==HIGH){
      digitalWrite(Relay,HIGH);//led off
      while (digitalRead(Lim2)==LOW){
        //ccw,lim2
        digitalWrite(Hb1,HIGH);
        digitalWrite(Hb2,LOW);
        analogWrite(HbPwm,255);
       }
       analogWrite(HbPwm,0);
       myservo.write(125);
       delay(500);
       digitalWrite(Hb1,LOW);
       digitalWrite(Hb2,HIGH);
       analogWrite(HbPwm,255);
       delay(tohome); //to home
       analogWrite(HbPwm,0);
       myservo.write(80);
       break;
    }
  }
 
  }
  

      
