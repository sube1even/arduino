/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo weapon;  // create servo object to control a servo

int nPulseWidth = DEFAULT_PULSE_WIDTH; // 1500 is stopped 2000 is max

void setup() 
{
  weapon.attach(7);
}

void loop() 
{
  nPulseWidth = 1750;
  weapon.writeMicroseconds(nPulseWidth);
  delay(1000);
}

