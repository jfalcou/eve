#include <eve/function/binarize_not.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                              = " << pf << '\n'
    << "-> eve::binarize_not(pf > 0.0f)    = " << eve::binarize_not(pf> 0.0f) << '\n'
    << "-> eve::binarize_not(pf > 0.0f, 3) = " << eve::binarize_not(pf> 0.0f,  3) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                                         = " << xf << '\n'
    << "-> eve::binarize_not(eve::True<float>(), xf)  = " << eve::binarize_not(eve::True<float>(), xf) << '\n'
    << "-> eve::binarize_not(eve::False<float>(), xf) = " << eve::binarize_not(eve::False<float>(), xf) << '\n'        ;
  return 0;
}
