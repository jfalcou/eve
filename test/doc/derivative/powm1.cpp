#include <eve/function/derivative/powm1.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, 3.5f};
  wide_ft qf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                        = " << pf << '\n'
    << "<- qf                        = " << qf << '\n'
    << "-> derivative(powm1)(pf, qf) = " << eve::derivative(eve::powm1)(pf, qf) << '\n';

  float xf = 3.0f;
  float yf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                        = " << xf << '\n'
    << "<- yf                        = " << yf << '\n'
    << "-> derivative(powm1)(xf, yf) = " << eve::derivative(eve::powm1)(xf, yf) << '\n';
  return 0;
}
