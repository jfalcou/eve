#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, eve::pi(eve::as(1.0f))};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                      = " << pf << '\n'
    << "-> exp_i(pf)               = " << eve::exp_i(pf) << '\n'
    << "-> exp_i(-i(as<wide_ft())) = " << eve::exp_i(-eve::i(eve::as<wide_ft>()))  << '\n';

  float xf = (eve::pio_2(eve::as(1.0f)));

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf            = " << xf << '\n'
    << "-> eve::exp_i(xf) = " << eve::exp_i(xf) << '\n';
  return 0;
}
