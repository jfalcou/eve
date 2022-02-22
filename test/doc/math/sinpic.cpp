#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), 0.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf         = " << pf << '\n'
            << "-> sinpic(pf) = " << eve::sinpic(pf) << '\n'
            << "-> diff(sinpic)(pf) = " << eve::diff(eve::sinpic)(pf) << '\n';

  float xf = 3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf         = " << xf << '\n'
            << "-> sinpic(xf) = " << eve::sinpic(xf) << '\n';
  return 0;
}
