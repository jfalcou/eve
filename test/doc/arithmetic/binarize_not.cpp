#include <eve/function/binarize_not.hpp>
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
    << "<- pf                               = " << pf << '\n'
    << "-> binarize_not(pf > 0.0f)          = " << eve::binarize_not(pf> 0.0f) << '\n'
    << "-> binarize_not(pf > 0.0f, 3)       = " << eve::binarize_not(pf> 0.0f,  3) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                               = " << xf << '\n'
    << "-> binarize_not(true_(eve::as<float>()), xf)  = " << eve::binarize_not(eve::true_(eve::as<float>()), xf) << '\n'
    << "-> binarize_not(false_(eve::as<float>()), xf) = " << eve::binarize_not(eve::false_(eve::as<float>()), xf) << '\n'        ;
  return 0;
}
