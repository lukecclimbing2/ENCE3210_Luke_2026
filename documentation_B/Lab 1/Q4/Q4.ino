#include <Arduino.h>

const int RED_PIN   = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN  = 11;

const char arr[] = { 'A','R','B','G','R','X','B','B','G' };
const int n = sizeof(arr) / sizeof(arr[0]);

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  int rCount = 0, gCount = 0, bCount = 0;

  for (int i = 0; i < n; i++) {
    if (arr[i] == 'R') rCount++;
    else if (arr[i] == 'G') gCount++;
    else if (arr[i] == 'B') bCount++;
  }

  if (rCount > 0) digitalWrite(RED_PIN, HIGH);
  if (gCount > 0) digitalWrite(GREEN_PIN, HIGH);
  if (bCount > 0) digitalWrite(BLUE_PIN, HIGH);

  Serial.println("Task 4:");
  Serial.print("R count = "); Serial.println(rCount);
  Serial.print("G count = "); Serial.println(gCount);
  Serial.print("B count = "); Serial.println(bCount);
}

void loop() {}
