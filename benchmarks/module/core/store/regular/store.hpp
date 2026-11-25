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

  eve::bench::memory_op_with_ignore_bench(
    "store",
    eve::as<w_t>{},
    [v](T* ptr, eve::relative_conditional_expr auto ignore)
    {
      eve::store[ignore](v, ptr);
      ankerl::nanobench::doNotOptimizeAway(ptr);
    });
}
