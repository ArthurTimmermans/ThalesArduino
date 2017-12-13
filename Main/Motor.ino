void stopMotor(){
    analogWrite(motorSpeed, 0);
    digitalWrite(motorLeftF, LOW); 
    digitalWrite(motorLeftB, LOW); 
    digitalWrite(motorRightF, LOW);
    digitalWrite(motorRightB, LOW);
}
void left(int x){
  digitalWrite(motorLeftF, LOW); 
  digitalWrite(motorLeftB, HIGH); 
  digitalWrite(motorRightF, HIGH);
  digitalWrite(motorRightB, LOW);
  for(speedm=0; speedm<=255; speedm+=5){
    analogWrite(motorSpeed, speedm);
  }
  delay(x);
  stopMotor();
}
void right(int x){
  digitalWrite(motorLeftF, HIGH); 
  digitalWrite(motorLeftB, LOW); 
  digitalWrite(motorRightF, LOW);
  digitalWrite(motorRightB, HIGH);
  for(speedm=0; speedm<=255; speedm+=5){
    analogWrite(motorSpeed, speedm);
  }
  delay(x);
  stopMotor();
}
void forward(int x){
  digitalWrite(motorLeftF, HIGH); 
  digitalWrite(motorLeftB, LOW); 
  digitalWrite(motorRightF, HIGH);
  digitalWrite(motorRightB, LOW);
  for(speedm=0; speedm<=255; speedm+=5){
    analogWrite(motorSpeed, speedm);
  }
  delay(x);
  stopMotor();
}
void backward(int x){
  digitalWrite(motorLeftF, LOW); 
  digitalWrite(motorLeftB, HIGH); 
  digitalWrite(motorRightF, LOW);
  digitalWrite(motorRightB, HIGH);
  for(speedm=0; speedm<=255; speedm+=5){
    analogWrite(motorSpeed, speedm);
  }
  delay(x);
  stopMotor();
}

bool isDirectionRight(){
  distanceMeDesF=distanceMeDes();
  if(distanceMeDesI<distanceMeDesF) return false;
  if(distanceMeDesI>=distanceMeDesF) return true;
}

