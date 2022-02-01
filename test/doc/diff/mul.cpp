#include <eve/function/diff/mul.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f,
                -2.0f, -3.0f,  2.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf          = " << pf << '\n'
            << "<- qf          = " << qf << '\n'
            << "-> mul(pf, qf) = " << eve::mul(pf, qf) << '\n'
            << "-> diff_1st(mul)(pf, qf) = " <<  eve::diff_1st(eve::mul)(pf, qf) << std::endl
            << "-> diff_2nd(mul)(pf, qf) = " <<  eve::diff_2nd(eve::mul)(pf, qf) << std::endl
            << "-> diff(mul)(pf, qf, 0u, 2u) = " <<  eve::diff(eve::mul)(pf, qf, 0u, 2u) << std::endl
            << "-> diff(mul)(pf, qf, 2u, 0u) = " <<  eve::diff(eve::mul)(pf, qf, 2u, 0u) << std::endl;

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "<- yf          = " << yf << '\n'
            << "-> mul(xf, yf) = " << eve::mul(xf, yf) << '\n'
            << "-> diff_1st(mul)(xf, yf) = " <<  eve::diff_1st(eve::mul)(xf, yf) << std::endl
            << "-> diff_2nd(mul)(xf, yf) = " <<  eve::diff_2nd(eve::mul)(xf, yf) << std::endl;
  return 0;
}
