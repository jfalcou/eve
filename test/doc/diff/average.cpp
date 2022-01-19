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
            << "-> average(pf, qf)                     = " << eve::average(pf, qf) << '\n'
            << "-> diff_1st(average)(pf, qf)        = " <<  eve::diff_1st(eve::average)(pf, qf) << std::endl
            << "-> diff_2nd(average)(pf, qf)        = " <<  eve::diff_2nd(eve::average)(pf, qf) << std::endl
            << "-> diff(average)(pf, qf, 0u, 2u) = " <<  eve::diff(eve::average)(pf, qf, 0u, 2u) << std::endl
            << "-> diff(average)(pf, qf, 2u, 0u) = " <<  eve::diff(eve::average)(pf, qf, 2u, 0u) << std::endl;

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                           = " << xf << '\n'
            << "<- yf                           = " << yf << '\n'
            << "-> average(xf, yf)              = " << eve::average(xf, yf) << '\n'
            << "-> diff_1st(average)(xf, yf) = " <<  eve::diff_1st(eve::average)(xf, yf) << std::endl
            << "-> diff_2nd(average)(xf, yf) = " <<  eve::diff_2nd(eve::average)(xf, yf) << std::endl;
  return 0;
}
