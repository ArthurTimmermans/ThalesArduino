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
