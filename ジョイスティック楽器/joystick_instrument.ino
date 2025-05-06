//www.elegoo.com
//2016.12.09

//ブザー用
#include "pitches.h"

// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output

//ブザー設定
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 100;  // 500 miliseconds
int x;
int y;

//ジョイスティック設定
int gosa = 50; //誤差範囲
int do1[] = {0,512};
int re[] = {0,0};
int mi[] = {512,0};
int fa[] = {1024,0};
int so[] = {1024,512};
int la[] = {1024,1024};
int si[] = {512,1024};
int do2[] = {0,1024};

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  x = analogRead(X_pin);
  y = analogRead(Y_pin);
  //delay(500);

  //ブザー設定
  //ド1
  if(x >= do1[0]-gosa && x < do1[0]+gosa && y >= do1[1]-gosa && y < do1[1]+gosa){
    tone(8, melody[0], duration);
    Serial.print("do");
    Serial.print("\n\n");
  //レ
  }else if(x >= re[0]-gosa && x < re[0]+gosa && y >= re[1]-gosa && y < re[1]+gosa){
    tone(8, melody[1], duration);
    Serial.print("re");
    Serial.print("\n\n");
  //ミ
  }else if(x >= mi[0]-gosa && x < mi[0]+gosa && y >= mi[1]-gosa && y < mi[1]+gosa){
    tone(8, melody[2], duration);
    Serial.print("mi");
    Serial.print("\n\n");
  //ファ
  }else if(x >= fa[0]-gosa && x < fa[0]+gosa && y >= fa[1]-gosa && y < fa[1]+gosa){
    tone(8, melody[3], duration);
    Serial.print("fa");
    Serial.print("\n\n");
  //ソ
  }else if(x >= so[0]-gosa && x < so[0]+gosa && y >= so[1]-gosa && y < so[1]+gosa){
    tone(8, melody[4], duration);
    Serial.print("so");
    Serial.print("\n\n");
  //ラ
  }else if(x >= la[0]-gosa && x < la[0]+gosa && y >= la[1]-gosa && y < la[1]+gosa){
    tone(8, melody[5], duration);
    Serial.print("la");
    Serial.print("\n\n");
  //シ
  }else if(x >= si[0]-gosa && x < si[0]+gosa && y >= si[1]-gosa && y < si[1]+gosa){
    tone(8, melody[6], duration);
    Serial.print("si");
    Serial.print("\n\n");
  //ド2
  }else if(x >= do2[0]-gosa && x < do2[0]+gosa && y >= do2[1]-gosa && y < do2[1]+gosa){
    tone(8, melody[7], duration);
    Serial.print("do2");
    Serial.print("\n\n");
  }
}
