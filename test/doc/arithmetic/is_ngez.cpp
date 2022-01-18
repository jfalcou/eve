//#include <eve/function/is_ngez.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()

{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf          =" << pf << '\n'
            << "-> is_ngez(pf) = " << eve::is_ngez(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "-> is_ngez(xf) = " << eve::is_ngez(xf) << '\n';
  return 0;
}
