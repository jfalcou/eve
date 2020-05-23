#include <eve/function/exponent.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-1.0f, 0.0f, 367.0f, -1005600.0f, eve::Mindenormal<float>(),
               eve::Inf<float>(), eve::Minf<float>(), eve::Nan<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> exponent(pf) = " << eve::exponent(pf) << '\n';

  float        xf = -32768.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf           = " << xf << '\n'
            << "-> exponent(xf) = " << eve::exponent(xf) << '\n';
  return 0;
}
