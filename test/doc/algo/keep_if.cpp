//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<int> v= {1,2,3,4,5,6,7,8,9,10,11,12,13};

  std::cout << " -> v                                                      = ";
  doc_utils::print(v);

  std::cout << " <- v.erase(eve::algo::keep_if(r1, eve::is_odd), v.end())  = ";
  v.erase(eve::algo::keep_if(v, eve::is_odd), v.end());
  doc_utils::print(v);

  return 0;
}
