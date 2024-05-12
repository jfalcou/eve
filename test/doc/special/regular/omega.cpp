#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-10.0, -2.0, -0.5, 0.0, 0.2, 0.5, 10.0, 100.0};

  std::cout << "---- simd" << '\n'
            << "<- pf             = " << pf << '\n'
            << "-> eve::omega(pf) = " << eve::omega(pf) << '\n'
            ;

  float        xf = -0.2f;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> eve::omega(xf)  = " << eve::omega(xf)<< '\n';
  return 0;
}
