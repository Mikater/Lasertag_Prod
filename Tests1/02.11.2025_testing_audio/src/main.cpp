#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  pinMode(11, OUTPUT);
}

void loop() {
  digitalWrite(11, LOW);
  sleep(1000);
  digitalWrite(11, HIGH);
  sleep(1000);
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}