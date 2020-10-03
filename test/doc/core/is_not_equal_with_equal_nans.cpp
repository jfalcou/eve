#include <eve/function/predicate.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f,
                1.0f,
                -1.0f,
                -2.0f,
                eve::mindenormal(eve::as<float>()),
                eve::inf(eve::as<float>()),
                eve::minf(eve::as<float>()),
                eve::nan(eve::as<float>())};
  wide_ft qf = {0.0f,
                eve::inf(eve::as<float>()),
                eve::minf(eve::as<float>()),
                eve::nan(eve::as<float>()),
                0.0f,
                1.0f,
                -1.0f,
                eve::nan(eve::as<float>())};

  std::cout << "---- simd" << '\n'
            << "<- pf =                  " << pf << '\n'
            << "<- qf =                  " << qf << '\n'
            << "-> eve::numeric(eve::is_not_equal)(pf, qf) = "
            << eve::numeric(eve::is_not_equal)(pf, qf) << '\n';

  float xf1 = 1.0f;
  float xf2 = eve::nan(eve::as<float>());
  float yf  = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf1 =                  " << xf1 << '\n'
            << "<- xf2 =                  " << xf2 << '\n'
            << "<- yf =                   " << yf << '\n'
            << "-> eve::numeric(eve::is_not_equal)(xf1, yf) = "
            << eve::numeric(eve::is_not_equal)(xf1, yf) << '\n'
            << "-> eve::numeric(eve::is_not_equal)(xf2, yf) = "
            << eve::numeric(eve::is_not_equal)(xf2, yf) << '\n';
  return 0;
}
