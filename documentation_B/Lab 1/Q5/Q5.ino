#include <Arduino.h>

const int RED_PIN   = 9;
const int GREEN_PIN = 10;

const int arr[] = { 1,2,3,4,2,3,5,2,3,6,2,3,5 };
const int n = sizeof(arr) / sizeof(arr[0]);

const int pattern[3] = { 2, 3, 5 };

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);

  int count = 0;

  for (int i = 0; i <= n - 3; i++) {
    if (arr[i] == pattern[0] &&
        arr[i + 1] == pattern[1] &&
        arr[i + 2] == pattern[2]) {
      count++;
    }
  }

  if (count > 0) {
    digitalWrite(GREEN_PIN, HIGH);
  } else {
    digitalWrite(RED_PIN, HIGH);
  }

  Serial.println("Task 5:");
  Serial.print("Pattern occurrences = "); Serial.println(count);
}

void loop() {}
