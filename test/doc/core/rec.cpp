#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, 2.0f, 10.0f, 200.0f, 1000.0f,
               eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf            = " << pf << '\n'
            << "-> rec)(pf)      = " << eve::rec(pf) << '\n'
            << "-> diff(rec)(pf) = " << eve::diff(eve::rec)(pf) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> rec(xf) = " << eve::rec(xf) << '\n';
  return 0;
}
