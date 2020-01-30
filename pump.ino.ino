 /**********************************************************************************                     
     * Project Name:   AQUABOT
     * Author List:     NISHANT MISHRA, MAYANK BANSAL                     
     * Filename:            pump              
     * Functions:           setup,loop,dig,back,stop,pump                 
     * Global Variables:    command                   
   ***********************************************************************************                         
  */
#include <AFMotor.h>

//initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ); 

AF_DCMotor motor3(3, MOTOR34_1KHZ);


char command; 
/* *******************************************************************************************************************
 * Function Name: Setup
 * Input:     none
 * Output:        
 * Logic:         
 * Example Call:  
 ********************************************************************************************************************** 
void setup() 
{       
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
}
/* *******************************************************************************************************************
 * Function Name: Loop
 * Input:     Inputs are Provided By User
 * Output:        It Calls the Function to perform the Operations Such as Starting Motor PUMP
 * Logic:         The Function is used to Determine the operation to be performed By the Rover
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/
void loop(){
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    //Serial.println(command);
    switch(command){
    case 'F':  
       dig();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      pump();
      break;
    
    }
  } 
}
/* *******************************************************************************************************************
 * Function Name: dig
 * Input:     None
 * Output:        Inform the Rover to run the dig motor
 * Logic:         The Function is used to Move the Dig Motor Forward
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/
void dig()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  
}
/* *******************************************************************************************************************
 * Function Name: back
 * Input:     None
 * Output:        Inform the Rover to run the dig motor
 * Logic:         The Function is used to Move the Dig Motor Backward
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/
void back()
{
  motor1.setSpeed(255); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  
}
/* *******************************************************************************************************************
 * Function Name: pump
 * Input:     None
 * Output:        Inform the Rover to run the pump motor
 * Logic:         The Function is used to Start the Motor Pump So that plants can be watered
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/
void pump()
{
  
  motor3.setSpeed(255); //Define maximum velocity
  motor3.run(FORWARD);  //turn on the pump
  
}
/* *******************************************************************************************************************
 * Function Name: stop
 * Input:     None
 * Output:        Inform the Rover to stop the pump motor
 * Logic:         The Function is used to Stop the Motor Pump
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/
void Stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
