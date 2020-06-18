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
  template<typename T> inline const auto optimal_size = 128*1024 / sizeof(T);

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
  template <typename T> struct value_
  {
    value_(T const& val) : v_(val) {}

    template <typename U> auto build() const
    {
      return std::vector<U,alloc<U>>(optimal_size<U>, static_cast<U>(v_));
    }

    T v_;
  };

  template <typename T>
  struct random_
  {
    template <typename U> random_(U mn, U mx) : vmn_(mn), vmx_(mx) {}

    template <typename U> auto build() const
    {
      std::vector<U,alloc<U>> data(optimal_size<U>);
      std::uniform_real_distribution<double> dist(vmn_,vmx_);

      std::generate ( data.begin(), data.end()
                    , [&]()
                      {
                        U that{};
                        std::generate ( bench::begin(that), bench::end(that)
                                      , [&]()
                                        {
                                          return static_cast<eve::element_type_t<U>>( dist(pRNG) );
                                        }
                                      );
                        return that;
                      }
                    );

      return data;
    }

    T vmn_, vmx_;
  };
}

#endif
