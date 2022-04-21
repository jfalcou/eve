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

auto sqrt_positive( w_t const& a )
{
  return eve::sqrt[a >= 0](a);
}

int main()
{
  w_t v = { 1, -2, 10, -3.5 };

  std::cout << sqrt_positive(v) << "\n";
}
//! [snippet]

//! [snippet-alt]
auto sqrt_positive_temp( w_t const& a )
{
  auto const f = eve::sqrt[a >= 0];
  return f(a);
}
//! [snippet-alt]
