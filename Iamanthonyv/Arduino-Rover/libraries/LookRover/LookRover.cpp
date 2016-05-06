#include "Arduino.h"
#include <LookRover.h>


LookRover::LookRover()
{
    debugPrintln("In Constructor LookRover::Look Rover");

}

void LookRover::init( int servoLeftPin,
                      int servoLeftStop,
                      int servoRightPin, 
		      int servoRightStop,
                      int triggerPin,
                      int echoPin,
                      int maxDistance,
                      int faceServoPin  )

{
    
	debugPrintln("in method LookRover::init()");

    	_faceServo.attach(faceServoPin);

   
        RangeRover::init(  servoLeftPin,
                           servoLeftStop,
                           servoRightPin,
                           servoRightStop,
			   triggerPin,
			   echoPin,
                           maxDistance );

}
                

void LookRover::look (int direction)
{

	_faceServo.write(direction);

}
                      
