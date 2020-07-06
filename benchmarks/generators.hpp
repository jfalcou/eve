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

#include <eve/logical.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/arch.hpp>
#include <eve/arch/spec.hpp>
#include <algorithm>
#include <numeric>
#include <random>

namespace eve::bench
{
  inline std::mt19937 pRNG = {};

  template<typename T> using alloc = eve::aligned_allocator<T,eve::limits<EVE_CURRENT_API>::bytes>;
  template<typename T> inline const auto optimal_size = 92*1024/sizeof(T);

  // -------------------------------------------------------------------------------------------------
  // Helpers over begin/end
  template<typename C> inline decltype(auto) begin(C&& c)
  {
    if constexpr( requires{ c.begin(); } )  return std::forward<C>(c).begin();
    else                                    return &c;
  }

  template<typename C> inline auto end(C&& c)
  {
    if constexpr( requires{ c.end(); } )  return std::forward<C>(c).end();
    else                                  return (&c) + 1;
  }

  // -------------------------------------------------------------------------------------------------
  // Generators
  template <typename U, typename T> auto value_(T const& val)
  {
    return std::vector<U,alloc<U>>(optimal_size<U>, static_cast<U>(val));
  }

  template <typename U, typename T> auto random_(T mn, T mx)
  {
    std::vector<U,alloc<U>>                 data(optimal_size<U>);
    std::uniform_real_distribution<double>  dist(mn,mx);
    std::generate(data.begin(), data.end(), [&]() { return static_cast<U>( dist(pRNG) ); });

    return data;
  }

  template <typename U> auto bernoulli_()
  {
    std::vector<eve::logical<U>,alloc<eve::logical<U>>>   data(optimal_size<U>);
    std::bernoulli_distribution dist;
    std::generate ( data.begin(), data.end()
                  , [&]()
                  {
                    return static_cast<eve::logical<U>>( dist(pRNG) );
                  }
                  );
    return data;
  }


}

#endif
