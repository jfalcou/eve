//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "memory_op_with_ignore_bench.hpp"

// The cost of a partial load of a native register.

int main()
{
  using T   = EVE_VALUE;
  using w_t = eve::wide<T>;

  eve::bench::memory_op_with_ignore_bench(
    "load",
    eve::as<w_t>{},
    [](T* ptr, eve::relative_conditional_expr auto ignore)
    {
      ankerl::nanobench::doNotOptimizeAway(eve::load[ignore](ptr, eve::as<w_t>{}));
    });
}
