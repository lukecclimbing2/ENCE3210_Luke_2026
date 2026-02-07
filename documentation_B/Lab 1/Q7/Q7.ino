#include <Arduino.h>

const int RED_PIN   = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN  = 11;

const int BTN_SELECT = 2;  
const int BTN_RUN    = 3;  

int A[10] = { 1,2,3,4,5,6,7,8,9,10 };
int B[10] = { 10,9,8,7,6,5,4,3,2,1 };
int C[10]; 

int opMode = 0;

struct Debounce {
  bool lastReading = HIGH;
  bool stableState = HIGH;
  unsigned long lastDebounceTime = 0;
};

const unsigned long DEBOUNCE_MS = 35;

Debounce dbSel, dbRun;

void setLEDs(bool r, bool g, bool b) {
  digitalWrite(RED_PIN,   r ? HIGH : LOW);
  digitalWrite(GREEN_PIN, g ? HIGH : LOW);
  digitalWrite(BLUE_PIN,  b ? HIGH : LOW);
}

void allOff() { setLEDs(false, false, false); }
void allOn()  { setLEDs(true,  true,  true ); }

bool pressedEdge(int pin, Debounce &db) {
  bool reading = digitalRead(pin);

  if (reading != db.lastReading) {
    db.lastDebounceTime = millis();
    db.lastReading = reading;
  }

  if ((millis() - db.lastDebounceTime) > DEBOUNCE_MS) {
    if (reading != db.stableState) {
      db.stableState = reading;
      if (db.stableState == LOW) return true;
    }
  }
  return false;
}

void showSelectedOpLED() {
  if (opMode == 1) setLEDs(true,  false, false); // add
  else if (opMode == 2) setLEDs(false, true,  false); // sub
  else if (opMode == 3) setLEDs(false, false, true ); // mul
  else allOff();
}

void computeAndStore() {
  allOff();

  for (int i = 0; i < 10; i++) {
    if (opMode == 1)      C[i] = A[i] + B[i];
    else if (opMode == 2) C[i] = A[i] - B[i];
    else if (opMode == 3) C[i] = A[i] * B[i];
    else                  C[i] = 0; 
  }

  Serial.println("Results C[10]:");
  for (int i = 0; i < 10; i++) {
    Serial.print("C[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(C[i]);
  }

  allOn(); 
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_RUN, INPUT_PULLUP);

  allOff();
  Serial.println("Task 7 ready. Press SELECT to choose op, RUN to compute.");
}

void loop() {
  if (pressedEdge(BTN_SELECT, dbSel)) {
    opMode++;
    if (opMode > 3) opMode = 1;

    Serial.print("Selected opMode = ");
    Serial.println(opMode);

    showSelectedOpLED();
  }

  if (pressedEdge(BTN_RUN, dbRun)) {
    Serial.println("RUN pressed.");
    computeAndStore();
  }
}
