//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
//! [snippet]
#include <eve/module/core.hpp>
#include <array>
#include <iostream>

auto load_not_first( float* ptr )
{
  return eve::load[ eve::ignore_first(1).else_(99) ](ptr);
}

auto load_not_last( float* ptr )
{
  return eve::load[ eve::ignore_last(1).else_(42) ](ptr);
}

int main()
{
  std::array<float,eve::wide<float>::size()> data;
  for(std::size_t i=0; i < data.size(); ++i) data[i] = 1+i;

  std::cout << load_not_first(&data[0] - 1) << "\n";
  std::cout << load_not_last(&data[1]) << "\n";
}
//! [snippet]
