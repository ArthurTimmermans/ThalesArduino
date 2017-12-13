/*
 * WE MUST CHECK HOW THIS LIBRARY RETURNS THE LONGITUDE AND LATITUDE AFTER PARSING. DOES IT USE ONLY DEGREES OR MINUTES AS WELL??? THIS CODE ASSUMES THAT IT USES ONLY DEGREES
 * 
 */

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Stepper.h>
#include <SharpIR.h>

#define motorLeftB 4 //if this is high and motorLeftF is low the motor moves backward
#define motorRightB 7 //if this is high and motorRightF is low the motor moves backward
#define motorLeftF 8 //if this is high and motorLeftB is low the motor moves forward
#define motorRightF 9 //if this is high and motorRightB is low the motor moves forward
#define motorSpeed 5 //PWM signal that will control the speed of the motors. We need one, that will be duplicated, because the motors will move symetrically 
#define turnTimeLeft 100 //
#define turnTimeRight 100 //
#define irPin A0

///NOTE! I know that this is a terrible way to use classes, but I do it for the sake of saving time, and because the classes in this case are pretty simple.
class positionr{ //creating a class for the position so that it is easier to work with it
  private:
  double longitude, latitude;
  public:
  const double get_longitude(){return longitude;}
  const double get_latitude(){return latitude; }
  void set_longitude(const double newLongitude) {longitude=newLongitude; }
  void set_latitude(const double newLatitude) {latitude=newLatitude; }
  const bool operator==(const positionr &other){ //creating an operator with which to check if two positions are the same
    if((abs(this->longitude-other.longitude)<0.001) && (abs(this->latitude-other.latitude)<0.001))//not sure if it has to be -> or just; setting the sensitivity to three decimal place
    return true;
    else return false;
  }
};
/*
 * Function declaration
 */
void stopMotor(); 
void left(int x);
void right(int x);
void forward(int x);
void backward(int x);
void IRdistance();
bool isDirectionRight();
float distanceMeDes();
positionr GPS_position(); //returns the current position

/*
 * variables and object declaration
 */

positionr myposition, destination; //for use in the main
bool grabStatus=false;
SoftwareSerial mySerial(3,2); //Setting new TTL serial communication 3-Rx 2-Tx
Adafruit_GPS GPS(&mySerial); //Initializing GPS objext
int speedm=0;
float distanceMeDesI, distanceMeDesF; //used to measure if the robot is going in the right direction 

void setup() {
  Serial.begin(115200); //This baud rate is higher, so that it is sure that it will be able to read from the GPS; not sure if we need this serial though
  GPS.begin(9600); //Turns on the gommunication between GPS and arduino
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY); //telling the GPS to send only the RMC NMEA sentences, since the only thing we need is possition
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // the NMEA sentences are updated 1 time per sec
  delay(1000); //gives a some time to the GPS to figure the new commands
  myposition=GPS_position();
  pinMode(motorLeftB, OUTPUT);
  pinMode(motorLeftF, OUTPUT);
  pinMode(motorRightB, OUTPUT);
  pinMode(motorRightF, OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  //here we have to define the destination
  //destination.set_longitude(longitude);
  //destination.set_latitude(latitude);
}

void loop() {
 if(!(myposition==destination)){
  //if the robot is not at the destination
  distanceMeDesI=distanceMeDes();
  forward(500);
  while(!isDirectionRight()){
    //the robot doesn't go in the right direction
    distanceMeDesI=distanceMeDes();
    left(100); 
    forward(500);
  }
 }
 else{
  //if the robot is at the destination
  //has to grab the thing
  //in the test scenario I make him go round so that we know when the robot thinks that he is at the code. 
  left(5000);
  exit(0);
  //end of test scenario
 }
}


