//www.elegoo.com
//2016.12.08
#include "SR04.h" //超音波センサ用
#include <Servo.h> //サーボモータ用

//超音波センサ用
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

//サーボ用
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position


void setup() {
   Serial.begin(9600);
   delay(1000);
   myservo.attach(9);  // attaches the servo on pin 9 to the servo object

   //サーボの初期位置
   myservo.write(0);
    delay(100);
}

void loop() {
   a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");
   delay(500);


   //スマホ隠す
   if(a < 20){
     Serial.print(a);
     Serial.println("cm");    
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(100);
   //初期位置へ戻す（ヒステリシス付き）
   }else if(a > 30){
    myservo.write(0);
    delay(100);
   }
   
}
