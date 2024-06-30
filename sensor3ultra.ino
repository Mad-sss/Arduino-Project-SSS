const int trigerPertama = A3;
const int trigerKedua = 5;
const int trigerKetiga = 6; 


const int echoPertama = A0;
const int echoKedua = A1;
const int echoKetiga = A2;


const int ledmerah = 8;
const int ledijo = 12;
const int ledkuning = 13; 


long durasiKanan;
long jarakKanan;
long durasiDepan;
long jarakDepan;
long durasiKiri;
long jarakKiri;




void setup() {
  // put your setup code here, to run once:
  pinMode(trigerPertama, OUTPUT);
  pinMode(trigerKedua, OUTPUT);
  pinMode(trigerKetiga, OUTPUT);


  pinMode(echoPertama, INPUT);
  pinMode(echoKedua, INPUT);
  pinMode(echoKetiga, INPUT);


  pinMode(ledijo, OUTPUT);
  pinMode(ledmerah, OUTPUT);
  pinMode(ledkuning, OUTPUT);


  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigerPertama, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPertama, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerPertama, LOW);
  durasiKanan = pulseIn(echoPertama, HIGH);
  jarakKanan = (durasiKanan * 0.0343)/2;
  Serial.print(jarakKanan);
  Serial.print(" ");
  if (jarakKanan < 10) {
    digitalWrite(ledijo, HIGH);
  } else {
    digitalWrite(ledijo, LOW);
  }


  delay(10);


  digitalWrite(trigerKedua, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerKedua, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerKedua, LOW);
  durasiDepan = pulseIn(echoKedua, HIGH);
  jarakDepan = (durasiDepan * 0.0343)/2;
  Serial.print(jarakDepan);
  Serial.print(" ");
  if(jarakDepan < 10) {
    digitalWrite(ledmerah, HIGH);
  } else {
    digitalWrite(ledmerah, LOW);
  }


  delay(10);


  digitalWrite(trigerKetiga, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerKetiga, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerKetiga, LOW);
  durasiKiri = pulseIn(echoKetiga, HIGH);
  jarakKiri = (durasiKiri * 0.0343)/2;
  Serial.print(jarakKiri);
  Serial.println("");
  if (jarakKiri < 10) {
    digitalWrite(ledkuning, HIGH);
  } else {
    digitalWrite(ledkuning, LOW);
  }


  delay(10);
}
