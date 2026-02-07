#include <Arduino.h>
#include <limits.h>

struct ArrayWithAfter {
  int a[50];
  int after;   
};

ArrayWithAfter g = {
  { 5, 12, 7, 12, 40, 3, 40, 9, 1, 18,
    22, 22, 6, 19, 0, -5, 11, 8, 15, 14,
    2,  4, 10, 13, 16, 17, 21, 20, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
    35, 36, 37, 38, 39, 41, 42, 43, 44, 45 },
  0
};

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  int max1 = INT_MIN;
  int max2 = INT_MIN;

  for (int i = 0; i < 50; i++) {
    int v = g.a[i];

    if (v > max1) {
      max2 = max1;
      max1 = v;
    } else if (v < max1 && v > max2) {
      max2 = v;
    }
  }

  g.after = max2;

  Serial.println("Task 3:");
  Serial.print("Largest = ");       Serial.println(max1);
  Serial.print("Second largest = ");Serial.println(g.after);
}

void loop() {}
