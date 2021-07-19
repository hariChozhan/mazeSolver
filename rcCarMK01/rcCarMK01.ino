#include <SoftwareSerial.h>
SoftwareSerial btt(2, 3); // (Rx,Tx)

int leftMotor1 = 7;
int leftMotor2 = 6;
int rightMotor1 = 5;
int rightMotor2 = 8;
char command = 'x';

void setup() {
  Serial.begin(9600);
  btt.begin(115200);
  Serial.println("*******RC CAR*******");
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}

void forward() {
  Serial.println("Forward");
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  delay(50);
}
void backward() {
  Serial.println("backward");
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  delay(50);
}
void left() {
  Serial.println("left");
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  delay(50);
}
void right() {
  Serial.println("right");
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  delay(50);
}

void stops() {
  Serial.println("Stop");
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  delay(10);
}

void loop() {
  while (btt.available() > 0) {
    command = btt.read();
    Serial.println("Command : ");
    Serial.println(command);
    if (command == 'w') {
      forward();
    }
    if (command == 'a') {
      left();
    }
    if (command == 'd') {
      right();
    }
    if (command == 's') {
      backward();
    }
    if (command == 'x') {
      stops();
    }
    stops();
  }
//  stops();
//  delay(500);
}
