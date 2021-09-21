#include <eve/function/binarize.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                          = " << pf << '\n'
    << "-> binarize(pf > 0.0f)         = " << eve::binarize(pf> 0.0f) << '\n'
    << "-> binarize(pf > 0.0f, 3)      = " << eve::binarize(pf> 0.0f,  3) << '\n';

  float xf = -1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                           = " << xf << '\n'
    << "-> binarize(true_(eve::as<float>()), xf)  = " << eve::binarize(eve::true_(eve::as<float>()), xf) << '\n'
    << "-> binarize(false_(eve::as<float>()), xf) = " << eve::binarize(eve::false_(eve::as<float>()), xf) << '\n'        ;
  return 0;
}
