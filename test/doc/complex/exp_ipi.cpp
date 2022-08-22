#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, 0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                        = " << pf << '\n'
    << "-> exp_ipi(pf)               = " << eve::exp_ipi(pf) << '\n'
    << "-> exp_ipi(-i(as<wide_ft())) = " << eve::exp_ipi(-eve::i(eve::as<wide_ft>()))  << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf               = " << xf << '\n'
    << "-> eve::exp_ipi(xf) = " << eve::exp_ipi(xf) << '\n';
  return 0;
}
