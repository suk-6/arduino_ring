#include <SoftwareSerial.h>

#define BT_RXD 8
#define BT_TXD 7
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  bluetooth.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  if (bluetooth.available())
  {
    // 문자열을 읽고 저장
    String readData = bluetooth.readStringUntil('\n');
    Serial.println(readData); // 읽은 데이터를 시리얼 모니터에 출력

    int separatorIndex = readData.indexOf('/');
    if (separatorIndex != -1)
    {
      // '/' 문자를 찾으면 분할
      String positionStr = readData.substring(0, separatorIndex);
      String powerStr = readData.substring(separatorIndex + 1);

      int position = positionStr.toInt();
      int power = powerStr.toInt();

      if (position == 0)
      {
        Serial.println(power);
        analogWrite(4, power);
        delay(500);
        analogWrite(4, 0);
      }
      else if (position == 1)
      {
        analogWrite(5, power);
        delay(500);
        analogWrite(5, 0);
      }
      else if (position == 2)
      {
        analogWrite(4, power);
        analogWrite(5, power);
        delay(500);
        analogWrite(4, 0);
        analogWrite(5, 0);
      }
    }
  }

  if (Serial.available())
  {
    bluetooth.write(Serial.read());
  }
}
