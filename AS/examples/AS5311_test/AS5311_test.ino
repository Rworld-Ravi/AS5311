#include <ResponsiveAnalogRead.h>
#include "AS.h"

ResponsiveAnalogRead analog(0, true);

AS5311 as5311(12, 13, 11); // data, clock, chip select

int counter, zeroVal, finalPoint, encoderVal, lastEncoderVal;
int lastPole = -1;

float valueMap;

void setup()

{
  Serial.begin(115200);
  analog.setSnapMultiplier(0.01);
  analog.setAnalogResolution(4096);
  analog.setActivityThreshold(1);
}

void loop() {

  
  //Step 1: Get the value
  encoderVal = as5311.value();
  
  //Step 2: Filter the encoder value
  encoderVal = filter();
  
  //Step 3: Change direction
  encoderVal = map(encoderVal, 0, 4095, 4095, 0);

  //Step 4: Get the zero error and use dynamic zeroing
  encoderVal = dynamicZeroError();  

  //Step 5: Increment or decrement counter variable
  checkCounter();  

  //Step 6: Assign a proper value
  valueMap = (counter * 2000) + encoderVal*0.48828125;

  //Show some data
  showData();
}
