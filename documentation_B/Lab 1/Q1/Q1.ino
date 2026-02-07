#include <Arduino.h>

int twiceSquare(int x) {
  long v = (long)x * (long)x;  
  v *= 2;
  return (int)v;
}

int results[512];

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  for (int i = 0; i <= 511; i++) {
    results[i] = twiceSquare(i);
  }

  Serial.println("Task 1:");
  Serial.print("results[0] = ");   Serial.println(results[0]);
  Serial.print("results[511] = "); Serial.println(results[511]);
}

void loop() {
  
}
