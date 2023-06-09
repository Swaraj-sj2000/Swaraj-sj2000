#include<SPI.h>
#include<RF24.h>
#include<nrf24L01.h>
RF24 radio(6,2);
const byte address[6]="00001";                               //same address as transmitter chip
const int enA=9;const int in1=8; const int in2=7;            //inputs for motor 1...ena=speed and in1 and in2 are direction inputs of motor driver
const int enB=3;const int in3=1;  const int in4=10;          //inputs for motor 2

//take care that enable pins work on pulse width modulation so attach them to the pmw digi pins  rest can be any digital pins

void setup()
{
  
  pinMode(enA,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(enB,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);

 digitalWrite(enA,LOW);                  //at start the motors are directioned to move forward  but speed is given 0
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(enB,LOW);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
 
 radio.begin();
 radio.openReadingPipe(0,address);
 radio.startListening();}

 void loop(){
  if(radio.available())
  {int go[6];                                       //array to accept data...6 data is to be recieved
  radio.read(&go,sizeof(go));                        //recieve the data in the above array
 
  //feed themotor drivers according to the data recieved
  
  analogWrite(enA,go[0]);                //motor1 speed                         
  digitalWrite(in1,go[1]);               
  digitalWrite(in2,go[2]
