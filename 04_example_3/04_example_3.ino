#define PIN_LED 13
unsigned int count;
int toggle; // toggle은 논리값으로 사용되므로 int로 변경

void setup() {
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(115200); // Initialize serial port
    while (!Serial) {
        ; // wait for serial port to connect.
    }
    Serial.println("Hello World!");
    count = 0;
    toggle = 0;
    digitalWrite(PIN_LED, toggle); // turn off LED.
}

void loop() {
    Serial.println(++count);
    toggle = toggle_state(toggle); // toggle LED value.
    digitalWrite(PIN_LED, toggle); // update LED status.
    delay(1000); // wait for 1,000 milliseconds
}

int toggle_state(int toggle) {
    return !toggle; // toggle 값을 반전시킴
}
