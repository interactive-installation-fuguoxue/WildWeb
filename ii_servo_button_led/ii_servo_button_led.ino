#include <Servo.h>

Servo myservoL, myservoDL;  // create servo object to control a servo
// twelve servo objects can be created on most boards


 const int buttonPinLike = 12;
 const int buttonPinDislike = 13;
 const int servoPinL  = 10;
 const int servoPinDL = 11;


const int redD = 5;
const int blueD  = 6;
const int greenD = 7;


const int greenL = 3;
const int blueL  = 9;

int pos = 0;    // variable to store the servo position
int lastButtonStateL;    // the previous state of button
int currentButtonStateL; // the current state of button
int lastButtonStateDL;    // the previous state of button
int currentButtonStateDL; // the current state of button

int x = 0;                              // a place to hold pin values

void setup() {
    Serial.begin(9600);                // initialize serial
    pinMode(buttonPinLike, INPUT_PULLUP); // set arduino pin to input pull-up mode
    pinMode(buttonPinDislike, INPUT_PULLUP);
    // for(int i = 2; i <= 13; i++){
    //   pinMode(i, INPUT_PULLUP);
    // }
    myservoL.attach(servoPinL);
    myservoDL.attach(servoPinDL);   
    currentButtonStateL = digitalRead(buttonPinLike);
    currentButtonStateDL = digitalRead(buttonPinDislike);

    pinMode(redD, OUTPUT);
    pinMode(greenD, OUTPUT);
    pinMode(blueD, OUTPUT);
    pinMode(greenL, OUTPUT);
    pinMode(blueL, OUTPUT);
}

void loop() {

  // colorWipe(strip.Color(  0,   0, 255), 50); // Blue LED strips

  lastButtonStateL    = currentButtonStateL;      // save the last state
  lastButtonStateDL    = currentButtonStateDL;      // save the last state
  currentButtonStateL = digitalRead(buttonPinLike); // read new state
  currentButtonStateDL = digitalRead(buttonPinDislike); // read new state

  digitalWrite(blueL, HIGH);

  digitalWrite(greenD, HIGH);
  digitalWrite(blueD, HIGH);

  // check if there was a request for data, and if so, send new data
  if (Serial.available() > 0) {
    if (Serial.read() == 'r') {
      for (int pin= 0; pin<=5; pin++){      // Read and send analog pins 0-5
        x = analogRead(pin);
        sendValue (x);
      }
      for (int pin= 2; pin<=13; pin++){     // Read and send digital pins 2-13
        x = digitalRead(pin);
        sendValue (x);
      }
      
      Serial.println();                 // Send a carriage returnt to mark end of pin data. 
      delay (5);                        // add a delay to prevent crashing/overloading of the serial port
    }
  }

  // lastButtonStateL = currentButtonStateL;      // save the last state
  // currentButtonStateL = digitalRead(buttonPin); // read new state
  // Serial.println(currentButtonStateL);

  if(lastButtonStateL == HIGH && currentButtonStateL == LOW) {

    Serial.println("The LIKE button is pressed");

    // colorWipe(strip.Color(  0, 255,   0), 50); // Green

    for (pos = 0; pos <= 140; pos += 1) { // goes from 0 degrees to 140 degrees
      // in steps of 1 degree
      myservoL.write(pos);              
      delay(15);                       // waits 15ms for the servo to reach the position
   }
    setColorL();

  } 
  // else {
  //   myservoL.write(0);
  // }

  if(lastButtonStateDL == HIGH && currentButtonStateDL == LOW) {

    Serial.println("The DISLIKE button is pressed");

    // colorWipe(strip.Color(255,   0,   0), 50); // Red

    for (pos = 0; pos <= 140; pos += 1) { // goes from 0 degrees to 140 degrees
      // in steps of 1 degree
      myservoDL.write(pos);              
      delay(15);                       // waits 15ms for the servo to reach the position
   }
    setColorD();
  } 
  // else {
  //   myservoDL.write(0);
  // }


}


void setColorD() {
  digitalWrite(redD, HIGH);
  digitalWrite(blueD, LOW);
  digitalWrite(greenD, HIGH);

  digitalWrite(blueL, HIGH);
  digitalWrite(greenL, LOW);
}

void setColorL() {
  digitalWrite(blueL, LOW);
  digitalWrite(greenL, HIGH);

  digitalWrite(redD, HIGH);
  digitalWrite(blueD, HIGH);
  digitalWrite(greenD, LOW);
}

void sendValue (int x){              // function to send the pin value followed by a "space". 
  Serial.print(x);
  Serial.write(32); 
}