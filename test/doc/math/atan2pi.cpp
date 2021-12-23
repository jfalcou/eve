//#include <eve/function/atan2pi.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, 4.0f, -2.0f };
  wide_ft qf = { 1.0f, -1.0f, 3.0f, -0.0f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf              = " << pf << '\n'
    << "<- qf              = " << qf << '\n'
    << "-> atan2pi(pf, qf) = " << eve::atan2pi(pf, qf) << '\n';

  float xf = 2.0f;
  float yf = 10.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf              = " << xf << '\n'
    << "-> atan2pi(xf, yf) = " << eve::atan2pi(xf, yf) << '\n';
  return 0;
}
