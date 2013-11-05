#include <Arduino.h>
#require "shift_register.cpp" as ShiftRegister

ShiftRegister sr(3, 4, 2);
uint8_t zeros[] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t all[] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  sr.setup();
  sr.writeAllPins(zeros);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void writeBoth(uint8_t pin) {
  uint8_t pin1 = pin;
  uint8_t pin2 = pin-16;
  all[0] = (pin1 & 1) ? HIGH : LOW;
  all[1] = (pin1 & 2) ? HIGH : LOW;
  all[2] = (pin1 & 4) ? HIGH : LOW;
  all[3] = (pin1 & 8) ? HIGH : LOW;
  all[4] = (pin2 & 1) ? HIGH : LOW;
  all[5] = (pin2 & 2) ? HIGH : LOW;
  all[6] = (pin2 & 4) ? HIGH : LOW;
  all[7] = (pin2 & 8) ? HIGH : LOW;
  sr.writeAllPins(all);
  if (pin < 16) {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  } else {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }
}

void loop() {
  for (uint8_t i = 0; i < 30; i++) {
    writeBoth(i);
    delay(10);
  }
  for (int8_t i = 28; i > 0; i--) {
    writeBoth(i);
    delay(10);
  }
}