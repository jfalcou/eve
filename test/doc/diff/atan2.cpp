//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 3}, qi = {4, 1, 1, ~0};

  std::cout << "---- simd" << '\n'
            << " <- pi              = " << pi << '\n'
            << " <- qi              = " << qi << '\n'
            << " -> eve::diff_1st(atan2)(pi, qi)   = " << eve::diff_1st(eve::atan2)(pi, qi) << '\n'
            << " -> eve::diff_2nd(atan2)(pi, qi)   = " << eve::diff_2nd(eve::atan2)(pi, qi) << '\n';

  double xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi                 = " << xi << '\n'
            << " yi                 = " << yi << '\n'
            << " -> eve::diff_1st(atan2)(xi, yi)   = " << eve::diff_1st(eve::atan2)(xi, yi) << '\n'
            << " -> eve::diff_2nd(atan2)(xi, yi)   = " << eve::diff_2nd(eve::atan2)(xi, yi) << '\n';
  return 0;
}
