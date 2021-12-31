//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [snippet]
#include <eve/function/sqrt.hpp>
#include <eve/wide.hpp>

using w_t = eve::wide<float, eve::fixed<4>>;

auto bound_sqrt( w_t const& a )
{
  return eve::sqrt[a >= 0](a);
}

int main()
{
  w_t v = { 1, -2, 10, -3.5 };

  std::cout << bound_sqrt(v) << "\n";
}
//! [snippet]

//! [snippet-alt]
auto bound_sqrt_temp( w_t const& a )
{
  auto const f = eve::sqrt[a >= 0];
  return f(a);
}
//! [snippet-alt]
