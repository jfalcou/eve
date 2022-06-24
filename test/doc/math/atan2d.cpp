#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, 4.0f, -2.0f };
  wide_ft qf = { 1.0f, -1.0f, 3.0f, -0.0f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                       = " << pf << '\n'
    << "<- qf                       = " << qf << '\n'
    << "-> atan2d(pf, qf)           = " << eve::atan2d(pf, qf) << '\n'
    
    ;

  float xf = 2.0f;
  float yf = 10.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf             = " << xf << '\n'
    << "-> atan2d(xf, yf) = " << eve::atan2d(xf, yf) << '\n';
  return 0;
}
