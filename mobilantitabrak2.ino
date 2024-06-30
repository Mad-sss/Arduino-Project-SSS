const int trigerDepan = A3;
const int trigerKanan = 5;
const int trigerKiri = 3; 


const int echoDepan = A0;
const int echoKanan = A1;
const int echoKiri = A2;


const int kananMasuk = 6;
const int kananKeluar = 9;
const int kiriMasuk = 11;
const int kiriKeluar = 10;


long durasiKanan;
long jarakKanan;
long durasiDepan;
long jarakDepan;
long durasiKiri;
long jarakKiri;


int waktu = 0;
int mundur1, mundur2, perubahanPosisi, kondisiMundur;



void setup() {
  // put your setup code here, to run once:
  pinMode(trigerDepan, OUTPUT);
  pinMode(trigerKanan, OUTPUT);
  pinMode(trigerKiri, OUTPUT);


  pinMode(echoDepan, INPUT);
  pinMode(echoKanan, INPUT);
  pinMode(echoKiri, INPUT);


  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(kananMasuk, 110);
  analogWrite(kananKeluar, 0);
  analogWrite(kiriMasuk, 111);
  analogWrite(kiriKeluar, 0);



  digitalWrite(trigerKanan, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerKanan, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerKanan, LOW);
  durasiKanan = pulseIn(echoKanan, HIGH);
  jarakKanan = (durasiKanan * 0.0343)/2;
  Serial.print(jarakKanan);
  Serial.print(" ");



  delay(10);



  digitalWrite(trigerDepan, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerDepan, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerDepan, LOW);
  durasiDepan = pulseIn(echoDepan, HIGH);
  jarakDepan = (durasiDepan * 0.0343)/2;
  Serial.print(jarakDepan);
  Serial.print(" ");



  delay(10);



  digitalWrite(trigerKiri, LOW);
  delayMicroseconds(2);
  digitalWrite(trigerKiri, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerKiri, LOW);
  durasiKiri = pulseIn(echoKiri, HIGH);
  jarakKiri = (durasiKiri * 0.0343)/2;
  Serial.print(jarakKiri);
  Serial.print(" ");
  Serial.print(waktu);
  Serial.println("");
  


  delay(10);



  // COMMAND UNTUK MOBIL
  // COMMAND UNTUK MOBIL
  // COMMAND UNTUK MOBIL
  // COMMAND UNTUK MOBIL
  // COMMAND UNTUK MOBIL


    
  if (jarakDepan > 2 && jarakDepan < 25 && jarakKanan > 15 && jarakKiri > 15) {
    // BELOKKANAN
    if (jarakKanan < jarakKiri) {
      analogWrite(kananMasuk, 140);
      analogWrite(kiriKeluar, 90);
      analogWrite(kiriMasuk, 0);
      delay(500);
      analogWrite(kananMasuk, 100); 
      analogWrite(kiriMasuk, 100);
      analogWrite(kiriKeluar, 0);
    }
    // BELOKKIRI
    if (jarakKanan > jarakKiri){
      analogWrite(kiriMasuk, 140);
      analogWrite(kananMasuk, 0);   
      analogWrite(kananKeluar, 90);
      delay(500);
      analogWrite(kiriMasuk, 100);
      analogWrite(kananMasuk, 100);
      analogWrite(kananKeluar, 0);
    }
  
  }
  if(jarakDepan > 2 && jarakDepan < 25 && jarakKanan < 15 && jarakKiri < 15) {
    // MUNDUR
    analogWrite(kananMasuk, 0);
    analogWrite(kananKeluar, 100);
    analogWrite(kiriMasuk, 0);
    analogWrite(kiriKeluar, 100);
    delay(1000);
    if(jarakKanan > jarakKiri){
      // HADAPKANAN
      analogWrite(kiriMasuk, 100);
      analogWrite(kiriKeluar, 0);
      delay(400);
      analogWrite(kananMasuk, 100);
      analogWrite(kananKeluar, 0);
    }
    if(jarakKanan < jarakKiri) {
      // HADAPKIRI
      analogWrite(kananMasuk, 100);
      analogWrite(kananKeluar, 0);
      delay(400);
      analogWrite(kiriMasuk, 100);
      analogWrite(kiriKeluar, 0);
    }
  }
  if(jarakDepan > 2 && jarakDepan < 25 && jarakKanan < 15 && jarakKiri > 15) {
    analogWrite(kananMasuk, 140);
    analogWrite(kiriMasuk, 0);
    analogWrite(kiriKeluar, 90);
    delay(300);
    analogWrite(kananMasuk, 100);
    analogWrite(kiriMasuk, 100);
    analogWrite(kiriKeluar, 0);
  }
  if(jarakDepan > 2 && jarakDepan < 25 && jarakKiri < 15 && jarakKanan > 15) {
    analogWrite(kiriMasuk, 140);
    analogWrite(kananMasuk, 0);
    analogWrite(kananKeluar, 90);
    delay(300);
    analogWrite(kananMasuk, 100);
    analogWrite(kiriMasuk, 100);
    analogWrite(kananKeluar, 0);
  }
  if(jarakDepan == 2) {
    analogWrite(kananMasuk, 0);
    analogWrite(kananKeluar, 140);
    analogWrite(kiriMasuk, 0);
    analogWrite(kiriKeluar, 140);
    delay(1300);
  }
  if(jarakKanan < 10 && jarakKiri > 10) {
    analogWrite(kiriMasuk, 95);
    delay(100);
  }
  if(jarakKiri < 10 && jarakKanan > 10){
    analogWrite(kananMasuk, 95);
    delay(100);
  }
  if(jarakKiri < 15 && jarakKanan < 15){
    if(jarakKiri < jarakKanan){
      analogWrite(jarakKanan, 90);
      delay(100);
    }
    if(jarakKiri > jarakKanan){
      analogWrite(jarakKiri, 90);
      delay(100);
    }
  }
}











