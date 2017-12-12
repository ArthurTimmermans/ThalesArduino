void IRdistance(){
  SharpIR SharpIR(irPin, 1080);
  //SharpIR SharpIR(irPin, 100, 93, 1080)// Pin, measurements, valid %, model
  return SharpIR.distance();
}

