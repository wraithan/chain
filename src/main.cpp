#include <Arduino.h>
namespace _c425c960 {
#include "Arduino.h"


class ShiftRegister {
    uint8_t SRCLK, RCLK, SER;
    uint8_t * pins;
  public:
    ShiftRegister(uint8_t srclk, uint8_t rclk, uint8_t ser) {
      SRCLK = srclk;
      RCLK = rclk;
      SER = ser;
      pins = new uint8_t[8];
      for (uint8_t i = 0; i < 8; i++) {
         pins[i] = 0;
      }
    }
    void setup() {
      pinMode(SRCLK, OUTPUT);
      pinMode(RCLK, OUTPUT);
      pinMode(SER, OUTPUT);
    }
    void writePin(uint8_t pin, uint8_t value) {
      pins[pin] = value;
      writeAllPins(pins);
    }
    void writeAllPins(uint8_t output[]) {
      for (int8_t i = 7; i >= 0; i--) {
        pins[i] = output[i];
        digitalWrite(SER, pins[i]);
        digitalWrite(SRCLK, HIGH);
        digitalWrite(SER, LOW);
        digitalWrite(SRCLK, LOW);
      }
      digitalWrite(RCLK, HIGH);
      digitalWrite(RCLK, LOW);
    }
};

};


_c425c960::ShiftRegister sr(3, 4, 2);
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