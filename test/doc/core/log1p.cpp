#include <eve/function/log1p.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -0.0f, 0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf        =  " << pf << '\n'
            << "-> log1p(pf) =  " << eve::log1p(pf) << '\n';

  float        xf = 3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> log1p(xf) = " << eve::log1p(xf) << '\n';
  return 0;
}
