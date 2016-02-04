/*
 * GPRS_SMS.ino
 *
 * Copyright (c) 2016 SODAQ.
 * Website    : http://sodaq.com/
 * Author     : Omar Hussein
 * Create Time: FEB 3,2016
 * 
 */
/*****************************************************************************/
//  Function:     Using GPRSBee with a Sim-Card , i will send a SMS Message 
//                to a predfined Mobile number with a predefined message.
//  Hardware:     GPRSBee rev.4 SMA , Autonomo , Autonomo Grove Shield
//  Arduino IDE:  Arduino-1.6.6
/*****************************************************************************/

#include "GPRSbee.h"

#define GPRSBEE_PWRPIN  7
#define XBEECTS_PIN     8

// Only needed if DIAG is enabled
#define DIAGPORT_RX     4
#define DIAGPORT_TX     5

#define CTS 12
#define DTR 9

bool sent_sms = false;

void setup()
{
  //The code will not start unless the serial monitor is opened or 10 sec is passed incase you want to operate Autonomo with external power source
  while ((!SerialUSB) && (millis()<10000));

  SerialUSB.begin(9600);
  SerialUSB.println("Here we start !! ");
  
  gprsbee.init(Serial1, CTS, DTR);
  digitalWrite(BEE_VCC, HIGH);

  //Power switching is still being resolved 
  gprsbee.setDiag(SerialUSB);
}
void loop()
{
  // Check if we already send a previous message or not , since we dont want to send the same message several times 
  if (sent_sms == false)
  {
    sent_sms = true;
    SerialUSB.println("Switching on..");
    bool retval = gprsbee.on();
    SerialUSB.println("...done. Retval = ");
    SerialUSB.println(retval);
   
    SerialUSB.println("Sending SMS");
    // phone number including the country code
    bool  smsSent = gprsbee.sendSMS("+436763834216", "I <3 GPRSBee");
    if (smsSent){
      SerialUSB.println("SMS sent!");
    // Set it True so we stop fullfilling the starting condition of the loop  
      sent_sms =true;
   } else {
      SerialUSB.println("SMS NOT SENT!");
    }
  }
}
