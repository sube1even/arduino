#include <SoftPWM.h>
#include <SoftPWM_timer.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL; 
uint8_t msg[5]; 

  

int leftFor = 3;
int leftBack = 4;
int rightFor = 5;
int rightBack = 6;

int data;
int dataLF;
int dataLB;
int dataRF;
int dataRB;

void setup() {
  // put your setup code here, to run once:
  
  radio.begin();
  radio.openReadingPipe(1,pipe); 
  radio.startListening();
  SoftPWMBegin();
  SoftPWMSet(leftFor, 0);
  SoftPWMSet(leftBack, 0);
  SoftPWMSet(rightFor, 0);
  SoftPWMSet(rightBack, 0);


}

void loop() {

  //if signal from the radio move the bot, otherwise fail to an "all off" condition
  if (radio.available()){
    radio.read(msg,5);
    dataLF=msg[0];
    dataLB=msg[1];
    dataRF=msg[2];
    dataRB=msg[3];
    data=msg[4];

    //analogWrite(motor,data);
    if((dataLF>0&&dataLB>0)||(dataRF>0&&dataRB>0)){
      //error condition (attempting to put pwm signal into both forwards and backwards at the same time)
      Serial.println("BOTH ABOVE ERROR");
      SoftPWMSet(leftFor, 0);
      SoftPWMSet(leftBack, 0);
      SoftPWMSet(rightFor, 0);
      SoftPWMSet(rightBack, 0);
      
    }else{
      SoftPWMSet(leftFor, dataLF);
      SoftPWMSet(leftBack, dataLB);
      SoftPWMSet(rightFor, dataRF);
      SoftPWMSet(rightBack, dataRB);
    }
    
  }else{
    //No signal from radio, this can happen if the radio is transmitting too slowly
    //either reduce the delay in the tx code or increase the delay below
    SoftPWMSet(leftFor, 0);
    SoftPWMSet(leftBack, 0);
    SoftPWMSet(rightFor, 0);
    SoftPWMSet(rightBack, 0);
  }

  //delay for sinking with the tx, adjust as needed
  delay(10);

}
