//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [snippet]
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using w_t = eve::wide<float, eve::fixed<4>>;

auto square_or_diff( w_t const& a, w_t const& b )
{
  std::cout << (a == b) << "\n";
  std::cout << a*b    << "\n";
  std::cout << a-b    << "\n";
  return eve::if_else( a == b, a * b, a - b );
}

int main()
{
  w_t v1 = { 1,  2, 3 , 4 };
  w_t v2 = { 1, -2, 10, 4 };

  std::cout << square_or_diff(v1,v2) << "\n";
}
//! [snippet]
