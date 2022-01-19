//================================================================================================== 
/** 
  EVE - Expressive Vector Engine 
  Copyright : EVE Contributors & Maintainers 
  SPDX-License-Identifier: MIT 
**/ 
//================================================================================================== 
 
#include <eve/module/arithmetic.hpp> 
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f,
                -2.0f, -3.0f,  2.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf                                  = " << pf << '\n'
            << "<- qf                                  = " << qf << '\n'
            << "-> negate(pf, qf)                      = " << eve::negate(pf, qf) << '\n'
            << "-> diff_1st(negate)(pf, qf)      = " <<  eve::diff_1st(eve::negate)(pf, qf) << std::endl
            << "-> diff_2nd(negate)(pf, qf)      = " <<  eve::diff_2nd(eve::negate)(pf, qf) << std::endl;

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                             = " << xf << '\n'
            << "<- yf                             = " << yf << '\n'
            << "-> negate(xf, yf)                 = " << eve::negate(xf, yf) << '\n'
            << "-> diff_1st(negate)(xf, yf) = " <<  eve::diff_1st(eve::negate)(xf, yf) << std::endl
            << "-> diff_2nd(negate)(xf, yf) = " <<  eve::diff_2nd(eve::negate)(xf, yf) << std::endl;
  return 0;
}
