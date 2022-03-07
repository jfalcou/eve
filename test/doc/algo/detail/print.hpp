//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/concepts/relaxed.hpp>
#include <iostream>

namespace eve::detail
{
  template < eve::algo::relaxed_range R>
  void print(R const & v)
  {
    for(auto i = v.begin();  i !=  v.end(); ++i) {std::cout << +eve::read(i) << ' ';};
    std::cout << '\n';
  }
}
