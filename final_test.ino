#include <Servo.h>
int PinLF = 14;
int PinLB = 15;
int PinRF = 16;
int PinRB = 17;

int inPin =0;
int val=0;

int ultrainputpin = 9; // 超音波信號接收腳位
int ultraoutputpin = 8; // 超音波信號發射腳位
int PWMEN1 = 3;
int PWMEN2 = 5;

int LED1pin[] = {10, 11, 12};
int num = 0;


int speakerPin = 4;
char notes[] = "ededebdcaeabegbc";
unsigned long beats[] = {1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 2, 1, 1, 1, 2};
int length = sizeof(notes);
int tempo = 300;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(LED1pin[i], OUTPUT);
  }
  pinMode(inPin,INPUT);
  
  pinMode(PinLB, OUTPUT);
  pinMode(PinLF, OUTPUT);
  pinMode(PinRF, OUTPUT);
  pinMode(PinRB, OUTPUT);
  pinMode(PWMEN1, OUTPUT);
  pinMode(PWMEN2, OUTPUT);
  
  pinMode(speakerPin, OUTPUT);

  pinMode(ultrainputpin,INPUT);//定義超音波輸入腳位
  pinMode(ultraoutputpin,OUTPUT);//定義超音波輸出腳位
}

void loop() {
  val = digitalRead(inPin);//button狀態
  float distance = ultrasound_F();//讀前方距離
  if (distance < 60) {
   // light(40);
    Serial.println("後方、請前進");
    stopp(20); //停止
    if(val == LOW){
       music();
    }
   
  } else {
    light(100);
    advance(80);
  }
}

void music(){
     for (int i = 0; i < 1; i++) {
    if (notes[i] == ' ') {
      delay(beats[i]*tempo);
    } else {
     playNote(speakerPin, notes[i], beats[i]*tempo);
    }
    delay(tempo / 10);
  }
}
void stopp(int a ) {
  digitalWrite(PinRF, LOW);
  digitalWrite(PinRB, LOW);
  analogWrite(PWMEN1, 0);
  analogWrite(PinRB, 0);
  digitalWrite(PinLF, LOW);
  digitalWrite(PinLB, LOW);
  analogWrite(PWMEN2, 0);
  analogWrite(PinLB, 0);
  delay(a);
}
//前進
void advance(int a) {
  digitalWrite(PinRF, HIGH);
  digitalWrite(PinRB, LOW);
  analogWrite(PWMEN1, 110);
  analogWrite(PinRB, 0);
  digitalWrite(PinLF, HIGH);
  digitalWrite(PinLB, LOW);
  analogWrite(PWMEN2, 150);//l
  analogWrite(PinLB, 0);
  delay(a);
}

float ultrasound_F() { //測出距離
  digitalWrite(ultraoutputpin, LOW); //讓超聲波發射低電壓2
  delayMicroseconds(5);
  digitalWrite(ultraoutputpin, HIGH); //讓超聲波發射高電壓10
  delayMicroseconds(10);
  digitalWrite(ultraoutputpin, LOW); //維持超聲波發射低電壓

  float Fdistance = pulseIn(ultrainputpin, HIGH); // 讀取相差時間
  Fdistance = Fdistance / 5.8 / 10; //將時間轉為距離
  Serial.print("F distance"); //輸出距離
  Serial.println(Fdistance);//顯示距離 cm
  return Fdistance;
}
void light( int a) {
  for (int i = 0; i < 3; i++) {
    num = random(3);
    digitalWrite(LED1pin[num], HIGH);
    delay(a);
    digitalWrite(LED1pin[num], LOW);
    delay(a);
  }
  }
}
void light2( int a) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED1pin[i], LOW);
    delay(a);
  }
}

void playNote(int OutPin, char note, unsigned long duration) {
  char names[] = {'e', 'd', 'e', 'd', 'e', 'b', 'd', 'c', 'a', 'e', 'a', 'b', 'e', 'g', 'b', 'c'}; 
  int tones[] = {1318, 1175, 1318, 1175, 1318, 988, 1175, 1046, 880, 659, 880, 988, 659, 784, 988, 1046}; 
  for (int i = 0; i < 16; i++) {

    tone(OutPin, tones[i], duration);
    delay(duration);
    noTone(OutPin);

  }
}
