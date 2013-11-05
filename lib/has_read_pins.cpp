#export= HasReadPins
class HasReadPins {
  public:
    virtual int read(int pin);
    virtual ~HasReadPins();
};

int HasReadPins::read(int pin) {return pin*0;}
HasReadPins::~HasReadPins() {}