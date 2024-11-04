#include <Servo.h>

#define PIN_IR    0         // IR sensor at Pin A0
#define PIN_LED   9
#define PIN_SERVO 10

#define _DUTY_MIN 0         // Servo 0 degree
#define _DUTY_NEU 1500      // Servo 90 degree
#define _DUTY_MAX 2000      // Servo 180 degree

#define _DIST_MIN  100.0    // Minimum distance 100mm (10cm)
#define _DIST_MAX  250.0    // Maximum distance 250mm (25cm)

#define EMA_ALPHA  0.1      // EMA filter coefficient
#define LOOP_INTERVAL 50    // Loop interval in ms

Servo myservo;
unsigned long last_loop_time;
float dist_ema = _DIST_MIN,duty=0;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(_DUTY_NEU);
  Serial.begin(1000000);
}

void loop() {
  if (millis() - last_loop_time < LOOP_INTERVAL) return;
  last_loop_time = millis();

  float a_value = analogRead(PIN_IR);
  float dist_raw = ((6762.0 / (a_value - 9.0)) - 4.0) * 10.0;

  if (dist_raw >= _DIST_MIN && dist_raw <= _DIST_MAX) {
    digitalWrite(PIN_LED, LOW);
    dist_ema = EMA_ALPHA * dist_raw + (1 - EMA_ALPHA) * dist_ema;
  } else {
    digitalWrite(PIN_LED, HIGH);
  }

  duty = _DUTY_MIN + ((dist_ema - _DIST_MIN) * (_DUTY_MAX - _DUTY_MIN)) / (_DIST_MAX - _DIST_MIN);
  myservo.writeMicroseconds(duty);

  Serial.print("IR: "); Serial.print(a_value);
  Serial.print(" Distance: "); Serial.print(dist_raw);
  Serial.print(" Filtered: "); Serial.print(dist_ema);
  Serial.print(" Servo: "); Serial.println(duty);
}
