#include <eve/function/logical.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {3.0f, -0.0f, -3.0f, 28.12f};
  wide_ft qf = {4.0f, -1.0f, -3.0f, 0.0f};
  std::cout << "---- simd" << '\n'
            << " <- pf =                      " << pf << '\n'
            << " <- qf =                      " << qf << '\n'
            << " -> eve::logical_or(pf, qf) = " << eve::logical_or(pf, qf) << '\n';

  float xf = 3.0f, yf = 4.0f;

  std::cout << "---- scalar" << '\n'
            << " xf =                         " << xf << '\n'
            << " yf =                         " << yf << '\n'
            << " -> eve::logical_or(xf, yf) = " << eve::logical_or(xf, yf) << '\n';
  return 0;
}
