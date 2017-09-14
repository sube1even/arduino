#include <SoftPWM.h>
#include <SoftPWM_timer.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <Servo.h>

Servo weapon;  // create servo object to control a servo

RF24 radio(9,10);
const uint64_t pipe = 0xB4B31E2CA9LL; 
uint8_t msg[5];  
 
int leftFor = 3;
int leftBack = 4;
int rightFor = 5;
int rightBack = 6;

int weaponPin = 7;

int dataPwmWeapon;
int dataLF;
int dataLB;
int dataRF;
int dataRB;

void setup() {
    Serial.begin(9600);
    
    // put your setup code here, to run once:
    radio.begin();
    radio.openReadingPipe(1,pipe); 
    radio.startListening();
    SoftPWMBegin();
    SoftPWMSet(leftFor, 0);
    SoftPWMSet(leftBack, 0);
    SoftPWMSet(rightFor, 0);
    SoftPWMSet(rightBack, 0);
  
    weapon.attach(weaponPin);
    weapon.writeMicroseconds(0);
}

void loop() {

  //if signal from the radio move the bot, otherwise fail to an "all off" condition
  if (radio.available()){
      radio.read(msg,5);
      dataLF=msg[0];
      dataLB=msg[1];
      dataRF=msg[2];
      dataRB=msg[3];
      dataPwmWeapon=msg[4];
  
      Serial.print(dataLF);
      Serial.print(", ");
      Serial.print(dataLB);
      Serial.print(", ");
      Serial.print(dataRF);
      Serial.print(", ");
      Serial.print(dataRB);
      Serial.print(", ");
      Serial.println(map(dataPwmWeapon,0,255,0,2000));
      
      dataPwmWeapon = map(dataPwmWeapon,0,255,0,2000);
      weapon.writeMicroseconds(dataPwmWeapon);

      delay(10);

    if((dataLF>0 && dataLB>0) || (dataRF>0 && dataRB>0)){
      //error condition (attempting to put pwm signal into both forwards and backwards at the same time)
      Serial.println("BOTH ABOVE ERROR");
      SoftPWMSet(leftFor, 0);
      SoftPWMSet(leftBack, 0);
      SoftPWMSet(rightFor, 0);
      SoftPWMSet(rightBack, 0);
    } else {
      SoftPWMSet(leftFor, dataLF);
      SoftPWMSet(leftBack, dataLB);
      SoftPWMSet(rightFor, dataRF);
      SoftPWMSet(rightBack, dataRB);
    }
    
  } else {
    //No signal from radio, this can happen if the radio is transmitting too slowly
    //either reduce the delay in the tx code or increase the delay below
    SoftPWMSet(leftFor, 0);
    SoftPWMSet(leftBack, 0);
    SoftPWMSet(rightFor, 0);
    SoftPWMSet(rightBack, 0);
    weapon.writeMicroseconds(0);
  }

  //delay for sinking with the tx, adjust as needed
  delay(10);

}
