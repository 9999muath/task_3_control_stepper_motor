#include <Stepper.h>
#define STEPS 20
Stepper stepper(STEPS, 8, 9, 10, 11);
const int Activate =  A2;      //Activate analog reading
const int speed_change    = A0; // analog speed change
const int step_change    = A1;  //analog step change
const int dir    = A3;          //Digital Dirction -- High->forward -- Low->backward
const int FORWARD    = A4;      //Manual --> if Activated the motor will be moving forward Until the button is deactivated 
const int BACKWARD    = A5;     //Manual --> if Activated the motor will be moving backward Until the button is deactivated 
const int LED_warning    = 0;   // will Activate if forward & backward botton is activated in the same time
int val, previous;              // two varible to control steps
void setup()
{ pinMode(Activate, INPUT_PULLUP);
pinMode(speed_change, INPUT_PULLUP);
pinMode(dir, INPUT_PULLUP);
}
void loop() {
  int sensorReading = analogRead(speed_change);
    int motorSpeed = map(sensorReading, 0, 1023, 1, 100);

  if (digitalRead(Activate)== HIGH){
  if(digitalRead(FORWARD)== LOW && digitalRead(BACKWARD)== LOW){

  if(digitalRead(dir)== HIGH){
  val = map(analogRead(step_change), 0 , 1023, 0, 20);
  stepper.setSpeed(motorSpeed);
  stepper.step(val-previous);
  previous = val;
  delay(20);
  digitalWrite(LED_warning, LOW);
}
else if (digitalRead(dir)== LOW){
  val = map(analogRead(step_change), 0 , 1023, 0, 20);

  stepper.setSpeed(motorSpeed);
  stepper.step(previous-val);
  previous = val;
  delay(20);
  digitalWrite(LED_warning, LOW);}}}

  
  else  if(digitalRead(FORWARD)== HIGH && digitalRead(BACKWARD)== LOW){
    stepper.setSpeed(motorSpeed);
    stepper.step(1);
    delay(20);
    digitalWrite(LED_warning, LOW);}

    
 else  if(digitalRead(FORWARD)== LOW && digitalRead(BACKWARD)== HIGH){
    stepper.setSpeed(motorSpeed);
    stepper.step(-1);
    delay(20);
    digitalWrite(LED_warning, LOW);}

    
 else  if(digitalRead(FORWARD)== HIGH && digitalRead(BACKWARD)== HIGH){
    stepper.setSpeed(motorSpeed);
    stepper.step(0);
    delay(20);
    digitalWrite(LED_warning, HIGH);}
 
else {stepper.step(0);}
}
