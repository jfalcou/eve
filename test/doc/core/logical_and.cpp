#include <eve/function/logical.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::logical<eve::wide<float, eve::fixed<4>>>;

int main()
{
  wide_ft pf = {true,true,false,false};
  wide_ft qf = {true,false,true,false};
  std::cout << "---- simd" << '\n'
            << " <- pf                       = " << pf << '\n'
            << " <- qf                       = " << qf << '\n'
            << " -> eve::logical_and(pf, qf) = " << eve::logical_and(pf, qf) << '\n';

  eve::logical<float> xf = false, yf = true;

  std::cout << "---- scalar" << '\n'
            << " xf                          = " << xf << '\n'
            << " yf                          = " << yf << '\n'
            << " -> eve::logical_and(xf, yf) = " << eve::logical_and(xf, yf) << '\n';
  return 0;
}
