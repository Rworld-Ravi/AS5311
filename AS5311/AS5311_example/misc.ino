void checkCounter() {

  uint32_t triPole = as5311.triPole(encoderVal);  

  if (lastPole == 2 && triPole == 0) {
    counter++;
  }

  if (lastPole == 0 && triPole == 2) {
    counter--;
  }

  lastEncoderVal = encoderVal;
  lastPole = triPole;
}

int dynamicZeroError() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    int readVal = Serial.read();

    if (readVal == 48)
    {
      zeroVal = encoderVal;
      finalPoint = 4095 - encoderVal;
    }
  }

  return as5311.dynamic_zero(encoderVal, zeroVal, finalPoint);
}

void showData() {

  Serial.print(encoderVal);
  Serial.print(" ");

  Serial.print(valueMap);
  Serial.print(" ");
  
  if (as5311.error()) {

    if (as5311.err_value.OCF) {
      Serial.print(" OCF");
    } else {
      Serial.print("    ");
    }
    if (as5311.err_value.COF) {
      Serial.print(" COF");
    } else {
      Serial.print("    ");
    }
    if (as5311.err_value.DECn) {
      Serial.print(" DEC");
    } else {
      Serial.print("    ");
    }
    if (as5311.err_value.INCn) {
      Serial.print(" INC");
    } else {
      Serial.print("    ");
    }
    if (as5311.err_value.LIN) {
      Serial.print(" LIN");
    } else {
      Serial.print("    ");
    }

    Serial.println();
  }
}
