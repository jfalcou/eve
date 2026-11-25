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

  eve::bench::memory_op_with_ignore_bench<T const, w_t::size()>(
    "load",
    [](auto const* c)
    {
      ankerl::nanobench::doNotOptimizeAway(eve::load[c->ignore](c->ptr, eve::as<w_t>{}));
    });
}
