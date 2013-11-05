#include <iostream>
namespace _30885503 {
namespace _4c25a7ea {

class HasReadPins {
  public:
    virtual int read(int pin);
    virtual ~HasReadPins();
};

int HasReadPins::read(int pin) {return pin*0;}
HasReadPins::~HasReadPins() {}
};

namespace _ea8ceeee {

namespace _848fe56 {
#include <math.h>
#include <iostream>

const int HIGH = 1;
const int LOW = 0;
const int OUTPUT = 0;

void pinMode(int pin, int value) {
  std::cout << "pin: " << pin << " mode " << value << std::endl;
}

void digitalWrite(int pin, int value) {
  std::cout << "pin: " << pow(2, pin-1) << " value " << value << std::endl;
}

int digitalRead(int pin) {
  return pin;
}

};


class BaseReadPin {
  public:
    virtual ~BaseReadPin();
    virtual int read();
};

BaseReadPin::~BaseReadPin() {}
int BaseReadPin::read() {return -1;}

class ExternalReadPin : public BaseReadPin {
    _30885503::_4c25a7ea::HasReadPins * const pin_holder;
    const int pin;
  public:
    ExternalReadPin(_30885503::_4c25a7ea::HasReadPins * const hrp, const int pin_number)
    : pin_holder(hrp)
    , pin(pin_number)
    {}
    int read();
};

int ExternalReadPin::read() {
  return pin_holder->read(pin);
}

class OnBoardReadPin : public BaseReadPin {
    const int pin;
  public:
    OnBoardReadPin(const int pin_number)
    : pin(pin_number)
    {}
    int read();
};

int OnBoardReadPin::read() {
  return _848fe56::digitalRead(pin);
}
};




class Multiplexer : public _4c25a7ea::HasReadPins {
    const int S0, S1, S2, S3, data;
    void select(int pin);
  public:
    Multiplexer(const int s0, const int s1, const int s2, const int s3, const int dpin) 
    : S0(s0)
    , S1(s1)
    , S2(s2)
    , S3(s3)
    , data(dpin)
    {}
    ~Multiplexer() {}
    void setup();
    void write(const int pin, const int value);
    int read(const int pin);
    _ea8ceeee::ExternalReadPin* get_read_pin(const int pin);
};

void Multiplexer::select(const int pin) {
  _30885503::_ea8ceeee::_848fe56::digitalWrite(S0, (pin & 1) ? _30885503::_ea8ceeee::_848fe56::HIGH : _30885503::_ea8ceeee::_848fe56::LOW);
  _30885503::_ea8ceeee::_848fe56::digitalWrite(S1, (pin & 2) ? _30885503::_ea8ceeee::_848fe56::HIGH : _30885503::_ea8ceeee::_848fe56::LOW);
  _30885503::_ea8ceeee::_848fe56::digitalWrite(S2, (pin & 4) ? _30885503::_ea8ceeee::_848fe56::HIGH : _30885503::_ea8ceeee::_848fe56::LOW);
  _30885503::_ea8ceeee::_848fe56::digitalWrite(S3, (pin & 8) ? _30885503::_ea8ceeee::_848fe56::HIGH : _30885503::_ea8ceeee::_848fe56::LOW);
}

void Multiplexer::setup() {
  _30885503::_ea8ceeee::_848fe56::pinMode(S0, _30885503::_ea8ceeee::_848fe56::OUTPUT);
  _30885503::_ea8ceeee::_848fe56::pinMode(S1, _30885503::_ea8ceeee::_848fe56::OUTPUT);
  _30885503::_ea8ceeee::_848fe56::pinMode(S2, _30885503::_ea8ceeee::_848fe56::OUTPUT);
  _30885503::_ea8ceeee::_848fe56::pinMode(S3, _30885503::_ea8ceeee::_848fe56::OUTPUT);
  _30885503::_ea8ceeee::_848fe56::pinMode(data, _30885503::_ea8ceeee::_848fe56::OUTPUT);
}

void Multiplexer::write(const int pin, const int value) {
  select(pin);
  _30885503::_ea8ceeee::_848fe56::digitalWrite(data, value);
}

int Multiplexer::read(const int pin) {
  select(pin);
  return _30885503::_ea8ceeee::_848fe56::digitalRead(data);
}

_ea8ceeee::ExternalReadPin* Multiplexer::get_read_pin(const int pin) {
  return new _ea8ceeee::ExternalReadPin(this, pin);
}

};



int main() {
  _30885503::Multiplexer m(1,2,3,4,5);
  std::cout << m.read(1) << std::endl;

  _30885503::_ea8ceeee::ExternalReadPin *rp;
  rp = m.get_read_pin(4);
  std::cout << rp->read() << std::endl;
  delete rp;
}
