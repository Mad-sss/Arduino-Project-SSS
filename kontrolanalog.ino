int led = 11;
int nyala = 1;
int kedap = 1;
const int pot = A1;


void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int kecepatan = analogRead(pot);
  kecepatan = map (kecepatan, 0, 1023, 1, 20);
  if (kedap == 1){
    nyala += 1;    
  }
  if (kedap == 0){
    nyala -= 1;
  }
  if (nyala == 150){
    kedap = 0;
  }
  if (nyala == 0){
    kedap = 1;
  }
  delay(kecepatan);  
  Serial.println(kecepatan);
  analogWrite(led, nyala);
}
