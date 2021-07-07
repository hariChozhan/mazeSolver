#define leftCenterSensor 4
#define leftNearSensor 3
#define leftFarSensor 2
#define rightCenterSensor 5
#define rightNearSensor 6
#define rightFarSensor 7
#define leftMotor1 7
#define leftMotor2 6
#define rightMotor1 5
#define rightMotor2 8
#define pwm 10

int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightCenterReading;
int rightNearReading;
int rightFarReading;

int leftNudge;
int replaystage;
int rightNudge;
#define leapTime 200

char path[30] = {};
int pathLength;
int readLength;

void setup() {
  Serial.begin(9600);
  Serial.println("*****Maze Follwer*****");
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
  pinMode(pwm, OUTPUT);
  analogWrite(pwm, 100);
  delay(1000);
}

void loop() {
  readSensors();
  if (leftFarReading == 0 && rightFarReading == 0 &&
      (leftCenterReading == 1 || rightCenterReading == 1) ) {
    straight();
  }
  else {
    leftHandWall();
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
}

void leftHandWall() {
  if ( leftFarReading == 0 && rightFarReading == 0) {
    Serial.println("Straight1");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    readSensors();
    if (leftFarReading == 0 || rightFarReading == 0) {
      done();
    }
    if (leftFarReading == 1 && rightFarReading == 1) {
      turnLeft();
    }
  }
  if (leftFarReading == 0) {
    Serial.println("Straight2");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    readSensors();
    if (leftFarReading == 1 && rightFarReading == 1) {
      turnLeft();
    }
    else {
      done();
    }
  }
  if (rightFarReading == 0) {
    Serial.println("Straight3");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(30);
    readSensors();
    if (leftFarReading == 0) {
      delay(leapTime - 30);
      readSensors();
      if (rightFarReading == 0 && leftFarReading == 0) {
        done();
      }
      else {
        turnLeft();
        return;
      }
    }
    delay(leapTime - 30);
    readSensors();
    if (leftFarReading == 1 && leftCenterReading == 1 &&
        rightCenterReading == 1 && rightFarReading == 1) {
      turnRight();
      return;
    }
    path[pathLength] = 'S';
    pathLength++;
    if (path[pathLength - 2] == 'B') {
      shortPath();
    }
    straight();
  }
  readSensors();
  if (leftFarReading == 1 && leftCenterReading == 1 && rightCenterReading == 1
      && rightFarReading == 1 && leftNearReading == 1 && rightNearReading == 1) {
    turnAround();
  }
}

void done() {
  Serial.println("Done1");
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  replaystage = 1;
  path[pathLength] = 'D';
  pathLength++;
  delay(500);
  replay();
}

void turnLeft() {
  while (digitalRead(rightCenterSensor) == 0 || digitalRead(leftCenterSensor) == 0) {
    Serial.println("Fast right1");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(20);
    Serial.println("Done2");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  }
  while (digitalRead(rightCenterSensor) == 1) {
    Serial.println("Fast right2");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(20);
    Serial.println("Done3");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  }
  if (replaystage == 0) {
    path[pathLength] = 'L';
    pathLength++;
    if (path[pathLength - 2] == 'B') {
      shortPath();
    }
  }
}
void turnRight() {
  while (digitalRead(rightCenterSensor) == 0) {
    Serial.println("Fast left1");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(20);
    Serial.println("Done4");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  }
  while (digitalRead(rightCenterSensor) == 1) {
    Serial.println("Fast left2");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(20);
    Serial.println("Done5");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  }
  while (digitalRead(leftCenterSensor) == 1) {
    Serial.println("Fast left3");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(20);
    Serial.println("Done6");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(10);
  }
  if (replaystage == 0) {
    path[pathLength] = 'R';
    Serial.println("r");
    pathLength++;
    Serial.print("Path length: ");
    Serial.println(pathLength);
    if (path[pathLength - 2] == 'B') {
      Serial.println("shortening path");
      shortPath();
    }
  }
}

void straight() {
  if ( digitalRead(leftCenterSensor) == 0) {
    Serial.println("Straight4");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(30);
    Serial.println("Left1");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(2);
    return;
  }
  if (digitalRead(rightCenterSensor) == 0) {
    Serial.println("Straight5");
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(30);
    Serial.println("Right1");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
    return;
  }
  Serial.println("Straight6");
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  delay(500);
  Serial.println("Stop1");
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  delay(100);
}

void turnAround() {
  Serial.println("Straight7");
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  delay(150);
  while (digitalRead(leftCenterSensor) == 1) {
    Serial.println("Fast Left3");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
    Serial.println("Stop2");
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
  path[pathLength] = 'B';
  pathLength++;
  straight();
}

void shortPath() {
  int shortDone = 0;
  if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'R') {
    pathLength -= 3;
    path[pathLength] = 'B';
    //Serial.println("test1");
    shortDone = 1;
  }
  if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'S' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'R';
    //Serial.println("test2");
    shortDone = 1;
  }
  if (path[pathLength - 3] == 'R' && path[pathLength - 1] == 'L' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'B';
    //Serial.println("test3");
    shortDone = 1;
  }
  if (path[pathLength - 3] == 'S' && path[pathLength - 1] == 'L' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'R';
    //Serial.println("test4");
    shortDone = 1;
  }
  if (path[pathLength - 3] == 'S' && path[pathLength - 1] == 'S' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'B';
    //Serial.println("test5");
    shortDone = 1;
  }
  if (path[pathLength - 3] == 'L' && path[pathLength - 1] == 'L' && shortDone == 0) {
    pathLength -= 3;
    path[pathLength] = 'S';
    //Serial.println("test6");
    shortDone = 1;
  }
  path[pathLength + 1] = 'D';
  path[pathLength + 2] = 'D';
  pathLength++;
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
  printPath();
}

void printPath() {
  Serial.println("+++++++++++++++++");
  int x;
  while (x <= pathLength) {
    Serial.println(path[x]);
    x++;
  }
  Serial.println("+++++++++++++++++");
}

void replay() {
  readSensors();
  if (leftFarReading == 1 && rightFarReading == 1) {
    straight();
  }
  else {
    if (path[readLength] == 'D') {
      Serial.println("Straight8");
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      delay(100);
      Serial.println("Stop3");
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
      //      endMotion();
    }
    if (path[readLength] == 'L') {
      Serial.println("Straight9");
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      delay(leapTime);
      turnLeft();
    }
    if (path[readLength] == 'R') {
      Serial.println("Straight10");
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      delay(leapTime);
      turnRight();
    }
    if (path[readLength] == 'S') {
      Serial.println("Straight11");
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      delay(leapTime);
      straight();
    }
    readLength++;
  }
  replay();
}

//void endMotion() {
//  digitalWrite(led, LOW);
//  delay(500);
//  digitalWrite(led, HIGH);
//  delay(200);
//  digitalWrite(led, LOW);
//  delay(200);
//  digitalWrite(led, HIGH);
//  delay(500);
//  endMotion();
//}
