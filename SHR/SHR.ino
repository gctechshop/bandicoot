#include <Motors1284.h> //Include the Motors Library
Motors motors(200);     //Setup the motors with a maximum speed, 250 is the fastest.

#include <Servo.h>
Servo scanServo;
int servoPos = 90;

const int IRPin = 7;      // Sharp 20cm = 150cm IR Range Finder
//int IRAverage[5] = {0,0,0,0,0};   
//int ThisRead = 0;
//int Total = 0;
//float Distance = 0;

const int leftBump = A0; //anything less than 900 means blocked
const int rightBump = A1;
int leftBlocked = 950;
int rightBlocked = 950;

int FoundPos = 0;
float FoundDist = 20;     // set's the min distance, SHARP GP20A02YK0F's accurate range 20cm-150cm

void setup() 
{ 
  delay(2000); //Wait for fingers to be removed from on switch
  for(int i = 0; i < 10; i++)
  {
    int scanLeft = analogRead(leftBump);
    if(scanLeft < leftBlocked)
    {
      leftBlocked = scanLeft-50;
    }
    delay(25);
    int scanRight = analogRead(rightBump);
    if(scanRight < rightBlocked)
    {
      rightBlocked = scanRight-50;  
    }
    delay(25);
  }
  
  //Serial.begin(9600);
  scanServo.attach(3);  // attaches the servo on pin 9 to the servo object 
  scanServo.write(servoPos);  //Move the Servo to 90
  delay(15);                       // waits 15ms for the servo to reach the position 

  motors.fwd(0); //Start Motors
}

void loop()
{
  if(analogRead(leftBump) < leftBlocked || analogRead(rightBump) < rightBlocked)
  {
    motors.stop();
    delay(50);
    motors.rev(250);
    //motors.right(300);
  for(int Pos = 0; Pos < 180; Pos += 5)     //loop sweeping servo left to right: Set's Pos to 0, loops while Pos is < 180, add's 5 to Pos with each loop
  {
    scanServo.write(Pos);                        //Set's servo position to Pos
    delay(100);                                     //waits for servo to move
    float volts = analogRead(IRPin)*0.0048828125;   //Converts Analog reading (0 - 1023) back to a voltage: Value from IR sensor * (5/1024)
    float distance = 65*pow(volts, -1.10);          //Not totally accurate but close enough, credit to www.luckylarry.co.uk
    if (distance > FoundDist)// && distance < 24)      //records the distance and position of the servo for the closest object within the sensors accurate range
    {
      FoundDist = distance;
      FoundPos = Pos;
    }
  }
  scanServo.write(FoundPos); 
  delay(500); //SHOW WHERE LONGEST WAS SEEN
  if(FoundPos > 90)
  {
    motors.right((FoundPos - 90) * 9);
    scanServo.write(90);                        //Set's servo position to Pos
    motors.fwd(0);
  } else
  {
    motors.left((90 - FoundPos) * 9);
    scanServo.write(90);                        //Set's servo position to Pos
    motors.fwd(0);
  }    
  }  
  /*Serial.print(analogRead(leftBump));
  Serial.print(",  ");
  Serial.println(analogRead(rightBump));
  delay(200); */

}
/*
void RollDistance()    // The Rolling Averge Calculator
{
  Total = Total - IRAverage[ThisRead];   // Minus the oldest read
  IRAverage[ThisRead] = analogRead(IRPin);  // Replaces the oldest Read
  Total = Total + IRAverage[ThisRead];   // Adds the New Read to the total
  ThisRead ++;     // Increment the Reading number
  
  if (ThisRead >= 5)   // Loops the Reading Number
  {
    ThisRead = 0;
  }
  float volts = (Total / 5)*0.0048828125;  // Converts it back into a voltage, volts (5) / Analog steps (1024)
  Distance = 65 * pow(volts, -1.1);       // Volts to the power of -1.1, times 65 gives a rough distance in cm 
} */
