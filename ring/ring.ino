#include <SoftwareSerial.h>

#define BT_RXD 7
#define BT_TXD 8
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop(){
  if (bluetooth.available()){
    char readString = bluetooth.read();
    Serial.write(readString);

    if (readString == '0') {
      analogWrite(4, 255);
      delay(500);
      analogWrite(4, 0);
    }

    if (readString == '1') {
      analogWrite(5, 255);
      delay(500);
      analogWrite(5, 0);
    }

    if (readString == '2') {
      analogWrite(4, 255);
      analogWrite(5, 255);
      delay(500);
      analogWrite(4, 0);
      analogWrite(5, 0);
    }
  }
}