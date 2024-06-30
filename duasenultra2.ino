const int trigbersama = 3;
const int echo1 = A1;
const int echo2 = A0;
const int ledmerah = 2;
const int ledijo = 7;
long duration1, distance1, duration2, distance2;



void setup() {
  // put your setup code here, to run once:
  pinMode(trigbersama, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(ledmerah, OUTPUT);
  pinMode(ledijo, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigbersama, LOW);
  delayMicroseconds(2);
  digitalWrite(trigbersama, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigbersama, LOW);

  duration1 = pulseIn(echo1, HIGH);
  distance1 = (duration1 * 0.0343)/2;

  if (distance1 < 10) {
    digitalWrite(ledmerah, HIGH);
  } else {
    digitalWrite(ledmerah, LOW);
  }
  Serial.println(distance1);

  delay(10);
  pulseIn(echo1, LOW);






  delay(10);






  digitalWrite(trigbersama, LOW);
  delayMicroseconds(2);
  digitalWrite(trigbersama, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigbersama, LOW);

  duration2 = pulseIn(echo2, HIGH);
  distance2 = (duration2 * 0.0343)/2;

  if (distance2 < 10) {
    digitalWrite(ledijo, HIGH);
  } else {
    digitalWrite(ledijo, LOW);
  }
  Serial.println(distance2);

  delay(10);  
  pulseIn(echo2, LOW);
}







