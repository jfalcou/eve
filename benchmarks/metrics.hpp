//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BENCHMARKS_METRICS_HPP
#define BENCHMARKS_METRICS_HPP

#include <benchmark/benchmark.h>

namespace eve::bench
{
  struct metrics
  {
    std::size_t size;
    void operator()(benchmark::State& state, double cycles, std::size_t c) const
    {
      auto iter = state.iterations();
      state.SetItemsProcessed( iter * size * c);
      state.counters["cycle_per_value"] = (cycles / iter) / (size*c);
    }
  };
}

#endif
