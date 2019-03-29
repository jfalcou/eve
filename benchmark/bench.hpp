//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BENCHMARK_BENCH_HPP
#define BENCHMARK_BENCH_HPP

#include <benchmark/benchmark.h>
#include <eve/cardinal.hpp>
#include "tts/detail/pp_helpers.hpp"
#include "cycleclock.h"
#include <algorithm>
#include <numeric>
#include <iostream>

namespace eve::bench
{
  // -------------------------------------------------------------------------------------------------
  struct metrics
  {
    std::size_t size;
    void operator()(benchmark::State& state, double cycles, std::size_t byte_size, std::size_t card) const
    {
      auto iter = state.iterations();
      state.SetItemsProcessed( iter * size * card);
      state.SetBytesProcessed( iter * size * byte_size);
      state.counters["cycle_per_value"] = (cycles / iter) / (size*card);
    }
  };

  // -------------------------------------------------------------------------------------------------
  // Generators
  template <typename T> auto value(std::size_t sz, T const& val)
  {
    std::vector<T> data(sz, val);
    return data;
  }

  template <typename T> auto iota(std::size_t sz, T first = {})
  {
    std::vector<T> data(sz);
    std::iota(data.begin(),data.end(),first);
    return data;
  }

  template <typename T> auto arithmetic(std::size_t sz, T first = {}, T step = 1)
  {
    std::vector<T> data(sz);

    data[0] = first;
    for(std::size_t i=1;i<sz;++i) data[i] = data[i-1] + step;

    return data;
  }

  template <typename T> auto geomtric(std::size_t sz, T first = 1, T step = 2)
  {
    std::vector<T> data(sz);

    data[0] = first;
    for(std::size_t i=1;i<sz;++i) data[i] = data[i-1] * step;

    return data;
  }

  template <typename T, typename U> auto random(std::size_t sz, U mn, U mx)
  {
      std::vector<T> data(sz);
      std::generate ( data.begin(), data.end()
                    , [=]()
                      {
                        return static_cast<T>( mn + std::rand() / (double)RAND_MAX * (mx - mn));
                      }
                    );
      return data;
  }

  template<typename Fun, typename... Args>
  struct experiment
  {
    using out_type = decltype( std::declval<Fun>()(std::declval<typename Args::value_type>()...) );

    experiment(std::string const& root, Fun fun, std::size_t size, Args const&... args) : output(size)
    {
      auto card = std::max({eve::cardinal_v<typename Args::value_type>...});
      std::cout << "[EVE] - Target: "<< TTS_STRING(EVE_CURRENT_API) << " - Build type: ";
      #ifdef NDEBUG
      std::cout << "Release - ";
      #else
      std::cout << "Debug - ";
      #endif
      std::cout << "Cardinal: " << card << "\n";

      benchmark::RegisterBenchmark( root.c_str()
                                  , [=,out = output.data()](benchmark::State& st)
                                    {
                                      auto c0 = benchmark::cycleclock::Now();
                                      while (st.KeepRunning())
                                      {
                                        for(std::size_t i=0;i<size;++i) out[i] = fun(args[i]...);
                                        benchmark::DoNotOptimize(out);
                                      }
                                      auto c1 = benchmark::cycleclock::Now();

                                      metrics{size} ( st, (c1 - c0)
                                                    , sizeof(out_type)
                                                    , card
                                                    );
                                    }
                                  );
    }

    private:
    std::vector<out_type> output;
  };
}

int main(int argc, char** argv)
{
  using namespace eve::bench;
  using T = TYPE();

  auto size   = benchmark::CPUInfo::Get().caches[1].size / sizeof(T);
  auto name = std::string(TTS_STRING(FUNCTION())) + " - " + std::string(TTS_STRING(TYPE()));

  experiment _(name, FUNCTION(), size, SAMPLES(size));

  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}

#endif
