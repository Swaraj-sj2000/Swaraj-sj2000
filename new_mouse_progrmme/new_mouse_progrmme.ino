#include <Wire.h>
#include <BleMouse.h>

BleMouse bleMouse;

const uint8_t MPU6050Address = 0x68;
const uint16_t I2C_TIMEOUT = 1000;

int16_t gyroX, gyroY;
int sensitivity = 500;
int delayInterval = 10;

uint8_t i2cRead(uint8_t registerAddress, uint8_t* data, uint8_t nbytes) {
  Wire.beginTransmission(MPU6050Address);
  Wire.write(registerAddress);
  if (Wire.endTransmission(false))
    return 1;
  Wire.requestFrom(MPU6050Address, nbytes, (uint8_t)true);
  for (uint8_t i = 0; i < nbytes; i++) {
    if (Wire.available())
      data[i] = Wire.read();
    else {
      uint32_t timeOutTimer = micros();
      while (((micros() - timeOutTimer) < I2C_TIMEOUT) && !Wire.available());
      if (Wire.available())
        data[i] = Wire.read();
      else
        return 2;
    }
  }
  return 0;
}

void setup() {
  Wire.begin();

  Wire.beginTransmission(MPU6050Address);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0x00); // Wake up MPU6050
  Wire.endTransmission(true);

  Serial.begin(115200);
  bleMouse.begin();
}

void loop() {
  uint8_t i2cData[14];
  if (i2cRead(0x3B, i2cData, 14) == 0) {
    gyroX = ((i2cData[8] << 8) | i2cData[9]);
    gyroY = ((i2cData[10] << 8) | i2cData[13]);

    gyroX = -gyroX / sensitivity/1.1 ;
    gyroY = -gyroY / sensitivity;

    if (bleMouse.isConnected()) {
      if(gyroX<5 && gyroX>-5){gyroX=0;}
      if(gyroY<5 && gyroY>-5){gyroY=0;}
      Serial.print("gyroX=");
      Serial.print(gyroX);
      Serial.print("   ");
      Serial.print("gyroY");
      Serial.print(gyroY);
      
      Serial.print("\r\n");
      bleMouse.move(gyroY, -gyroX);
    }
  }

  delay(delayInterval);
}
