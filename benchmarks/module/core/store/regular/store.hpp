//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "memory_op_with_ignore_bench.hpp"

// The cost of a partial store of a native register.

int main()
{
  using T   = EVE_VALUE;
  using w_t = eve::wide<T>;

  // The value is opaque to the compiler, but stays in a register.
  w_t v{T{2}};
  ankerl::nanobench::doNotOptimizeAway(v);

  // doNotOptimizeAway(ptr) after the store: the pointer is already in a register and the memory
  // clobber keeps the store alive, without loading anything back.
  eve::bench::memory_op_with_ignore_bench<T, w_t::size()>(
    "store",
    [v](auto const* c)
    {
      eve::store[c->ignore](v, c->ptr);
      ankerl::nanobench::doNotOptimizeAway(c->ptr);
    });
}
