#include <eve/function/cos.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/pi.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), eve::pi(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf      = " << pf << '\n'
            << "-> cos(pf) = " << eve::cos(pf) << '\n';

  float xf = 3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> cos(xf) = " << eve::cos(xf) << '\n';

  using wide_dt = eve::wide<double, eve::fixed<4>>;

  wide_dt e{+0x1.42ae8e38e5eb9p+954, +0x1.ee7ed0206072ap+559, +0x1.d71af50a57018p-128, +0x1.154e112f8b03cp-826};
  std::cout << "---- simd" << std::hexfloat << '\n'
            << "<- e      = " << e << '\n'
             << "-> cos(e) = " << eve::big(eve::cos)(e) << '\n';

  return 0;
}
