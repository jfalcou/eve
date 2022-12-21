//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo/algo/array_utils.hpp>
#include <eve/module/algo/algo/common_forceinline_lambdas.hpp>
#include <eve/module/algo/algo/concepts.hpp>
#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/preprocess_range.hpp>
#include <eve/module/algo/algo/traits.hpp>
#include <eve/module/core.hpp>

#include <array>
#include <utility>

namespace eve::algo
{
template<typename TraitsSupport> struct any_of_ : TraitsSupport
{
  template<typename P> struct delegate
  {
    explicit delegate(P p) : p(p) {}

    EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
    {
      eve::logical test = p(eve::load[ignore](it));
      res               = eve::any[ignore](test);
      return res;
    }

    template<typename I, std::size_t size>
    EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
    {
      auto tests   = array_map(arr, load_and_apply {p});
      auto overall = array_reduce(tests, eve::logical_or);
      res          = eve::any(overall);
      return res;
    }

    P    p;
    bool res = false;
  };

  template<relaxed_range Rng, typename P> EVE_FORCEINLINE bool operator()(Rng&& rng, P p) const
  {
    auto processed = preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));

    if( processed.begin() == processed.end() ) return false;

    delegate<P> d {p};
    algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
    return d.res;
  }
};


//================================================================================================
//! @addtogroup algos
//! @{
//!   @var any_of
//!
//!   @brief a SIMD version of `std::any_of`
//!
//!   Tests if any of the elements in the range match the predicate.
//!   by default aligns and unrolls 4 times.
//!
//!   **Alternative Header**
//!
//!   @code
//!   #include <eve/algo.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve::algo
//!   {
//!     template <eve::algo::relaxed_range Rng, typename P>
//!     bool any_of(Rng&& rng, P p);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `rng`: Relaxed input range to process
//!    * 'p':   Predicate
//!
//!   **Return value**
//!
//!   `true` if `p` returns true for at least one element in the range, `false` otherwise.
//!    Returns `false` if the range is empty.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/any_of.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto any_of = function_with_traits<any_of_>[default_simple_algo_traits];
}
