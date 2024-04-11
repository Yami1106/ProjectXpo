//Instruction
//433Mhz Receiver Pin: Arduino GPIO 11

//RECEIVE DATA DETAILS
/*
   1 => FORWARD
   2 => BACKWARD
   3 => RIGHT
   4 => LEFT
*/

//Library
#include "US.h"
#include "MOTOR_CONTROL.h"
#include <VirtualWire.h>

void setup()
{
  Serial.begin(9600);	// Debugging only
  Serial.println("setup");

  MOTOR_PIN_INITIATE();

  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
  MOTOR_LOOP();

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;
    digitalWrite(13, true);
    Serial.print("Got: ");
    for (i = 0; i < buflen; i++)
    {
      Serial.print(char(buf[i]));
    }

    if (buf[0] == '0') MOTOR_DIR_CUR = STOP;
    if (buf[0] == '1') {
      if (readDistance() > 10)
        MOTOR_DIR_CUR = FORWARD;
      else
        MOTOR_DIR_CUR = STOP;
    }
    if (buf[0] == '2') MOTOR_DIR_CUR = BACKWARD;
    if (buf[0] == '3') MOTOR_DIR_CUR = RIGHT;
    if (buf[0] == '4') MOTOR_DIR_CUR = LEFT;
    Serial.println("");
    digitalWrite(13, false);
  }
}
