#include <eve/function/diff/atan2.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f,
                -2.0f, -3.0f,  2.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                    = " << pf << '\n'
    << "<- qf                    = " << qf << '\n'
    << "-> diff(atan2)(pf) = " << eve::diff(eve::atan2)(pf, qf) << '\n';

  float xf = 1.0f;
  float yf = -1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                    = " << xf << '\n'
    << "<- yf                    = " << yf << '\n'
    << "-> diff(atan2)(xf) = " << eve::diff(eve::atan2)(xf, yf) << '\n';
  return 0;
}
