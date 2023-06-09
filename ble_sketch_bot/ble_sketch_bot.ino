#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

String receivedChar;
String text;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("Robotics_club_Bot");
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
   receivedChar =SerialBT.read();

 
  if (SerialBT.available()) {
     
    Serial.print("Received:");//print on serial monitor
    Serial.println((String)receivedChar);
  }
}
