#include <eve/function/binarize.hpp>
#include <eve/wide.hpp>
#include <eve/constant/true.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                          = " << pf << '\n'
    << "-> eve::binarize(pf > 0.0f)    = " << eve::binarize(pf> 0.0f) << '\n'
    << "-> eve::binarize(pf > 0.0f, 3) = " << eve::binarize(pf> 0.0f,  3) << '\n';

  float xf = -1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                                     = " << xf << '\n'
    << "-> eve::binarize(eve::True<float>(), xf)  = " << eve::binarize(eve::True<float>(), xf) << '\n'
    << "-> eve::binarize(eve::False<float>(), xf) = " << eve::binarize(eve::False<float>(), xf) << '\n'        ;
  return 0;
}
