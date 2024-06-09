#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {1.0f, 2.0f, -3.0f, eve::inf(eve::as<float>()),
                eve::inf(eve::as<float>()), eve::nan(eve::as<float>()), -0.0f, 0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> sqrt(pf)        = " << eve::sqrt(pf) << '\n'
            << "-> sqrt[raw](pf)   = " << eve::sqrt[eve::raw2](pf) << '\n'
            << "-> sqrt[pf > 0](pf)= " << eve::sqrt[pf > 0](pf) << '\n';


  float xf = 32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> sqrt(xf)        = " << eve::sqrt(xf) << '\n';

  return 0;
}
