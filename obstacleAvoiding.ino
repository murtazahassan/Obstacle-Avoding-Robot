// Install Libaray HCRS04 by Martin Sosic from Manage Library

#include <HCSR04.h>
#include <Servo.h>

Servo myservo;
UltraSonicDistanceSensor distanceSensor(13, 12);
double myUltra = 0;
int myPins[6] = {5, 6, 7, 8, 9, 3};       // MOTOR PIN NUMBERS

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(myPins[i], OUTPUT);
  }
  Serial.begin(9600);
  myservo.attach(11);
  myservo.write(80); // Center Position 
}


void loop() {

  myUltra = distanceSensor.measureDistanceCm();
  Serial.println(myUltra);
  if (myUltra < 20 && myUltra != -1) {
    obstacleDetected();
  }
  else {
    moveRobot(100, 90);
    delay(100);
  }

}

void obstacleDetected() {
  moveRobot(0, 0); delay(500);
  myservo.write(0);
  delay(500);
  myUltra = distanceSensor.measureDistanceCm();
  if (myUltra > 20 || myUltra == -1) {
    moveRobot(-100, -100); delay(500);
    moveRobot(-70, 70); delay(500);
  }
  else {
    moveRobot(0, 0); delay(500);
    myservo.write(180);
    delay(500);
    myUltra = distanceSensor.measureDistanceCm();
    if (myUltra > 20 || myUltra == -1) {
      moveRobot(-100, -100); delay(500);
      moveRobot(70, -70); delay(500);

    }
    else {
      moveRobot(-70, -70);
      delay(500);
      moveRobot(-70, -70);
      delay(1000);
    }
  }
  myservo.write(80);
}


void moveRobot(int myLeftSpeed, int myRightSpeed)
{
  if (myLeftSpeed <= 0) {
    digitalWrite(myPins[1], 0);
    digitalWrite(myPins[2], 1);
  }
  else {
    digitalWrite(myPins[1], 1);
    digitalWrite(myPins[2], 0);
  }

  if (myRightSpeed <= 0) {
    digitalWrite(myPins[3], 0);
    digitalWrite(myPins[4], 1);
  }
  else {
    digitalWrite(myPins[3], 1);
    digitalWrite(myPins[4], 0);
  }

  analogWrite(myPins[0], abs(myLeftSpeed));
  analogWrite(myPins[5], abs(myRightSpeed));
}
