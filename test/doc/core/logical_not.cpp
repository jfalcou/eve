#include <eve/function/logical.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {3.0f, 0.0f, -3.0f, -0.0};

  std::cout << "---- simd" << '\n'
            << " <- pf =                  " << pf << '\n'
            << " -> eve::logical_not(pf) = " << eve::logical_not(pf) << '\n';

  std::int32_t xf = 3, yf = 0;

  std::cout << "---- scalar" << '\n'
            << " xf =                     " << xf << '\n'
            << " yf =                     " << yf << '\n'
            << " -> eve::logical_not(xf) = " << eve::logical_not(xf) << '\n'
            << " -> eve::logical_not(yf) = " << eve::logical_not(yf) << '\n';
  return 0;
}
