//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BENCHMARKS_GENERATORS_HPP
#define BENCHMARKS_GENERATORS_HPP

#include <eve/memory/aligned_allocator.hpp>
#include <eve/arch.hpp>
#include <algorithm>
#include <numeric>

namespace eve::bench
{
  template<typename T>
  using bench_alloc = eve::aligned_allocator<T, eve::limits<EVE_CURRENT_API>::bytes>;

  template<typename T>
  inline const auto optimal_size = benchmark::CPUInfo::Get().caches[1].size / sizeof(T);

  // -------------------------------------------------------------------------------------------------
  // Generators
  template <typename T> auto value(T const& val)
  {
    std::vector<T,bench_alloc<T>> data(optimal_size<T>, val);
    return data;
  }

  template <typename T> auto iota(T first = {})
  {
    std::vector<T,bench_alloc<T>> data(optimal_size<T>);
    std::iota(data.begin(),data.end(),first);
    return data;
  }

  template <typename T> auto arithmetic(T first = {}, T step = 1)
  {
    std::vector<T,bench_alloc<T>> data(optimal_size<T>);

    data[0] = first;
    for(std::size_t i=1;i<optimal_size<T>;++i) data[i] = data[i-1] + step;

    return data;
  }

  template <typename T> auto geometric(T first = 1, T step = 2)
  {
    std::vector<T,bench_alloc<T>> data(optimal_size<T>);

    data[0] = first;
    for(std::size_t i=1;i<optimal_size<T>;++i) data[i] = data[i-1] * step;

    return data;
  }

  template <typename T, typename U> auto random(U mn, U mx)
  {
    std::vector<T,bench_alloc<T>> data(optimal_size<T>);
    std::generate ( data.begin(), data.end()
                  , [=]()
                    {
                      return static_cast<T>( mn + std::rand() / (double)RAND_MAX * (mx - mn));
                    }
                  );
    return data;
  }
}

#endif
