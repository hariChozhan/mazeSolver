int leftMotor1 = 7;
int leftMotor2 = 6;
int rightMotor1 = 5;
int rightMotor2 = 8;
char command = 'x';

void setup() {
  Serial.begin(115200);
  Serial.println("*******RC CAR*******");
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
}

void forward() {
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}
void backward() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
}
void left() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}
void right() {
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}

void stops() {
  Serial.println("Stop");
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}

void loop() {
  while (Serial.available() > 0) {
    command = Serial.read();
    Serial.println("Command : ");
    Serial.println(command);
    if (command == 'w') {
      Serial.println("forward");
      forward();
    }
    if (command == 'a') {
      Serial.println("left");
      left();
    }
    if (command == 'd') {
      Serial.println("right");
      right();
    }
    if (command == 's') {
      Serial.println("backward");
      backward();
    }
    if (command == 'x') {
      Serial.println("Stop");
      stops();
    }
  }
  delay(100);
}
