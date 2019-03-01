#include <eve/function/logical.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft =  eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 3.0f, -0.0f, -3.0f, 5.0f };
  wide_ft qf = { 4.0f, -1.0f, -3.0f, 0.0f };
  std::cout
    <<  "---- simd" << '\n'
    << " <- pf =                      " << pf << '\n'
    << " <- qf =                      " << qf << '\n'
    << " -> eve::logical_and(pf, qf) = " << eve::logical_and(pf, qf) << '\n';

  float xf = 3.0f, yf = 4.0f;

  std::cout
    << "---- scalar"  << '\n'
    << " xf =                         " << xf << '\n'
    << " yf =                         " << yf << '\n'
    << " -> eve::logical_and(xf, yf) = " << eve::logical_and(xf, yf) << '\n';
  return 0;
}
