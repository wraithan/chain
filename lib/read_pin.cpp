#require "./has_read_pins.cpp" as HasReadPins
#require "./onboard.cpp" as onboard

class BaseReadPin {
  public:
    virtual ~BaseReadPin();
    virtual int read();
};

BaseReadPin::~BaseReadPin() {}
int BaseReadPin::read() {return -1;}

#export ExternalReadPin
class ExternalReadPin : public BaseReadPin {
    HasReadPins * const pin_holder;
    const int pin;
  public:
    ExternalReadPin(HasReadPins * const hrp, const int pin_number)
    : pin_holder(hrp)
    , pin(pin_number)
    {}
    int read();
};

int ExternalReadPin::read() {
  return pin_holder->read(pin);
}

#export OnBoardReadPin
class OnBoardReadPin : public BaseReadPin {
    const int pin;
  public:
    OnBoardReadPin(const int pin_number)
    : pin(pin_number)
    {}
    int read();
};

int OnBoardReadPin::read() {
  return onboard.digitalRead(pin);
}