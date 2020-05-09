#include <eve/function/is_ordered.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f, 2.0f,
                eve::Inf<float>(), eve::Minf<float>(), eve::Nan<float>()};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f,  -0.0f,
                eve::Nan<float>(), -2.0f,  -eve::Nan<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf                 = " << pf << '\n'
            << "<- qf                 = " << qf << '\n'
            << "-> is_ordered(pf, qf) = " << eve::is_ordered(pf, qf) << '\n';

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                 = " << xf << '\n'
            << "<- yf                 = " << yf << '\n'
            << "-> is_ordered(xf, yf) = " << eve::is_ordered(xf, yf) << '\n';
  return 0;
}
