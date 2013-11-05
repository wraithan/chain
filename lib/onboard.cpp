#include <math.h>
#include <iostream>

#export HIGH
const int HIGH = 1;
#export LOW
const int LOW = 0;
#export OUTPUT
const int OUTPUT = 0;

#export pinMode
void pinMode(int pin, int value) {
  std::cout << "pin: " << pin << " mode " << value << std::endl;
}

#export digitalWrite
void digitalWrite(int pin, int value) {
  std::cout << "pin: " << pow(2, pin-1) << " value " << value << std::endl;
}

#export digitalRead
int digitalRead(int pin) {
  return pin;
}
