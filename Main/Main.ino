/*
 * WE MUST CHECK HOW THIS LIBRARY RETURNS THE LONGITUDE AND LATITUDE AFTER PARSING. DOES IT USE ONLY DEGREES OR MINUTES AS WELL??? THIS CODE ASSUMES THAT IT USES ONLY DEGREES
 * 
 */

#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

class position{ //creating a class for the position so that it is easier to work with it
  private:
  double longitude, latitude;
  public:
  const double get_longitude(){return longitude;}
  const double get_latitude(){return latitude; }
  void set_longitude(const double newLongitude) {longitude=newLongitude; }
  void set_latitude(const double newLatitude) {latitude=newLatitude; }
  const bool operator==(const position &other){ //creating an operator with which to check if two positions are the same
    if((abs(this->longitude-other.longitude)<0.001) && (abs(this->latitude-other.latitude)<0.001))//not sure if it has to be -> or just; setting the sensitivity to three decimal place
    return true;
    else return false;
  }
};

position initialPosition, myPosition, destination; //for use in the main
/* 
 *  HERE WE HAVE TO DEFINE THE LONGITUDE AND LATITUDE OF THE DESTINATION
 *  
 */
bool grabStatus=false;
SoftwareSerial mySerial(3,2); //Setting new TTL serial communication 3-Rx 2-Tx
Adafruit_GPS GPS(&mySerial); //Initializing GPS objext

void setup() {
  Serial.begin(115200); //This baud rate is higher, so that it is sure that it will be able to read from the GPS
  GPS.begin(9600); //Turns on the gommunication between GPS and arduino
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY); //telling the GPS to send only the RMC NMEA sentences, since the only thing we need is possition
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // the NMEA sentences are updated 1 time per sec
  delay(1000); //gives a some time to the GPS to figure the new commands
  initialPosition=GPS_position();
}

void loop() {
  myPosition=GPS_position();
  if(!grabStatus){
    if(!(myPosition==destination)){ //using !(xx==xx) instead of xx!=xx, so that I don't have to overload another operator in the class
      //we are not currently at the destination so we have to move in that direction.
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
position GPS_position(){ //a function which returns the current position
  position current_position; //creating object that will be returned
    bool t=false; //used to test for successfull parsing; 
    while(!t){
      if(GPS.newNMEAreceived()) {
       if(GPS.parse(GPS.lastNMEA())){ //checking if parsing has been successful
        t=true;
        current_position.set_longitude(GPS.longitude); //asssigning the current position to the object
        current_position.set_latitude(GPS.latitude); //asssigning the current position to the object
       }
      } 
    }
    return current_position;
}

