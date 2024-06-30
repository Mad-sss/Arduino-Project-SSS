int red = 11;
int green = 10;
int blue = 9;
const int ubahred = A0;
const int ubahgreen = A1;


void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(ubahred, INPUT);
  pinMode(ubahgreen, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int jadired = analogRead(ubahred);
  int jadigreen = analogRead(ubahgreen);
  jadired = map(jadired, 0, 1023, 0, 255);
  jadigreen = map(jadigreen, 0, 1023, 0, 255);
  analogWrite(red, jadired);
  analogWrite(green, jadigreen);
  analogWrite(blue, 100);
}
