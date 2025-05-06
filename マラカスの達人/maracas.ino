//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


//ボールスイッチ用
const int ledPin = 13;//the led attach to
int preState = LOW; //スイッチの前の状態

//当たり判定用
int count = 0; //何マス進んだか
int judge[] = {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0};
//何マスにドンがあるか

//ブザー用
int buzzer = 3;//the pin of the active buzzer

void setup() {
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Hello, World!");
  //lcd.setCursor(1,1);
  //lcd.print("|aa");

  //ボールスイッチ用
  pinMode(ledPin,OUTPUT);//initialize the ledPin as an output
  pinMode(2,INPUT);
  digitalWrite(2, HIGH);


}

//電光掲示板用
//参考サイト：https://s51517765.hatenadiary.jp/entry/2020/08/31/073000
const int delayTime = 400; //ms
String displayString = "";
const int displayWidth = 15;



void printLCD(String string0, String string1) {

  //上の段はセンタリング
  //if (string0.length() < displayWidth - 1) {
  //  String tmp = "";
  //  for (int i = 0; i < (displayWidth - string0.length()) / 2; i++) {
  //    tmp += ' ';
  //  }
  //  string0 = tmp + string0;
  //}
  //下の段の文字列生成
  for (int i = 0; i < displayWidth + string1.length(); i++) {
    lcd.clear();
    displayString = "";
    if (i < 16) {
      for (int j = 0; j < displayWidth - i + 1; j++) {
        displayString += ' ';
      }
      for (int k = 0; k < i; k++) {
        displayString += string1[k];
      }
    }
    else  if (i < string1.length()) {
      displayString = "";
      for (int k = 0; k <=  displayWidth; k++) {
        displayString += string1[i - displayWidth + k];
      }
    }
    else {
      displayString = "";
      for (int k = 0; i - displayWidth + k < string1.length(); k++) {
        displayString += string1[i - displayWidth + k];
      }
    }
    //printする
    lcd.setCursor(0, 0);
    lcd.print(string0);
    lcd.setCursor(0, 1);
    lcd.print(displayString);
    delay(delayTime);



    //ボールスイッチ用
    int digitalVal = digitalRead(2);

    //マラカスが振られた事を検知
    if(HIGH == digitalVal){
      if(preState == LOW){     

        //ブザーを鳴らす
         //output an frequency
          unsigned char x;
         for(x=0;x<80;x++)
         {
          digitalWrite(buzzer,HIGH);
          delay(1);//wait for 1ms
          digitalWrite(buzzer,LOW);
          delay(1);//wait for 1ms
          }

            
        //タイミング判定
        int timing;
        //timing = (count - 15) % 16;
        //timing = 15 - count % 16;
        //timing = (count % 16 + 1) % 16;
        timing = count - 14;
        //Serial.print(count);
        //Serial.print("\n");
        //Serial.print(timing);
        //Serial.print("\n");

          if(judge[timing] == 1){
            Serial.print("Good!!\n");
            lcd.setCursor(0,0);
            lcd.print(" |GOOD!");
            delay(100);
          }else{
            Serial.print("Bad\n");
            lcd.setCursor(0,0);
            lcd.print(" |BAD");
            delay(100);
          }
      }
      preState = HIGH;
    }else{
      preState = LOW;
    }
    lcd.setCursor(0,0);
    lcd.print("|");
    count = count + 1;      
  }
}



void loop() {
  String string0 = " |";
  //String string1 = "O     O     O    O O O O O ";
  String string1 = "O       O       O       O   O   O       O       O       O   O   ";
  //String string1 = "OXOXOXXXOXOXOXXX";
  printLCD(string0, string1);
}
