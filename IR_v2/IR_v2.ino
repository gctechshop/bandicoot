#include <Motors.h>  //Include the Motors Library
Motors motors(250);  //Setup the motors with a maximum speed, 250 is the fastest.
/*Commands are: motors.fwd(0); 0 Drives continuously, Send it a number to drive forward for that amount of time (1 second = 1000)
                motors.rev(0); 
                motors.left(0); 
                motors.right(0);
                motors.stop(); No number needed

/* The following use's Ken Shirriff IRremote library, Download from 
** https://github.com/shirriff/Arduino-IRremote install using the instructions
** Upload the IRrecvDemo Example, open the serial monitor and push the remotes buttons
** The mini remote fires 3 commands for each button press, choose any of the 3
** and copy it over the values below (after the 0x)      */

#include <IRremote.h>
int RECV_PIN = 4;  //Plug the IR receiver in, the bulb part faces backwards, bend it to face up for better contol
IRrecv irrecv(RECV_PIN);  //Setup the receiver pin on the IR sensor
decode_results results;   //Store the decoded results

unsigned long up = 0xAF59867;
unsigned long right = 0xAF548B7;
unsigned long down = 0xAF518E7;
unsigned long Left = 0xAF5A857;
unsigned long Stop = 0xAF5D02F;


void setup() //the libraries take care of pin setups
{
  irrecv.enableIRIn(); // Start the receiver
}

void loop() 
{
  if (irrecv.decode(&results)) 
  {
    if(results.value == up)
      motors.fwd(0);
    else if(results.value == right)
      motors.right(300);
    else if(results.value == down)
      motors.rev(0);
    else if(results.value == Left)
      motors.left(300);
    else if(results.value == Stop)
      motors.stop();
    irrecv.resume(); // Receive the next value
  }
}

