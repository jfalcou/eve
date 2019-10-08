#include <eve/function/ldexp.hpp>
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
            << "-> eve::ldexp(pf, qi) = " << eve::ldexp(pf, qi) << '\n';

  iT xi = 2, mxi = -2, yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xi  =                      " << xi << '\n'
            << "<- mxi =                      " << mxi << '\n'
            << "<- yi  =                      " << yi << '\n'
            << "-> eve::ldexp(xi, yi) = " << eve::ldexp(xi, yi) << '\n'
            << "-> eve::ldexp(mxi, yi)= " << eve::ldexp(mxi, yi) << '\n';
  return 0;
}
