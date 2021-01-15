#include <eve/function/diff/pow.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
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
            << "-> pow(pf, qf) = " << eve::pow(pf, qf) << '\n'
            << "-> diff_1st(pow)(pf, qf) = " <<  eve::diff_1st(eve::pow)(pf, qf) << std::endl
            << "-> diff_2nd(pow)(pf, qf) = " <<  eve::diff_2nd(eve::pow)(pf, qf) << std::endl;

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "<- yf          = " << yf << '\n'
            << "-> pow(xf, yf) = " << eve::pow(xf, yf) << '\n'
            << "-> diff_1st(pow)(xf, yf) = " <<  eve::diff_1st(eve::pow)(xf, yf) << std::endl
            << "-> diff_2nd(pow)(xf, yf) = " <<  eve::diff_2nd(eve::pow)(xf, yf) << std::endl;
  return 0;
}
