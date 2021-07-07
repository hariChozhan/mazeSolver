#define sensor1 2
#define sensor2 3
#define sensor3 4
#define sensor4 5
#define sensor5 6
#define sensor6 7
void setup() {
  Serial.begin(9600);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
}

void loop() {
  Serial.println("***************");
  Serial.println(digitalRead(sensor1));
  Serial.println(digitalRead(sensor2));
  Serial.println(digitalRead(sensor3));
  Serial.println(digitalRead(sensor4));
  Serial.println(digitalRead(sensor5));
  Serial.println(digitalRead(sensor6));
  delay(500);
}
