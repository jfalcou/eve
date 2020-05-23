//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BENCHMARK_BENCH_HPP
#define BENCHMARK_BENCH_HPP

#include <benchmark/benchmark.h>
#include <eve/traits/cardinal.hpp>
#include "tts/detail/type_id.hpp"
#include "cycleclock.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <type_traits>

// Turn a variadic macro calls into a string containing properly placed commas
#define AS_STRING(...)    AS_STRING_((__VA_ARGS__))
#define AS_STRING__(...)  #__VA_ARGS__
#define AS_STRING_(TXT)   AS_STRING__ TXT

#define AS_UNIQUE3(ID, LINE)  ID##LINE
#define AS_UNIQUE2(ID, LINE)  AS_UNIQUE3(ID, LINE)
#define AS_UNIQUE(ID)         AS_UNIQUE2(ID, __LINE__)

#define EVE_REGISTER_BENCHMARK(FUNC, TYPE, ...)                                                     \
eve::bench::experiment  AS_UNIQUE(bench)                                                            \
                        ( std::string(AS_STRING(FUNC)) + " - " + ::tts::type_id<TYPE>()             \
                        , FUNC, eve::bench::optimal_size<TYPE>, __VA_ARGS__                         \
                        )                                                                           \
/**/


namespace eve::bench
{
  template<typename Fun, typename... Args>
  struct experiment
  {
    using out_type = decltype( std::declval<Fun>()(std::declval<typename Args::value_type>()...) );

    experiment(std::string const& root, Fun fun, std::size_t size, Args const&... args) : output(size)
    {
      auto card = std::max({eve::cardinal_v<typename Args::value_type>...});

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

                                      metrics{size}(st, (c1 - c0), card);
                                    }
                                  )
      ->ReportAggregatesOnly(true)
      ->Repetitions(5);
    }

  private:
    using o_t = std::conditional_t< std::is_same_v<out_type,bool>, int, out_type>;
    std::vector < o_t >  output;
  };

  inline void start_benchmarks(int argc, char** argv)
  {
    benchmark::Initialize(&argc, argv);

    std::cout << "[EVE] - Target: "<< AS_STRING(EVE_CURRENT_API) << " - Build type: ";
    #ifdef NDEBUG
    std::cout << "Release\n";
    #else
    std::cout << "Debug\n";
    #endif

    benchmark::RunSpecifiedBenchmarks();
  }
}

#endif

