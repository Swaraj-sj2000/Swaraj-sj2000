//declarations
#include <LiquidCrystal.h>
#include <Servo.h>
//Servo s1;
Servo s2;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int trigP=8,echoP=7;
long dur; int dis;

float tm;
const int piezo=13;
const int ledg=A0;
const int ledr=A1;

void alert(int a,int p)
{for(int i=0;i<2;i++)
{digitalWrite(a,HIGH);tone(p,500);delay(200);
digitalWrite(a,LOW);noTone(p);delay(200);
digitalWrite(a,HIGH);tone(p,500);delay(200);
digitalWrite(a,LOW);noTone(p);delay(200);} 
}

//setup
void setup() {
  lcd.begin(16,2);
  pinMode(trigP,OUTPUT);
  pinMode(echoP,INPUT);
  
  //s1.attach(9);
  s2.attach(10);
  
  Serial.begin(9600);
 
  //s1.write(0);
  s2.write(170);
  
  pinMode(ledg,OUTPUT);
  pinMode(ledr,OUTPUT);
}

//main loop

void loop() {
 
  digitalWrite(trigP, LOW);
  delayMicroseconds(2);
  digitalWrite(trigP, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigP, LOW);
 
  dur = pulseIn(echoP, HIGH);
  
  dis = dur * 0.034 / 2; 
  //Serial.println(dis);
  
  lcd.clear();
  digitalWrite(ledg,LOW);
  digitalWrite(ledr,LOW);
  
  if(dis<=30)
   { Serial.println("enter temperature");
      while (Serial.available()==0){}
  
     tm = Serial.parseFloat();
     Serial.println(tm);
     lcd.setCursor(0,0);
     lcd.print("Temperature = "); 
     lcd.setCursor(0,1);
     lcd.print(tm); 
      lcd.print(" *F");
  
  delay(2000);
  lcd.clear();
  
  if(tm<100.4)
  {//s1.write(90);
   s2.write(80);//open
   
  lcd.setCursor(0,0);
  
  lcd.write("Safe");
  
  digitalWrite(ledg,HIGH);
  tone(piezo,200);delay(200);noTone(piezo);
  delay(5000);
  
 
  }
  
  else if(tm>=100.4)
  {//s1.write(0);
   s2.write(170);
  lcd.print("Not Safe");
  alert(ledr,piezo);
  
  }
  }
  
  else{//s1.write(0);
 s2.write(170);
 }
  
  delay(300);}
