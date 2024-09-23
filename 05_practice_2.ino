int ledPin = 7; // LED 핀 번호 (예: 13번 핀)

void setup() {
  pinMode(ledPin, OUTPUT); // LED 핀을 출력 모드로 설정
}

void loop() {
  digitalWrite(ledPin, LOW); // LED 끄기
  delay(1000); // 1초 대기

  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH); // LED 켜기
    delay(100); // 0.1초 대기
    digitalWrite(ledPin, LOW); // LED 끄기
    delay(100); // 0.1초 대기
  }

  while(1){}
}
