#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);
//commands to the gsm and their functionality
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
//  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
//  updateSerial();
//  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
//  updateSerial();
//  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
//  updateSerial();
//  mySerial.println("ATI");//Gets the model and version of the module
//  updateSerial();
//  mySerial.println("AT+COPS?");//Checks that you are connected to a network
//  updateSerial();
//  mySerial.println("AT+COPS=?");//Returns all operators in that network
//  updateSerial();
//  mySerial.println("AT+CBC");//Return the battery state of the module
//  updateSerial();

///SENDING MESSAGES
    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode;selects SMSmessage format as a text
    updateSerial();
    mySerial.println("AT+CMGS=\"+2540797229001\"");//sends sms to the phone number specified
    mySerial.print("Hope you are doing okay.Welcome:)"); //text content
    updateSerial();
///RECEIVING MESSAGES
//    mySerial.write(26);//represents the "ctrl+z" character represented as SMS where it is the 26th non-printing character described as substitute' in the ASCII table
//    mySerial.println("AT+CNMI=2,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
//    updateSerial();
///DIALING A CALL
//    mySerial.println("ATD+ +2540797229001;"); // Dials the number that is specified (;)modifier seperates the dial string into multiple dial commands;all but the last must end with a semicolon
//    updateSerial();
//    delay(20000); // wait for 20 seconds...
///HANGS UP THE CALL
//    mySerial.println("ATH"); //hangs up the call
//    updateSerial();
///RECEIVES AN INCOMING CALL
//    mySerial.println("ATA"); //hangs up the call
//    updateSerial();
}


void loop()
{
  //updateSerial();//The loop function is not empty as we are polling for newly arrived SMS messages. 
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
