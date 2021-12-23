//#include <eve/function/nextafter.hpp>
#include <eve/module/ieee.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pi = {0.0f, 1.0f, 1.0f-eve::eps(eve::as<float>())/2, 1.0f};
  w_t qi = {-1.0f, -2.0f, 3.0f, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << std::setprecision(9) << '\n'
            << " <- pi                = " << pi << '\n'
            << " <- qi                = " << qi << '\n'
            << " -> nextafter(pi, qi) = " << eve::nextafter(pi, qi) << '\n';

  std::uint32_t xi = 3, yi = 7;

  std::cout << "---- scalar" << '\n'
            << " xi                   = " << xi << '\n'
            << " yi                   = " << yi << '\n'
            << " -> nextafter(xi, yi) = " << eve::nextafter(xi, yi) << '\n';
  return 0;
}
