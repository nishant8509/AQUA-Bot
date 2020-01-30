  /**********************************************************************************                     
     * Project Name:   AQUABOT
     * Author List:     NISHANT MISHRA, MAYANK BANSAL                     
     * Filename:        rover                   
     * Functions:      setup,loop,stop                      
     * Global Variables:   val,nb                       
   ***********************************************************************************                         
  */
int val;

int nb;
/* *******************************************************************************************************************
 * Function Name: Setup
 * Input:     None
 * Output:        Operations such as starting motor pump
 * Logic:         The Function is used to Perform the operation to be performed By the Rover
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/



void setup() {

// put your setup code here, to run once:

Serial.begin(9600);

pinMode(9,OUTPUT);

pinMode(8,OUTPUT);

pinMode(7,OUTPUT);

pinMode(6,INPUT);

}

// put your main code here, to run repeatedly:
/* *******************************************************************************************************************
 * Function Name: loop
 * Input:     None
 * Output:        ROver operation
 * Logic:         The Function is used to Decide which Arduino pin will match
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/

void loop()

{

if(Serial.available()>0)

{

int data= Serial.read();

Stop();

if(data=='R')

{

digitalWrite(9,HIGH);

digitalWrite(8,LOW);

digitalWrite(6,HIGH);

digitalWrite(7,LOW);

}

else if(data=='L')

{

digitalWrite(9,LOW);

digitalWrite(8,HIGH);

digitalWrite(6,LOW);

digitalWrite(7,HIGH);

}else if(data=='F'){

digitalWrite(9,LOW);

digitalWrite(8,HIGH);

digitalWrite(6,HIGH);

digitalWrite(7,LOW);

}else if(data=='B'){

digitalWrite(9,HIGH);

digitalWrite(8,LOW);

digitalWrite(6,LOW);

digitalWrite(7,HIGH);

}

}

}
/* *******************************************************************************************************************
 * Function Name: Stop
 * Input:     None
 * Output:        Operations such as stopping rovor
 * Logic:         The Function is used to stop the Rover
 * Example Call:  Called Automatically By the App
 ********************************************************************************************************************** 
*/

void Stop()

{

digitalWrite(9,LOW);

digitalWrite(8,LOW);

digitalWrite(6,LOW);

digitalWrite(7,LOW);

}
