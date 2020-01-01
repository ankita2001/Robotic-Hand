      // code for detecting impacts with 3-axis accelerometer and contol two dc motors

#include<microM.h>
#include <Servo.h>

#define THRESHOLD 150 //In order to determine the state of the hand (opened/closed)
#define EMGPIN 3 //Analog pin connected to Muscle Sensor V3 Board
#define LITTLEPIN  2 //Digital pin used by Little servo
#define RINGPIN    3 //Digital pin used by Ring servo
#define MIDDLEPIN  9 //Digital pin used by Middle servo
#define INDEXPIN   10 //Digital pin used by Index servo
#define THUMBPIN   11 //Digital pin used by Thumb servo

//Constants used to open and close the fingers
#define LITTLE 1 
#define RING   2
#define MIDDLE 3
#define INDEX  4
#define THUMB  5

Servo servoLittleFinger;         // Define servo fingers
Servo servoRingFinger;         // Define servo fingers
Servo servoMiddleFinger;         // Define servo fingers
Servo servoIndexFinger;         // Define servo fingers
Servo servoThumbFinger;         // Define servo fingers

int finger;

// Motion routines for handopen and handclose
void openhand(){
  for(finger = 1; finger < 6; finger++)
  {
    openFinger(finger);
   }
 }
void closehand(){
  for(finger = 1; finger < 6 ; finger++)
  {
    closeFinger(finger);
    }
 }

// You have to rewrite properly the functions to open and close the fingers 
// according of your assembly
// In my case, middle and index fingers are opened when servo is at 170 degrees and the others when servo is at 0 degrees

void openFinger(int finger){
  if(finger==LITTLE){servoLittleFinger.write(170);} // Little finger
  else if(finger==RING){servoRingFinger.write(170);}// Ring finger
  else if(finger==MIDDLE){servoMiddleFinger.write(170);}// Middle finger
  else if(finger==INDEX){servoIndexFinger.write(170);}// Index finger
  else if(finger==THUMB){servoThumbFinger.write(170);}//Thumb finger
}

void closeFinger(int finger){
  if(finger==LITTLE){servoLittleFinger.write(10);} // Little finger 
  else if(finger==RING){servoRingFinger.write(10);}// Ring finger
  else if(finger==MIDDLE){servoMiddleFinger.write(10);}// Middle finger
  else if(finger==INDEX){servoIndexFinger.write(10);}// Index finger
  else if(finger==THUMB){servoThumbFinger.write(10);}//Thumb finger
}

void setup() {
  // put your setup code here, to run once:

  microM.Setup();                        // this must be called first in your setup function
  microM.sensitivity=50;                 // if your robot vibrates or moves over a rough surface then increase this value to prevent false triggering
  microM.devibrate=100;                   // depends on the construction of your robot. Increase the value if you get additional readings after initial impact
  
  Serial.begin(9600);                    // initialize serial monitor

  servoLittleFinger.attach(LITTLEPIN);  // Set Little finger servo to digital pin 2
  servoRingFinger.attach(RINGPIN);  // Set Ring finger servo to digital pin 3
  servoMiddleFinger.attach(MIDDLEPIN);  // Set Middle finger servo to digital pin 9
  servoIndexFinger.attach(INDEXPIN);  // Set Index finger servo to digital pin 10
  servoThumbFinger.attach(THUMBPIN);  // Set Thumb finger servo to digital pin 11

}

void loop() {
  // put your main code here, to run repeatedly:   

    pos();
    int value = analogRead(EMGPIN); //Sampling analog signal
    if(value>THRESHOLD) //If the value of the sample is greater than THRESHOLD means that the hand has been closed
    {closehand();}
    else //Otherwise the hand is open
    {openhand();}
    Serial.println(value); //You can use serial monitor to set THRESHOLD properly, comparing the values shown when you open and close your hand
}

  void pos()
  {
      microM.Impact();                       // function must be called at least once every 2mS to work accurately
    Serial.println(""); 
    Serial.print("\tMagnitude:");
    Serial.print(microM.magnitude);
    Serial.print("\tDelta X:");
    Serial.print(microM.deltx);
    Serial.print("\tDelta Y:");
    Serial.print(microM.delty);
    Serial.print("\tDelta Z:");
    Serial.println(microM.deltz);
    Serial.print("\tX axis:");
    Serial.print(microM.xaxis);
    Serial.print("\tY axis:");
    Serial.print(microM.yaxis);
    Serial.print("\tZ axis:");
    Serial.print(microM.zaxis);
    Serial.println(""); 
    microM.magnitude=0; 
    delay(1000);// prevents display repeating the same values
  }

