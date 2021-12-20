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

auto sub_neither_first_nor_last( w_t const& a, w_t const& b )
{
  return eve::sub[ eve::keep_between(1,3) ](a,b);
}

int main()
{
  w_t v = { 10, 20, 30, 40 };
  w_t w = {  4,  3,  2,  1 };

  std::cout << sub_neither_first_nor_last(v,w) << "\n";
}
//! [snippet]
