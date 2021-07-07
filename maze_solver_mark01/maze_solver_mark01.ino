const int leftIRsensor = 2;
const int centreIRsensor = 3;
const int rightIRsensor = 4;
const int leftMotor1 = 5;
const int leftMotor2 = 6;
const int rightMotor1 = 7;
const int rightMotor2 = 8;
const int leftMotorEn = 9;
const int rightMotorEn = 10;
int pwm = 150;
#define debug 1

void setup() {
  Serial.begin(9600);
  Serial.println("********Maze Follower*****");
  pinMode(leftIRsensor, INPUT);
  pinMode(centreIRsensor, INPUT);
  pinMode(rightIRsensor, INPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
}

void forward() {
  analogWrite(leftMotorEn, pwm);
  analogWrite(rightMotorEn, pwm);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}

void backward() {
  analogWrite(leftMotorEn, pwm);
  analogWrite(rightMotorEn, pwm);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
}

void left() {
  analogWrite(leftMotorEn, pwm);
  analogWrite(rightMotorEn, pwm);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}

void right() {
  analogWrite(leftMotorEn, pwm);
  analogWrite(rightMotorEn, pwm);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}

void rest() {
  analogWrite(leftMotorEn, pwm);
  analogWrite(rightMotorEn, pwm);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}

void loop() {
  int leftIRvalue = digitalRead(leftIRsensor);
  int centreIRvalue = digitalRead(centreIRsensor);
  int rightIRvalue = digitalRead(rightIRsensor);
  if (debug)
  {
    Serial.println("Left IR Value:");
    Serial.print(leftIRvalue);
    Serial.println("Right IR Value:");
    Serial.print(rightIRvalue);
    Serial.println("Centre IR Value:");
    Serial.print(centreIRvalue);
  }
  if (leftIRvalue == LOW && centreIRvalue == HIGH && rightIRvalue == LOW) {
    forward();
    if (debug) {
      Serial.println("FORWARD");
    }
  }
  if (leftIRvalue == HIGH && centreIRvalue == LOW && rightIRvalue == LOW) {
    left();
    if (debug) {
      Serial.println("LEFT");
    }
  }
  if (leftIRvalue == LOW && centreIRvalue == LOW && rightIRvalue == HIGH) {
    right();
    if (debug) {
      Serial.println("RIGHT");
    }
  }
  if (leftIRvalue == HIGH && centreIRvalue == LOW && rightIRvalue == HIGH) {
    left();
    if (debug) {
      Serial.println("LEFT");
    }
  }
  if (leftIRvalue == HIGH && centreIRvalue == HIGH && rightIRvalue == LOW) {
    left();
    if (debug) {
      Serial.println("LEFT");
    }
  }
  if (leftIRvalue == LOW && centreIRvalue == HIGH && rightIRvalue == HIGH) {
    forward();
    if (debug) {
      Serial.println("FORWARD");
    }
  }
  if (leftIRvalue == LOW && centreIRvalue == LOW && rightIRvalue == LOW) {
    backward();
    if (debug) {
      Serial.println("BACKWARD");
    }
  }
  if (leftIRvalue == HIGH && centreIRvalue == HIGH && rightIRvalue == HIGH) {
    left();
    if (debug) {
      Serial.println("LEFT");
    }
  }
  if (leftIRvalue == HIGH && centreIRvalue == LOW && rightIRvalue == HIGH) {
    rest();
    if (debug) {
      Serial.println("STOPPED");
    }
  }
}
