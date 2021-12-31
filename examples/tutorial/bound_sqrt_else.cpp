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
  return eve::sqrt[ eve::if_(a >= 0) ](a);
}

auto bound_sqrt_else( w_t const& a )
{
  return eve::sqrt[ eve::if_(a >= 0).else_(0) ](a);
}

int main()
{
  w_t v = { 1, -2, 10, -3.5 };

  std::cout << bound_sqrt(v)       << "\n";
  std::cout << bound_sqrt_else(v)  << "\n";
}
//! [snippet]
