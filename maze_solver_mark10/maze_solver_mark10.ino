#define leftCenterSensor 4
#define leftNearSensor 3
#define leftFarSensor 2
#define rightCenterSensor 9
#define rightNearSensor 10
#define rightFarSensor 11
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
int leftNudge;
int replaystage;
int rightNudge;
#define leapTime 200
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
  Serial.begin(9600);
  Serial.println("***********Maze Solver Mark 10***********");
  delay(1000);
}
void loop() {
  readSensors();
  if (leftFarReading == 0 && rightFarReading == 0 &&
      (leftCenterReading == 1 || rightCenterReading == 1) ) {
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
  leftCenterReading = digitalRead(leftCenterSensor);
  leftNearReading = digitalRead(leftNearSensor);
  leftFarReading = digitalRead(leftFarSensor);
  rightCenterReading = digitalRead(rightCenterSensor);
  rightNearReading = digitalRead(rightNearSensor);
  rightFarReading = digitalRead(rightFarSensor);
  Serial.print(leftFarReading);
  Serial.print(leftNearReading);
  Serial.print(leftCenterReading);
  Serial.print(rightCenterReading);
  Serial.print(rightNearReading);
  Serial.print(rightFarReading);
}

void straight() {
  if ( digitalRead(leftCenterSensor) == 0) {
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
  if (digitalRead(rightCenterSensor) == 0) {
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
  if ( leftFarReading == 1 && rightFarReading == 1) {
    Serial.println("Straight4");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    readSensors();
    //    if (leftFarReading == 1 || rightFarReading == 1) {
    //      done();
    //    }
    //    if (leftFarReading == 0 && rightFarReading == 0) {
    turnLeft();
    //  }
  }
}

void turnLeft() {
  while (digitalRead(rightCenterSensor) == 1 || digitalRead(leftCenterSensor) == 1) {
    Serial.println("Fast Left1");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(50);
    Serial.println("Stop");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(100);
  }
  while (digitalRead(rightCenterSensor) == 0) {
    Serial.println("Fast left2");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(50);
    Serial.println("Stop");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(100);
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
