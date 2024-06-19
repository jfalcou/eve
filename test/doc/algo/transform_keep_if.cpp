//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> v(16);
  eve::algo::iota(v, 0);
  std::cout << "Input vector:\n  " << tts::as_string(v) << "\n\n";

  auto func = [](eve::like<int> auto x) {
    return kumi::make_tuple(-x, eve::is_even(x));
  };

  v.erase(eve::algo::transform_keep_if(v, func), v.end());
  std::cout << "Output (opposites of even numbers):\n  "
            << tts::as_string(v)
            << "\n\n";
  return 0;
}
