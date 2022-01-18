//#include <eve/function/ldexp.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;
using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_it qi = {12, 2, -2, 3 };
  wide_ft pf = {1.0f, -1.0f, 0.0f, -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf            = " << pf << '\n'
            << "<- qi            = " << qi << '\n'
            << "-> ldexp(pf, qi) = " << eve::ldexp(pf, qi) << '\n';

  float xf = 2, mxf = -2;
  iT yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xf             = " << xf << '\n'
            << "<- mxf            = " << mxf << '\n'
            << "<- yi             = " << yi << '\n'
            << "-> ldexp(xf, yi)  = " << eve::ldexp(xf, yi) << '\n'
            << "-> ldexp(mxf, yi) = " << eve::ldexp(mxf, yi) << '\n';
  return 0;
}
