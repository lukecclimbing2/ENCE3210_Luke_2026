#include <Arduino.h>

const int BTN1_PIN = 2;   
const int BTN2_PIN = 3;   

const int RED_PIN   = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN  = 11;

volatile long btn1Count = 0;
volatile long btn2Count = 0;

volatile unsigned long lastIsrUs1 = 0;
volatile unsigned long lastIsrUs2 = 0;
const unsigned long DEBOUNCE_US = 30000; // 30 ms

void setLEDs(bool r, bool g, bool b) {
  digitalWrite(RED_PIN, r ? HIGH : LOW);
  digitalWrite(GREEN_PIN, g ? HIGH : LOW);
  digitalWrite(BLUE_PIN, b ? HIGH : LOW);
}

void ISR_btn1() {
  unsigned long now = micros();
  if (now - lastIsrUs1 >= DEBOUNCE_US) {
    btn1Count++;
    lastIsrUs1 = now;
  }
}

void ISR_btn2() {
  unsigned long now = micros();
  if (now - lastIsrUs2 >= DEBOUNCE_US) {
    btn2Count++;
    lastIsrUs2 = now;
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(BTN2_PIN, INPUT_PULLUP);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  setLEDs(false, false, false);

  attachInterrupt(digitalPinToInterrupt(BTN1_PIN), ISR_btn1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN2_PIN), ISR_btn2, FALLING);

  Serial.println("Lab2 P1: Press BTN1 and BTN2. Watch counts and LED result.");
}

void loop() {
  long c1, c2;
  noInterrupts();
  c1 = btn1Count;
  c2 = btn2Count;
  interrupts();

  if (c1 > c2)      setLEDs(true,  false, false); // red
  else if (c1 < c2) setLEDs(false, true,  false); // green
  else              setLEDs(false, false, true ); // blue

  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 250) {
    lastPrint = millis();
    Serial.print("BTN1=");
    Serial.print(c1);
    Serial.print(" BTN2=");
    Serial.println(c2);
  }
}
