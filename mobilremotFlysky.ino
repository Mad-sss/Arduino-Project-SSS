/*
  Arduino FS-I6X Demo
  fsi6x-arduino-uno.ino
  Read output ports from FS-IA6B receiver module
  Display values on Serial Monitor
  
  Channel functions by Ricardo Paiva - https://gist.github.com/werneckpaiva/
  
  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/
 
// Define Input Connections
#define CH1 A0
#define CH2 A1
#define CH3 A2
// #define CH4 9
// #define CH5 10
// #define CH6 11
 
// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
// int ch4Value; 
// int ch5Value;

// pin untuk kendali mobil
int kananMasuk = 6;
int kananKeluar = 9;
int kiriMasuk = 10;
int kiriKeluar = 11;
int kondisiBelok;
int kondisiMaju;
 
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
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  // pinMode(CH4, INPUT);
  // pinMode(CH5, INPUT);
  // pinMode(CH6, INPUT);
  pinMode(kananMasuk, OUTPUT);
  pinMode(kananKeluar, OUTPUT);
  pinMode(kiriMasuk, OUTPUT);
  pinMode(kiriKeluar, OUTPUT);
}
 
 
void loop() {


  // kondisi awal mobil
  // analogWrite(kananMasuk, 100);
  // analogWrite(kananKeluar, 0);
  // analogWrite(kiriMasuk, 100);
  // analogWrite(kiriKeluar, 0);
  

  // Get values for each channel
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, -100);
  // ch4Value = readChannel(CH4, -100, 100, 0);
  // ch5Value = readChannel(CH5, -100, 100, 0);
  // ch6Value = readSwitch(CH6, false);
  

  // Print to Serial Monitor
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" | Ch3: ");
  Serial.println(ch3Value);
  // Serial.print(" | Ch4: ");
  // Serial.print(ch4Value);
  // Serial.print(" | Ch5: ");
  // Serial.print(ch5Value);
  // Serial.print(" | Ch6: ");
  // Serial.println(ch6Value);


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
  if (kondisiBelok == 0 && kondisiMaju == 1) {
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
  if (kondisiMaju == 0){
    analogWrite(kananMasuk, 0);
    analogWrite(kananKeluar, 0);
    analogWrite(kiriMasuk, 0);
    analogWrite(kiriKeluar, 0);
  }


  // mobil sedang belok
  if (kondisiBelok == 1 && kondisiMaju == 1) {
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
    if(ch3Value > 0){
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
  delay(50);
}
