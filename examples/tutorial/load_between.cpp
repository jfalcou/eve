//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
//! [snippet]
#include <eve/module/core.hpp>
#include <iostream>

auto load_between( float* ptr )
{
  return eve::load[ eve::keep_between(1,3).else_(-6.3f) ]( ptr );
}

int main()
{
  std::array<float,eve::wide<float>::size()-1> data;
  for(std::size_t i=0; i < data.size(); ++i) data[i] = 1+i;

  std::cout << load_between(&data[0] - 1) << "\n";
}
//! [snippet]
