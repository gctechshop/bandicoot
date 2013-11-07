#include <Motors.h>  //Include the Motors Library
Motors motors(250);  //Setup the motors with a maximum speed, 250 is the fastest.

void setup()
{
  
}

void loop()
{ 
  //BASIC CONTROL, Always drives at maxSpeed
  motors.fwd(500);   //Drive Forward for 500mS
  motors.left(500);  //Turn Left for 500mS
  motors.rev(500);   //Drive Backwards for 500mS
  motors.right(500); //Right Right for 500mS
  //the time can be changed, "0" is continuous
  motors.stop();     //Stop Motors
  
  //INDIVIDUAL CONTROL
  //motors."l"=left,"r"=right(Direction, Speed)
  //Direction "1"=Fwd, "0"=Rev, Speed 0 = Slow, 250 = Fast
  motors.l(1, 250);   
  dt();
  motors.r(1, 250);
  dt();
  motors.l(0, 0);   
  dt();
  motors.r(0, 0);
  dt();
  motors.l(0, 250);   
  dt();
  motors.r(0, 250);
  dt();
  motors.stop();
  dt();
}

void dt()
{
  delay(500); 
}
