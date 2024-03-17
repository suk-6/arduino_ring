#include <SoftwareSerial.h>

#define LEFT 8
#define RIGHT 9
#define CENTER 10

#define BT_RXD 6
#define BT_TXD 7
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  bluetooth.begin(9600);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(CENTER, OUTPUT);
}

void loop() {
  if (bluetooth.available()) {
    // 문자열을 읽고 저장
    String readData = bluetooth.readStringUntil('\n');

    int separatorIndex = readData.indexOf('/');
    if (separatorIndex != -1) {
      // '/' 문자를 찾으면 분할
      String positionStr = readData.substring(0, separatorIndex);
      String powerStr = readData.substring(separatorIndex + 1);

      int position = positionStr.toInt();
      int power = powerStr.toInt();
      Serial.println(position);
      Serial.println(power);

      switch(position){
        case 0:
          analogWrite(CENTER, power);
          analogWrite(LEFT, power);
          break;
        case 1:
          analogWrite(CENTER, power);
          analogWrite(RIGHT, power);
          break;
        case 2:
          analogWrite(LEFT, power);
          break;
        case 3:
          analogWrite(RIGHT, power);
          break;
      }

      delay(500);
      analogWrite(LEFT, 0);
      analogWrite(RIGHT, 0);
      analogWrite(CENTER, 0);
    }
  }

  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
}
