#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pi = {0.0f,                                  1.0f, 1.0f-eve::eps(eve::as<float>())/2, 1.0f              };
  w_t qi = {eve::smallestposval(eve::as<float>()), 2.0f, 1.0f,                     eve::inf(eve::as<float>()) };

  std::cout << "---- simd" << std::setprecision(9) << '\n'
            << " <- pi                = " << pi << '\n'
            << " <- qi                = " << qi << '\n'
            << " -> nb_values(pi, qi) = " << eve::nb_values(pi, qi) << '\n';

  std::uint32_t xi = 3, yi = 7;

  std::cout << "---- scalar" << '\n'
            << " xi                   = " << xi << '\n'
            << " yi                   = " << yi << '\n'
            << " -> nb_values(xi, yi) = " << eve::nb_values(xi, yi) << '\n';
  return 0;
}
