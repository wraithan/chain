#require "./has_read_pins.cpp" as HasReadPins
#require "./read_pin.cpp" as RP
#require "./onboard.cpp" as onboard

#export= Multiplexer
class Multiplexer : public HasReadPins {
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
    RP.ExternalReadPin* get_read_pin(const int pin);
};

void Multiplexer::select(const int pin) {
  onboard.digitalWrite(S0, (pin & 1) ? onboard.HIGH : onboard.LOW);
  onboard.digitalWrite(S1, (pin & 2) ? onboard.HIGH : onboard.LOW);
  onboard.digitalWrite(S2, (pin & 4) ? onboard.HIGH : onboard.LOW);
  onboard.digitalWrite(S3, (pin & 8) ? onboard.HIGH : onboard.LOW);
}

void Multiplexer::setup() {
  onboard.pinMode(S0, onboard.OUTPUT);
  onboard.pinMode(S1, onboard.OUTPUT);
  onboard.pinMode(S2, onboard.OUTPUT);
  onboard.pinMode(S3, onboard.OUTPUT);
  onboard.pinMode(data, onboard.OUTPUT);
}

void Multiplexer::write(const int pin, const int value) {
  select(pin);
  onboard.digitalWrite(data, value);
}

int Multiplexer::read(const int pin) {
  select(pin);
  return onboard.digitalRead(data);
}

RP.ExternalReadPin* Multiplexer::get_read_pin(const int pin) {
  return new RP.ExternalReadPin(this, pin);
}
