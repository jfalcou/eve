#include <eve/function/diff/sub.hpp>
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
            << "-> sub(pf, qf) = " << eve::sub(pf, qf) << '\n'
            << "-> diff_1st(sub)(pf, qf) = " <<  eve::diff_1st(eve::sub)(pf, qf) << std::endl
            << "-> diff_2nd(sub)(pf, qf) = " <<  eve::diff_2nd(eve::sub)(pf, qf) << std::endl
            << "-> diff(sub)(pf, qf, 0u, 2u) = " <<  eve::diff(eve::sub)(pf, qf, 0u, 2u) << std::endl
            << "-> diff(sub)(pf, qf, 2u, 0u) = " <<  eve::diff(eve::sub)(pf, qf, 2u, 0u) << std::endl;

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "<- yf          = " << yf << '\n'
            << "-> sub(xf, yf) = " << eve::sub(xf, yf) << '\n'
            << "-> diff_1st(sub)(xf, yf) = " <<  eve::diff_1st(eve::sub)(xf, yf) << std::endl
            << "-> diff_2nd(sub)(xf, yf) = " <<  eve::diff_2nd(eve::sub)(xf, yf) << std::endl;
  return 0;
}
