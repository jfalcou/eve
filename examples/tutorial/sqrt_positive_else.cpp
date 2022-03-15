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

using w_t = eve::wide<float, eve::fixed<4>>;

auto sqrt_positive( w_t const& a )
{
  return eve::sqrt[ eve::if_(a >= 0) ](a);
}

auto sqrt_positive_else( w_t const& a )
{
  return eve::sqrt[ eve::if_(a >= 0).else_(0) ](a);
}

int main()
{
  w_t v = { 1, -2, 10, -3.5 };

  std::cout << sqrt_positive(v)       << "\n";
  std::cout << sqrt_positive_else(v)  << "\n";
}
//! [snippet]
