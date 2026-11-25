//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "memory_op_with_ignore_bench.hpp"

int main()
{
  using T   = EVE_VALUE;
  using w_t = eve::wide<T>;

  w_t v{T{2}};
  ankerl::nanobench::doNotOptimizeAway(v);

  eve::bench::memory_op_with_ignore_bench<T, w_t::size()>(
    "store",
    [v](auto const* c)
    {
      eve::store[c->ignore](v, c->ptr);
      ankerl::nanobench::doNotOptimizeAway(c->ptr);
    });
}
