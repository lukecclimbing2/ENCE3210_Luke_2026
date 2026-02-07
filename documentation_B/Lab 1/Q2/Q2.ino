#include <Arduino.h>
#include <math.h>

double cosVals[361];

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  const double pi = acos(-1.0);

  for (int deg = 0; deg <= 360; deg++) {
    double rad = deg * (pi / 180.0);
    cosVals[deg] = cos(rad);
  }

  Serial.println("Task 2:");
  Serial.print("cos(0)   = ");   Serial.println(cosVals[0], 6);
  Serial.print("cos(60)  = ");   Serial.println(cosVals[60], 6);
  Serial.print("cos(180) = ");   Serial.println(cosVals[180], 6);
  Serial.print("cos(360) = ");   Serial.println(cosVals[360], 6);
}

void loop() {}
