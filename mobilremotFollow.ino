
 
// Define Input Connections
#define CH1 A0
// #define CH2 A1
#define CH3 A2
// #define CH4 9
#define CH5 A1
// #define CH6 11
const int trig1 = 3;
const int trig2 = 5;
const int echo1 = A5;
const int echo2 = A4;
 
// Integers to represent values from sticks and pots
int ch1Value;
// int ch2Value;
int ch3Value;
// int ch4Value; 
int ch5Value;

// pin untuk kendali mobil
int kananMasuk = 6;
int kananKeluar = 9;
int kiriMasuk = 10;
int kiriKeluar = 11;
int kondisiBelok;
int kondisiMaju;
int kondisifollow;
int samaJarak;
 
// Boolean to represent switch value
bool ch6Value;
 
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
 
void setup(){
  // Set up serial monitor
  Serial.begin(9600);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  // pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  // pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  // pinMode(CH6, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(kananMasuk, OUTPUT);
  pinMode(kananKeluar, OUTPUT);
  pinMode(kiriMasuk, OUTPUT);
  pinMode(kiriKeluar, OUTPUT);
}
 
 
void loop() {

  // Get values for each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  // ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  // ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = readChannel(CH5, -100, 100, 0);
  // ch6Value = readSwitch(CH6, false);
  


  // Menentukan jarak dua sensor
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  int durasiKanan = pulseIn(echo1, HIGH);
  int jarakKanan = (durasiKanan * 0.0343)/2;

  delay(10);

  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  int durasiDepan = pulseIn(echo2, HIGH);
  int jarakKiri = (durasiDepan * 0.0343)/2;


  // Print to Serial Monitor
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" | Ch5: ");
  Serial.print(ch5Value);
  Serial.print(" | Jarak Kanan: ");
  Serial.print(jarakKanan);
  Serial.print(" | Jarak Kiri: ");
  Serial.println(jarakKiri);



  // MOBIL FOLLOW ATAU RC
  if (ch5Value <= 0){
    kondisifollow = 1;
  } else {
    kondisifollow = 0;
  }



  // MOBIL FOLLOW
  if (kondisifollow == 1){
    int bedaJarak = jarakKanan - jarakKiri;
    int bedaJarak2 = jarakKiri - jarakKanan;
    if(bedaJarak >= 4 || bedaJarak2 >= 4){
      samaJarak = 1;
    } else {
      samaJarak = 0;
    }    
    // MOBIL FOLLOW DIAM     
    if(jarakKanan < 50 && jarakKiri < 50 && bedaJarak < 4 && bedaJarak2 < 4){
      analogWrite(kananMasuk, 0);
      analogWrite(kananKeluar, 0);
      analogWrite(kiriMasuk, 0);
      analogWrite(kiriKeluar, 0);
    }
    // MOBIL FOLLOW MAJU
    if(jarakKanan > 50 && jarakKanan < 100 && jarakKiri > 50 && jarakKiri < 100 && bedaJarak < 4 && bedaJarak2 < 4){
      analogWrite(kananMasuk, 100);
      analogWrite(kananKeluar, 0);
      analogWrite(kiriMasuk, 100);
      analogWrite(kiriKeluar, 0);
    }
    // MOBIL MENYAMAKAN JARAK
    if(samaJarak == 1){
      if(jarakKanan > 100 && jarakKiri > 100){
        analogWrite(kananMasuk, 0);
        analogWrite(kananKeluar, 0);
        analogWrite(kiriMasuk, 0);
        analogWrite(kiriKeluar, 0);
      }
      if(bedaJarak >= 4){
        analogWrite(kananMasuk, 90);
        analogWrite(kananKeluar, 0);
        analogWrite(kiriMasuk, 100+(bedaJarak*4));
        analogWrite(kiriKeluar, 0);     
      }
      if(bedaJarak2 >= 4){
        analogWrite(kananMasuk, 100+(bedaJarak2*4));
        analogWrite(kananKeluar, 0);
        analogWrite(kiriMasuk, 90);
        analogWrite(kiriKeluar, 0);         
      }
    }
    // MOBIL MENCARI FOLLOW
    if(jarakKanan >= 100 && jarakKiri >= 100){
      analogWrite(kananMasuk, 100);
      analogWrite(kananKeluar, 0);
      analogWrite(kiriMasuk, 0);
      analogWrite(kiriKeluar, 100);
    }
  }



  // MOBIL BELOK ATAU LURUS ATAU BERHENTI
  if (ch1Value > 8 || ch1Value < -8){
    kondisiBelok = 1;
  } else {
    kondisiBelok = 0;
  }
  if (ch3Value > 8 || ch3Value < -8){
    kondisiMaju = 1;
  } else {
    kondisiMaju = 0;
  }


  // MOBIL MAJU ATAU MUNDUR ATAU BERHENTI
  if (kondisiBelok == 0 && kondisiMaju == 1 && kondisifollow == 0) {
    if (ch3Value <= 0){
      int kecepatanMobil = (ch3Value*-1) + 100;
      analogWrite(kananMasuk, 0);
      analogWrite(kananKeluar, kecepatanMobil);
      analogWrite(kiriMasuk, 0);
      analogWrite(kiriKeluar, kecepatanMobil);
    }
    if (ch3Value > 0){
      int kecepatanMobil = ch3Value + 100;
      analogWrite(kananMasuk, kecepatanMobil);
      analogWrite(kananKeluar, 0);
      analogWrite(kiriMasuk, kecepatanMobil);
      analogWrite(kiriKeluar, 0);
    }
  }
  if (kondisiMaju == 0 && kondisifollow == 0){
    analogWrite(kananMasuk, 0);
    analogWrite(kananKeluar, 0);
    analogWrite(kiriMasuk, 0);
    analogWrite(kiriKeluar, 0);
  }


  // mobil sedang belok
  if (kondisiBelok == 1 && kondisiMaju == 1 && kondisifollow == 0) {
    // lagi mundur
    if(ch3Value <= 0){
      if (ch1Value <= 0){
        int tajamBelokan = (ch1Value*-1) + 100;
        analogWrite(kananMasuk, 0);
        analogWrite(kananKeluar, tajamBelokan);
        analogWrite(kiriMasuk, 0);
        analogWrite(kiriKeluar, 100);
      }
      if (ch1Value > 0) {
        int tajamBelokan = ch1Value + 100;
        analogWrite(kananMasuk, 0);
        analogWrite(kananKeluar, 100);
        analogWrite(kiriMasuk, 0);
        analogWrite(kiriKeluar, tajamBelokan);
      }      
    }
    // lagi maju
    if(ch3Value > 0 && kondisifollow == 0){
      if (ch1Value <= 0){
        int tajamBelokan = (ch1Value*-1) + 100;
        analogWrite(kananMasuk, tajamBelokan);
        analogWrite(kananKeluar, 0);
        analogWrite(kiriMasuk, 100);
        analogWrite(kiriKeluar, 0);
      }
      if (ch1Value > 0) {
        int tajamBelokan = ch1Value + 100;
        analogWrite(kananMasuk, 100);
        analogWrite(kananKeluar, 0);
        analogWrite(kiriMasuk, tajamBelokan);
        analogWrite(kiriKeluar, 0);
      } 
    }
  }
  delay(20);
}
