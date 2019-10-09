#include <eve/function/ifrexp.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<8>>;
using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_it qi = {-10, 2, -2, 3, -1, 4, 2, -6};
  wide_ft pf = {eve::Mindenormal<float>(),
                1.0f,
                -1.0f,
                eve::Inf<float>(),
                eve::Minf<float>(),
                eve::Nan<float>(),
                0.0f,
                -2.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf =              " << pf << '\n'
            << "<- qi =              " << qi << '\n'
            << "-> eve::ifrexp(pf, qi) = " << eve::ifrexp(pf, qi) << '\n';

  float xf = 2, mxf = -2;
  iT yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xf  =                      " << xf << '\n'
            << "<- mxf =                      " << mxf << '\n'
            << "<- yi  =                      " << yi << '\n'
            << "-> eve::ifrexp(xf, yi) = " << eve::ifrexp(xf, yi) << '\n'
            << "-> eve::ifrexp(mxf, yi)= " << eve::ifrexp(mxf, yi) << '\n';
  return 0;
}
