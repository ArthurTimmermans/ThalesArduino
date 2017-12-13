
void IRdistance(){
  SharpIR SharpIR(irPin, 1080);
  return SharpIR.distance();
}

float distanceMeDes(){
  return sqrt(pow((destination.get_longitude()-myposition.get_longitude()), 2)+pow((destination.get_latitude()-myposition.get_latitude()), 2));
}

