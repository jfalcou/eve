// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <cfenv>


int main()
{
  auto ttnmb = eve::twotonmb(eve::as<double>());
  eve::wide w0{1.0, 10.0, 25.0, 33.0}; //, 27.0, 13.0, 18.0, 4.0};
  eve::wide w1{0.0, 25.0, 33.0, 12.0}; //, 20.0, 18.0, 6.0, 10.0};
  w0+= ttnmb/2;
  w1+= ttnmb-100;
//  eve::wide<double, eve::fixed<8>> p(ttnmb-1);
   double p(ttnmb-1);
  std::cout << std::setprecision(20);
  std::cout << "<- p                    = " << p << "\n";
  std::cout << "<- w0                   = " << w0 << "\n";
  std::cout << "<- w1                   = " << w1 << "\n";
  std::cout << "-> add[mod = p](w0, w1) = " << eve::add[eve::mod = p](w0, w1) << "\n";
}
