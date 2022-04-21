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

namespace doc_utils
{
  template<eve::algo::relaxed_range R>
  void print(R const & v)
  {
    auto n = v.end() - v.begin();
    auto cur = v.begin();
    if(n)
    {
      for(auto i = 1;  i !=  n; ++i, ++cur) {std::cout << +eve::read(cur) << " ";};
      if (n) std::cout << +eve::read(cur) << "\n";
    }
  }
}
