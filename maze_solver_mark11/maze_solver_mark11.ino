#define leftCenterSensor 3
#define leftNearSensor 4
#define leftFarSensor 5
#define rightCenterSensor 2
#define rightNearSensor 1
#define rightFarSensor 0
int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightCenterReading;
int rightNearReading;
int rightFarReading;
#define leftMotor1 7
#define leftMotor2 6
#define rightMotor1 5
#define rightMotor2 8
//#define leftPwm 9
//#define rightPwm 10
int leftNudge;
int replaystage;
int rightNudge;
#define leapTime 500
#define debug 1
char path[30] = {};
int pathLength;
int readLength;
void setup() {
  pinMode(leftCenterSensor, INPUT);
  pinMode(leftNearSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(rightCenterSensor, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
//  pinMode(leftPwm, OUTPUT);
//  pinMode(rightPwm, OUTPUT);
//  analogWrite(leftPwm,255);
//  analogWrite(rightPwm,255);
  Serial.begin(9600);
  Serial.println("***********Maze Solver Mark 11***********");
  delay(1000);
}
void loop() {
  readSensors();
  if (leftFarReading < 200 && rightFarReading < 200 &&
      (leftCenterReading > 200 || rightCenterReading > 200) ) {
    //    Serial.println("Straight Line");
    straight();
  }
  else {
    //    Serial.println("Left Hand wall");
    leftHandWall();
    //    digitalWrite(leftMotor1, LOW);
    //    digitalWrite(leftMotor2, LOW);
    //    digitalWrite(rightMotor1, LOW);
    //    digitalWrite(rightMotor2, LOW);
  }
  delay(500);
}
void readSensors() {
  leftCenterReading = analogRead(leftCenterSensor);
  leftNearReading = analogRead(leftNearSensor);
  leftFarReading = analogRead(leftFarSensor);
  rightCenterReading = analogRead(rightCenterSensor);
  rightNearReading = analogRead(rightNearSensor);
  rightFarReading = analogRead(rightFarSensor);
  Serial.print(leftFarReading);
  Serial.print(leftNearReading);
  Serial.print(leftCenterReading);
  Serial.print(rightCenterReading);
  Serial.print(rightNearReading);
  Serial.print(rightFarReading);
}

void straight() {
  if ( digitalRead(leftCenterSensor) < 200) {
    Serial.println("Straight2");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(10);
    Serial.println("Right1");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(20);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    return;
  }
  if (digitalRead(rightCenterSensor) < 200) {
    Serial.println("Straight3");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(10);
    Serial.print("Left1");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(20);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    return;
  }
  Serial.println("Straight1");
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  delay(50);
  Serial.println("Stop");
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  delay(10);
}
void leftHandWall() {
  if ( leftFarReading > 200 && rightFarReading > 200) {
    Serial.println("Straight4");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    readSensors();
    //    if (leftFarReading > 200 || rightFarReading > 200) {
    //      done();
    //    }
    //    if (leftFarReading <200 && rightFarReading <200) {
    turnLeft();
    //  }
  }
}

void turnLeft() {
  while (digitalRead(rightCenterSensor) > 200 || digitalRead(leftCenterSensor) > 200) {
    Serial.println("Fast Left1");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(20);
    Serial.println("Stop");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  }
  while (digitalRead(rightCenterSensor) < 200) {
    Serial.println("Fast left2");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(20);
    Serial.println("Stop");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  }
  //  if (replaystage == 0) {
  //    path[pathLength] = 'L';
  //    pathLength++;
  //    if (path[pathLength - 2] == 'B') {
  //      shortPath();
  //    }
  //  }
}
void done() {
  Serial.println("Done");
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  //    replaystage = 1;
  //    path[pathLength] = 'D';
  //    pathLength++;
  //    delay(500);
  //    replay();
}
