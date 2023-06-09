#include<SPI.h>
#include<RF24.h>
#include<nrf24L01.h>

RF24 radio(9,8);               //radio
const byte address[6]="00001";
const int xpin=A0,ypin=A1;      //joystick input
int in1,in2,in3,in4,xval,yval;  // for motor driver
int S1,S2;                     //speed of left and right motors... can be from vslue 0 to 255

void setup()
{pinMode(xpin,INPUT);  
pinMode(ypin,INPUT);
radio.begin();
radio.openWritingPipe(address);
radio.stopListening();
  }
 void loop()
 {int go[6];                //6 data to be sent in1 in2 in3 in4 S1 and S2
  xval=analogRead(xpin);
 yval=analogRead(ypin);
   {
    if(xval<480)                           //mid p of joystick is 512 so forward is  set with a range when the value is less than 480
      {in1=1;in2=0;in3=1;in4=0;            //in1=high in2=low=motor1 forward   in3=high and in4=low=motor2 forward  reverse them for each pair for back
      S1=map(480-xval,0,480,0,200);         //setting the min speed=0 and max as 200...at 255 it become uncontrollable
      S2=map(480-xval,0,480,0,200);}        //same for motor2
      
   else if(xval>540)                        //for back
      {in1=0;in2=1;in3=0;in4=1;
      S1=map(xval,540,1023,0,200);
      S2=map(xval,540,1023,0,200);}
      
   else if(xval>=480 && xval<=540)         //a range of values for being at rest
      {S1=0;S2=0;}
      }

    //directions
   {if(yval<500)                             //left...cause 512 is mid
      {yval=map(500-yval,0,500,0,150);       //left motion is caused when motor right is faster than motor left
      S2=S2+yval;
      S1=S1-yval;
      if(S1<0){S1=0;}                        //but take care that after direction addition too the speeds must not exceed 200 and preceed 0
      if(S2 >200){S2=200;}}
   else if(yval>530)                         //right
      {yval=map(yval,530,1023,0,150);       
      S1=S1+yval;
      S2=S2-yval;
      if(S1>200){S1=200;}
      if(S2<0){S2=0;}}
   }
   if(S1<10){S1=0;}                       //if very less speed is given then motors will make noise but wont move so to avoid that noise just switch it off at very low speeds
   if(S2<10){S2=0;}

   go[0]=S1;                             //pack the data in an array
   go[1]=in1;
   go[2]=in2;
   go[3]=S2;
   go[4]=in3;
   go[5]=in4;
   
     
   radio.write(&go,sizeof(go));        //send it over radio
   
      
  }
  
  
  
  
  
  
