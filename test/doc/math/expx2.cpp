#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{

  wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
               eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> expx2(pf)        = " << eve::expx2(pf) << '\n'
            << "-> diff(expx2)(pf)  = " << eve::diff(eve::expx2)(pf) << '\n'
            << "-> expx2(pf, -1.0f) = " << eve::expx2(pf, -1.0f) << '\n';

  float xf = 1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf        = " << xf << '\n'
            << "-> expx2(xf) = " << eve::expx2(xf) << '\n';
  return 0;
}
