//#include <eve/function/pedantic/prev.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/constant/bitincrement.hpp>
#include <eve/constant/eps.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-0.0f, 2.0f, eve::eps(eve::as<float>()), 0.0f};
  wide_it pi = {-1, 2, -3, -32};

  std::cout << "---- simd" << '\n'
            << "<- pf                  =" << std::setprecision(12) << pf << '\n'
            << "-> prev(pf)            =" << eve::prev(pf) << '\n'
            << "-> pedantic(prev)(pf) =" << eve::pedantic(eve::prev)(pf) << '\n'
            << "<- pi                  =" << pi << '\n'
            << "-> prev(pi)            =" << eve::prev(pi) << '\n';

  float        xf = 0.0f;
  std::int16_t xi = -3;

  std::cout << "---- scalar" << '\n'
            << "<- xf                  = " << xf << '\n'
            << "-> prev(xf, 3)         = " << eve::prev(xf, 3) << '\n'
            << "<- xi                  = " << xi << '\n'
            << "-> prev(xi)            = " << eve::prev(xi) << '\n';
  return 0;
}
