//#include <eve/function/significants.hpp>
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;
using wide_ft = eve::wide<double, eve::fixed<4>>;

int main()
{
  wide_it qi = {0, 1, 2, 4};
  wide_ft pf = {1.2345678901f, 1.2345678901f, 1.2345678901f, 1.2345678901f};

  std::cout << "---- simd" << std::setprecision(8) << '\n'
            << "<- pf            = " << pf << '\n'
            << "<- qi            = " << qi << '\n'
            << "-> significants(pf, qi) = " << eve::significants(pf, qi) << '\n';

  float xf = 2.34316;
  iT yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xf             = " << xf << '\n'
            << "<- yi             = " << yi << '\n'
            << "-> significants(xf, yi)  = " << eve::significants(xf, yi) << '\n';
  return 0;
}
