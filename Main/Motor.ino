void stopMotor(){
  analogWrite(motorLeftF, 0);
  analogWrite(motorRightF, 0);
  analogWrite(motorLeftB,0);
  analogWrite(motorRightB, 0);
}
void left(int x){
  analogWrite(motorLeftF, 255);
  analogWrite(motorRightF, 0);
  analogWrite(motorLeftB, 0);
  analogWrite(motorRightB, 255);
  delay(x);
  stopMotor();
}
void right(int x){
  analogWrite(motorLeftF, 0);
  analogWrite(motorRightF, 255);
  analogWrite(motorLeftB, 255);
  analogWrite(motorRightB, 0);
  delay(x);
  stopMotor();
}
void forward(int x){
  analogWrite(motorLeftF, 255);
  analogWrite(motorRightF, 255);
  analogWrite(motorLeftB, 0);
  analogWrite(motorRightB, 0);
  delay(x);
  stopMotor();
}
void backward(int x){
  analogWrite(motorLeftF, 0);
  analogWrite(motorRightF, 0);
  analogWrite(motorLeftB, 255);
  analogWrite(motorRightB, 255);
  delay(x);
  stopMotor();
}

