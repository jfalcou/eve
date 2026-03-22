//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <type_traits>

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#define TTS_MAIN
#include <tts/tts.hpp>
#include <eve/module/core.hpp>
#include <eve/memory/align.hpp>
#include <eve/memory/aligned_allocator.hpp>

namespace eve::bench
{
  template <typename... Generators>
  class benchmark
  {
    private:
    ankerl::nanobench::Bench bench;
    std::size_t dataSize;
    std::size_t repetitions;

    kumi::tuple<Generators...> gens;
    std::vector<std::ptrdiff_t> run_cardinals;

    void configure_bench()
    {
      bench.output(nullptr);
      bench.performanceCounters(true);
      bench.epochs(repetitions);
      bench.batch(dataSize);
    }

    template <typename TestType, typename Func, std::size_t... Is>
    void execute_internal(const std::string& name, Func func, std::index_sequence<Is...>)
    {
      constexpr std::ptrdiff_t N = eve::cardinal_v<TestType>;
      constexpr bool is_scalar = std::is_same_v<TestType, eve::element_type_t<TestType>>;

      std::size_t alignedDataSize = eve::align(dataSize, eve::over{static_cast<std::size_t>(N)});

      run_cardinals.push_back(N);

      kumi::tuple<std::vector<std::invoke_result_t<Generators>,
                              eve::aligned_allocator<std::invoke_result_t<Generators>>>...> data;

      (
        ( kumi::get<Is>(data).resize(alignedDataSize),
          std::generate(kumi::get<Is>(data).begin(), kumi::get<Is>(data).end(), kumi::get<Is>(gens))
        ), ...
      );

      bench.batch(alignedDataSize);

      bench.run(name, [&]()
      {
        if constexpr (is_scalar)
        {
          for (std::size_t i = 0; i < alignedDataSize; ++i)
          {
            if constexpr (std::is_void_v<decltype(func(kumi::get<Is>(data)[i]...))>)
            {
              func(kumi::get<Is>(data)[i]...);
              (ankerl::nanobench::doNotOptimizeAway(kumi::get<Is>(data)[i]), ...);
            }
            else
            {
              ankerl::nanobench::doNotOptimizeAway(func(kumi::get<Is>(data)[i]...));
            }
          }
        }
        else
        {
          // Capture the underlying scalar types of all generators
          using GenTypes = std::tuple<std::invoke_result_t<Generators>...>;

          for (std::size_t i = 0; i < alignedDataSize; i += N)
          {
            if constexpr( std::is_void_v<decltype(func(eve::wide< std::tuple_element_t<Is, GenTypes>
                                                                , eve::fixed<N>
                                                                >(&kumi::get<Is>(data)[i])...))>
                        )
            {
              func(eve::wide<std::tuple_element_t<Is, GenTypes>, eve::fixed<N>>(&kumi::get<Is>(data)[i])...);
            }
            else
            {
              auto res = func(eve::wide<std::tuple_element_t<Is, GenTypes>, eve::fixed<N>>(&kumi::get<Is>(data)[i])...);

              using ResType = decltype(res);

              // Fallback just in case the benchmarked function is a function that returns a  scalar
              if constexpr (std::is_arithmetic_v<ResType>)
              {
                ankerl::nanobench::doNotOptimizeAway(res);
              }
              else
              {
                alignas(ResType) eve::element_type_t<ResType> scratch[N];
                eve::store(res, scratch);
                ankerl::nanobench::doNotOptimizeAway(scratch);
              }
            }
          }
        }
      });
    }

    template <typename TestType, typename Func>
    void execute_single_run(const std::string& name, Func func)
    {
      execute_internal<TestType>(name, func, std::index_sequence_for<Generators...>{});
    }

    public:
    benchmark(std::size_t dataSize, std::size_t repetitions, Generators... generators)
      : dataSize(dataSize), repetitions(repetitions), gens{generators...}
    {
      configure_bench();
    }

    benchmark(Generators... generators) : benchmark(4096, 10, generators...)
    {
    }

    ~benchmark()
    {
      report();
    }

    benchmark& reset()
    {
      bench = ankerl::nanobench::Bench();
      run_cardinals.clear();
      configure_bench();
      return *this;
    }

    template <typename TestType = kumi::element_t<0, kumi::tuple<std::invoke_result_t<Generators>...>>,
              typename Func, typename... Rest>
    benchmark& run(const std::string& name, Func func, Rest&&... rest)
    {
      static_assert ( sizeof...(rest) % 2 == 0
                    , "Arguments to run() must be provided in pairs: (\"Name\", function)."
                    );

      execute_single_run<TestType>(name, func);

      if constexpr (sizeof...(rest) > 0)
        run<TestType>(std::forward<Rest>(rest)...);

      return *this;
    }

    benchmark& report(std::ostream& out = std::cout)
    {
      auto const& results = bench.results();
      if (results.empty()) return *this;

      out << "| Name | N | Speedup | Eff. | cyc/elem | min | max | elem/s | ins/elem |\n";
      out << "|:---|---:|---:|---:|---:|---:|---:|---:|---:|\n";

      double baseline_time = results.front().median(ankerl::nanobench::Result::Measure::elapsed);

      for (std::size_t i = 0; i < results.size(); ++i)
      {
        auto const& res = results[i];
        double current_time = res.median(ankerl::nanobench::Result::Measure::elapsed);
        double batch_size   = static_cast<double>(res.config().mBatch);
        std::ptrdiff_t N    = run_cardinals[i];

        double speedup      = baseline_time / current_time;
        double efficiency   = speedup / static_cast<double>(N);
        double elem_per_sec = batch_size / current_time;

        double ins_per_elem = res.median(ankerl::nanobench::Result::Measure::instructions) / batch_size;
        double cyc_per_elem = res.median(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;
        double min_cyc_elem = res.minimum(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;
        double max_cyc_elem = res.maximum(ankerl::nanobench::Result::Measure::cpucycles) / batch_size;

        out << "| " << res.config().mBenchmarkName << " | " << N << " | ";

        if (speedup == 1.0)
        {
          out << "x1.00 | ";
        }
        else
        {
          out << "x" << std::fixed << std::setprecision(2) << speedup << " | ";
        }

        out << std::fixed << std::setprecision(1) << (efficiency * 100.0) << "% | "
            << std::fixed << std::setprecision(2) << cyc_per_elem << " | "
            << std::setprecision(2) << min_cyc_elem << " | "
            << std::setprecision(2) << max_cyc_elem << " | "
            << std::setprecision(0) << elem_per_sec << " | "
            << std::setprecision(2) << ins_per_elem << " |\n";
      }

      out << "\n" << std::flush;
      return *this;
    }
  };
}
