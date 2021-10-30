#include <PS3BT.h>
#include <usbhub.h>
#include <Servo.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

Servo myservo;  // サーボを制御するサーボオブジェクトの作成
int pos = 0;    // サーボの初期角度

// Arduinoのピンモード設定
#define UR1 22
#define UR2 24
#define UL1 26
#define UL2 28
#define DR1 30
#define DR2 32
#define DL1 34
#define DL2 36
#define T1 38
#define T2 40
#define Se 42

void setup() {
  pinMode(UR1,OUTPUT);
  pinMode(UR2,OUTPUT);
  pinMode(UL1,OUTPUT);
  pinMode(UL2,OUTPUT);
  pinMode(DR1,OUTPUT);
  pinMode(DR2,OUTPUT);
  pinMode(DL1,OUTPUT);
  pinMode(DL2,OUTPUT);
  pinMode(T1,OUTPUT);
  pinMode(T2,OUTPUT);

  Serial.begin(115200);
  while (!Serial); // シリアルポートの接続
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));

  myservo.attach(Se);  // 使用するサーボのピンを定義
}

void loop() {
  Usb.Task();
  if (PS3.PS3Connected) {
    if (PS3.getButtonClick(PS)){
      // 機体とのペアリング
      Serial.print(F("\r\nPS"));
    }

    // △〇×□ボタンの操作
   else if (PS3.getButtonClick(TRIANGLE)){
     // 格納ゲートを開く 
     Serial.print(F("\r\nOpen"));
      myservo.write(90);
    }
   else if (PS3.getButtonClick(CIRCLE)){
      // 格納ゲートを開く
      Serial.print(F("\r\nClose"));
      myservo.write(0);
    }
   else if (PS3.getButtonPress(CROSS)){
      // 収集機構の回転（回収）
      Serial.print(F("\r\nRotationB"));
      digitalWrite(T1,HIGH);
      digitalWrite(T2,LOW);
    }
    else if (PS3.getButtonPress(SQUARE)){
      // 収集機構の回転（戻す）
      Serial.print(F("\r\nRotationA"));
      digitalWrite(T1,LOW);
      digitalWrite(T2,HIGH);
    }

    // 十字ボタンの操作
    else if (PS3.getButtonPress(UP)) {
      // 前に機体を移動
      Serial.print(F("\r\nUp"));
      digitalWrite(UR1,HIGH);
      digitalWrite(UR2,LOW);
      digitalWrite(UL1,HIGH);
      digitalWrite(UL2,LOW);
      digitalWrite(DR1,HIGH);
      digitalWrite(DR2,LOW);
      digitalWrite(DL1,HIGH);
      digitalWrite(DL2,LOW);
    }
    else  if (PS3.getButtonPress(RIGHT)) {
      // 右に機体を移動
      Serial.print(F("\r\nRight"));
      digitalWrite(UR1,LOW);
      digitalWrite(UR2,HIGH);
      digitalWrite(UL1,HIGH);
      digitalWrite(UL2,LOW);
      digitalWrite(DR1,HIGH);
      digitalWrite(DR2,LOW);
      digitalWrite(DL1,LOW);
      digitalWrite(DL2,HIGH);
    }
    else  if (PS3.getButtonPress(DOWN)) {
      // 後ろに機体を移動
      Serial.print(F("\r\nDown"));
      digitalWrite(UR1,LOW);
      digitalWrite(UR2,HIGH);
      digitalWrite(UL1,LOW);
      digitalWrite(UL2,HIGH);
      digitalWrite(DR1,LOW);
      digitalWrite(DR2,HIGH);
      digitalWrite(DL1,LOW);
      digitalWrite(DL2,HIGH);
    }
    else  if (PS3.getButtonPress(LEFT)) {
      // 左に機体を移動
      Serial.print(F("\r\nLeft"));
      digitalWrite(UR1,HIGH);
      digitalWrite(UR2,LOW);
      digitalWrite(UL1,LOW);
      digitalWrite(UL2,HIGH);
      digitalWrite(DR1,LOW);
      digitalWrite(DR2,HIGH);
      digitalWrite(DL1,HIGH);
      digitalWrite(DL2,LOW);

    // その他のボタンの操作
    }
    else if (PS3.getButtonPress(L1)){
      Serial.print(F("\r\nL1"));
    }else if (PS3.getButtonPress(L2)) {
      // 左に機体を旋回
      Serial.print(F("\r\nRotationL"));
      digitalWrite(UR1,HIGH);
      digitalWrite(UR2,LOW);
      digitalWrite(UL1,LOW);
      digitalWrite(UL2,HIGH);
      digitalWrite(DR1,HIGH);
      digitalWrite(DR2,LOW);
      digitalWrite(DL1,LOW);
      digitalWrite(DL2,HIGH);
    }
    else if (PS3.getButtonPress(L3)){
      Serial.print(F("\r\nL3"));
    }
    else if (PS3.getButtonPress(R1)){
      Serial.print(F("\r\nR1"));
    }
    else if (PS3.getButtonPress(R2)){
      // 右に機体を旋回
      Serial.print(F("\r\nRotationR"));
      digitalWrite(UR1,LOW);
      digitalWrite(UR2,HIGH);
      digitalWrite(UL1,HIGH);
      digitalWrite(UL2,LOW);
      digitalWrite(DR1,LOW);
      digitalWrite(DR2,HIGH);
      digitalWrite(DL1,HIGH);
      digitalWrite(DL2,LOW);
    }
    else if (PS3.getButtonPress(R3)){
      Serial.print(F("\r\nR3"));
    }
    else if (PS3.getButtonPress(SELECT)) {
      Serial.print(F("\r\nSelect"));
    }
    else if (PS3.getButtonPress(START)) {
      Serial.print(F("\r\nStart"));
    }
    else{
    // 何もボタンが押されていないときの処理
    Serial.print(F("\r"));    
    digitalWrite(UR1,LOW);
    digitalWrite(UR2,LOW);
    digitalWrite(UL1,LOW);
    digitalWrite(UL2,LOW);
    digitalWrite(DR1,LOW);
    digitalWrite(DR2,LOW);
    digitalWrite(DL1,LOW);
    digitalWrite(DL2,LOW);
    digitalWrite(T1,LOW);
    digitalWrite(T2,LOW);
    }
  }
}
