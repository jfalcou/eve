//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [snippet]
#include <eve/function/sub.hpp>
#include <eve/wide.hpp>

using w_t = eve::wide<float, eve::fixed<4>>;

auto sub_not_first( w_t const& a, w_t const& b )
{
  return eve::sub[ eve::ignore_first(1) ](a,b);
}

auto sub_not_last( w_t const& a, w_t const& b )
{
  return eve::sub[ eve::ignore_last(1) ](a,b);
}

int main()
{
  w_t v = { 10, 20, 30, 40 };
  w_t w = {  4,  3,  2,  1 };

  std::cout << sub_not_first(v,w) << "\n";
  std::cout << sub_not_last(v,w) << "\n";
}
//! [snippet]
