#include <eve/function/ulpdist.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pi = {0.0f,                         1.0f, 1.0f-eve::eps(eve::as<float>())/2, 1.0f              };
  w_t qi = {eve::smallestposval(eve::as<float>()), 2.0f, 1.0f,                     eve::inf(eve::as<float>()) };

  std::cout << "---- simd" << std::setprecision(9) << '\n'
            << " <- pi              = " << pi << '\n'
            << " <- qi              = " << qi << '\n'
            << " -> ulpdist(pi, qi) = " << eve::ulpdist(pi, qi) << '\n';

  std::uint32_t xi = 3, yi = 7;

  std::cout << "---- scalar" << '\n'
            << " xi                 = " << xi << '\n'
            << " yi                 = " << yi << '\n'
            << " -> ulpdist(xi, yi) = " << eve::ulpdist(xi, yi) << '\n';
  return 0;
}
