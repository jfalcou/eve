//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
//! [snippet]
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using w_t = eve::wide<float, eve::fixed<4>>;

auto sqrt_positive( w_t const& a )
{
  return eve::if_else( a >= 0, eve::sqrt(a), a);
}

int main()
{
  w_t v = { 1, -2, 10, -3.5 };

  std::cout << sqrt_positive(v) << "\n";
}
//! [snippet]
