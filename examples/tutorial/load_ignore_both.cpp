//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
//! [snippet]
#include <eve/module/core.hpp>
#include <iostream>

auto load_between( float* ptr )
{
  return eve::load[ (eve::ignore_first(1) && eve::ignore_last(1)).else_(-6.3f) ]( ptr );
}

int main()
{
  std::array<float,eve::wide<float>::size()-1> data;
  for(std::size_t i=0; i < data.size(); ++i) data[i] = 1+i;

  std::cout << load_between(&data[0] - 1) << "\n";
}
//! [snippet]
