#include "AS5311.h"

AS5311 as5311(12, 13, 11); // data, clock, chip select

int counter, zeroVal, finalPoint, encoderVal, lastEncoderVal;
int lastPole = -1;

float valueMap;

void setup()

{
  Serial.begin(115200);
}

void loop() {
  //Step 1: Get the value
  encoderVal = as5311.value();
  
  //Step 2: Change direction
  encoderVal = map(encoderVal, 0, 4095, 4095, 0);

  //Step 3: Get the zero error and use dynamic zeroing
  encoderVal = dynamicZeroError();  

  //Step 4: Increment or decrement counter variable
  checkCounter();  

  //Step 5: Assign a proper value
  valueMap = (counter * 2000) + encoderVal*0.48828125;

  //Show some data
  showData();
}
