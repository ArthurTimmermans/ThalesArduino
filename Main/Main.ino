/*
 * WE MUST CHECK HOW THIS LIBRARY RETURNS THE LONGITUDE AND LATITUDE AFTER PARSING. DOES IT USE ONLY DEGREES OR MINUTES AS WELL??? THIS CODE ASSUMES THAT IT USES ONLY DEGREES
 * 
 */

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Stepper.h>
#include <math.h>

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
void alignPos(double &orientationAngle, int &stepLeft, int &stepRight); //moves the robot so that it points straight to the destination, also updates the value of the orientation angle
bool checkForObstacle(); //checks if there are obstacles up to 80 cm in front of the robot
void updateOrientation(double &orientationAngle);//only updates the information for the orientation angle
void straight(float meters);//moves the robot forward
/*
 * variables and object declaration
 */
int stepsPerRevolution=100, radiusTire=0.03; //ENTER HERE THE STEPS PER REVOLUTION, and the radius of the Tire
Stepper rightStepper(stepsPerRevolution, 8, 9);
Stepper leftStepper(stepsPerRevolution, 10, 11);
int stepCountRight=0, stepCountLeft=0;
positionr initialposition, myposition, destination; //for use in the main
bool grabStatus=false;
const double pi=3.14159265;
double orientationAngle=pi/2, destinationAngle; //these are used to keep track of the orientation of the robot
SoftwareSerial mySerial(3,2); //Setting new TTL serial communication 3-Rx 2-Tx
Adafruit_GPS GPS(&mySerial); //Initializing GPS objext


void setup() {
  Serial.begin(115200); //This baud rate is higher, so that it is sure that it will be able to read from the GPS
  GPS.begin(9600); //Turns on the gommunication between GPS and arduino
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY); //telling the GPS to send only the RMC NMEA sentences, since the only thing we need is possition
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // the NMEA sentences are updated 1 time per sec
  delay(1000); //gives a some time to the GPS to figure the new commands
  initialposition=GPS_position();
  //here we have to define the destination
  //destination.set_longitude(longitude);
  //destination.set_latitude(latitude);
  destinationAngle=atan(destination.get_longitude()/destination.get_latitude());
}

void loop() {
  myposition=GPS_position();
  if(!grabStatus){
    if(!(myposition==destination)){ //using !(xx==xx) instead of xx!=xx, so that I don't have to overload another operator in the class
      alignPos(); 
      if(!checkForObstacle()){
        straight(0.5);
        updateOrientation(); 
      }
      else{
        /*
         * there is an obstacle that has to be surrounded
         */
      }
    }
    else{
    /*
     * The destination is riched and now the robot has to grab the thing and bring it back
     * change grabStatus
     */
     grabStatus=true;
   }
  }
   else{
    /* 
     *  Will come here if grabStatus is true and now the robot has to come back to initial destination
     */
  }
}
/*
 * Functions definition
 */
positionr GPS_position(){ //a function which returns the current positionr
  positionr current_position; //creating object that will be returned
    bool t=false; //used to test for successfull parsing; 
    while(!t){
      if(GPS.newNMEAreceived()) {
       if(GPS.parse(GPS.lastNMEA())){ //checking if parsing has been successful
        t=true;
        current_position.set_longitude(GPS.longitude); //asssigning the current positionr to the object
        current_position.set_latitude(GPS.latitude); //asssigning the current positionr to the object
       }
      } 
    }
    return current_position;
}

void alignPos(){
  while(abs(orientationAngle-destinationAngle)>(pi/180)){
    //the program comes here if the robot is not aligned properly
    //have to think of an idea to run motors in parallel
  }
  return;
}
bool checkForObstacle(){
  
}
void updateOrientation(){
  
}
void straight(float meters){
  
}
