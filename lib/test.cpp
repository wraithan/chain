#include <iostream>
#require "./multiplexer.cpp" as Multiplexer
#require "./read_pin.cpp" as RP

int main() {
  Multiplexer m(1,2,3,4,5);
  std::cout << m.read(1) << std::endl;

  RP.ExternalReadPin *rp;
  rp = m.get_read_pin(4);
  std::cout << rp->read() << std::endl;
  delete rp;
}
