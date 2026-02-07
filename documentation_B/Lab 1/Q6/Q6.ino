#include <Arduino.h>

const int RED_PIN   = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN  = 11;

const int BUTTON_PIN = 2; 

const unsigned long STEP_MS = 300; 

bool running = false;

bool lastReading = HIGH;
bool stableState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_MS = 35;

unsigned long lastStepTime = 0;
int stepIndex = 0;

void setLEDs(bool r, bool g, bool b) {
  digitalWrite(RED_PIN,   r ? HIGH : LOW);
  digitalWrite(GREEN_PIN, g ? HIGH : LOW);
  digitalWrite(BLUE_PIN,  b ? HIGH : LOW);
}

void allOff() {
  setLEDs(false, false, false);
}

void doStep(int idx) {
  switch (idx) {
    case 0: setLEDs(true,  false, false); break; 
    case 1: setLEDs(true,  true,  false); break; 
    case 2: setLEDs(true,  true,  true ); break; 
    case 3: setLEDs(false, true,  true ); break; 
    case 4: setLEDs(false, false, true ); break; 
    case 5: setLEDs(true,  false, true ); break; 
  }
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  allOff();
}

void loop() {
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastReading) {
    lastDebounceTime = millis();
    lastReading = reading;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    if (reading != stableState) {
      stableState = reading;

      if (stableState == LOW) {
        running = !running;

        if (!running) {
          allOff();
        } else {
          stepIndex = 0;
          lastStepTime = 0; 
        }
      }
    }
  }

  if (running) {
    unsigned long now = millis();
    if (now - lastStepTime >= STEP_MS) {
      lastStepTime = now;
      doStep(stepIndex);
      stepIndex = (stepIndex + 1) % 6;
    }
  }
}
