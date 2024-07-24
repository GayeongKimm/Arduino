#include <SoftwareSerial.h> // 소프트웨어 시리얼 라이브러리 불러오기

int piezo = 12;

int buttonState = 0;
const int buttonPin = 3;
const int ledPin = 2;

//dc모터
int speed1 = 9;
int In1 = 8;
int In2 = 7;

int speed2 = 4;
int In3 = 6;
int In4 = 5;

SoftwareSerial BTSerial(10, 11); // 소프트웨어 시리얼 객체를 11(TX), 12번(RX)으로 생성

void setup() {
  Serial.begin(9600); // 시리얼 통신을 개시, 속도는 9600
  BTSerial.begin(9600); // 소프트웨어 시리얼 통신 개시, 속도는 9600

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  pinMode(speed1, OUTPUT);1
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(speed2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
}

void loop() {
  if (Serial.available()) { // 시리얼 통신으로 문자가 들어오면
    BTSerial.write(Serial.read()); // 블루투스 시리얼 통신으로 발송
  }
  
  if (BTSerial.available()) { // 블루투스 시리얼 통신으로 문자가 들어오면
    char c = BTSerial.read();
    Serial.write(c); // 시리얼 창에 표시(시리얼 통신으로 출력)

    if (c == 'F') forward1();
    else if (c == 'B') backward1();
    else if (c == 'L') turnleft();
    else if (c == 'R') turnright();
    else if (c == '0') stopall();
  }

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    stopall();
  }
}

void forward1() {
  digitalWrite(In1, LOW); // 첫 번째 모터 반시계 방향
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW); // 두 번째 모터 반시계 방향
  digitalWrite(In4, HIGH);
  analogWrite(speed1, 100); // 첫 번째 모터 속도
  analogWrite(speed2, 100); // 두 번째 모터 속도
}

void backward1() {
  digitalWrite(In1, HIGH); // 첫 번째 모터 시계 방향
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH); // 두 번째 모터 시계 방향
  digitalWrite(In4, LOW);
  analogWrite(speed1, 100); // 첫 번째 모터 속도
  analogWrite(speed2, 100); // 두 번째 모터 속도
}

void turnleft() {
  digitalWrite(In1, LOW); // 첫 번째 모터 반시계 방향
  digitalWrite(In2, HIGH);
  digitalWrite(In3, HIGH); // 두 번째 모터 시계 방향
  digitalWrite(In4, LOW);
  analogWrite(speed1, 100); // 첫 번째 모터 속도
  analogWrite(speed2, 100); // 두 번째 모터 속도
}

void turnright() {
  digitalWrite(In1, HIGH); // 첫 번째 모터 시계 방향
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW); // 두 번째 모터 반시계 방향
  digitalWrite(In4, HIGH);
  analogWrite(speed1, 100); // 첫 번째 모터 속도
  analogWrite(speed2, 100); // 두 번째 모터 속도
}

void stopall() {
  digitalWrite(In1, LOW); // 모든 모터 정지
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  analogWrite(speed1, 0); // 첫 번째 모터 속도 0
  analogWrite(speed2, 0); // 두 번째 모터 속도 0
}
