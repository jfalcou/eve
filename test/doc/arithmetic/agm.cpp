//#include <eve/function/agm.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <iostream>


int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 3};
  w_t qi = {4, 1, 1, eve::inf(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << " <- pi              = " << pi << '\n'
            << " <- qi              = " << qi << '\n'
            << " -> agm(pi, qi) = " << eve::agm(pi, qi) << '\n';

  double xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi                 = " << xi << '\n'
            << " yi                 = " << yi << '\n'
            << " -> agm(xi, yi) = " << eve::agm(xi, yi) << '\n';

  return 0;
}
