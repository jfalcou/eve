//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/reduce.hpp>
#include <eve/algo/traits.hpp>
#include <eve/module/core.hpp>

#include <optional>

namespace eve::algo
{
template<typename TraitsSupport> struct min_value_ : TraitsSupport
{
  template<relaxed_range Rng, typename Less>
  EVE_FORCEINLINE std::optional<eve::value_type_t<Rng>> operator()(Rng&& rng, Less less) const
  {
    if( rng.begin() == rng.end() ) return std::nullopt;

    // We could advance the rng.begin() here but it can mess the alignment
    // and it's just one element, so we won't.
    auto default_answer = eve::read(rng.begin());

    return eve::algo::reduce[TraitsSupport::get_traits()](
        EVE_FWD(rng), std::pair {eve::min(less), default_answer}, default_answer);
  }

  template<relaxed_range Rng>
  EVE_FORCEINLINE std::optional<eve::value_type_t<Rng>> operator()(Rng&& rng) const
  {
    return operator()(EVE_FWD(rng), eve::is_less);
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!   @var min_value
//!
//!   @brief SIMD algorithm that returns minimum value in the range.
//!
//!   C++ standard only has `std::min_element` that returns iterator
//!   to the minimum element.
//!   We have that too (see: `eve::algo::min_element`) but it's slower then just
//!   getting the value. So we also provide `min_value` for when you don't care about the
//!   position.
//!   By default unrolls by 4 and aligned all memory accesses.
//!
//!   @note for equivalent elements we return the first amoung equal.
//!   @note we assume that `eve::is_less` defined for your type is total order.
//!        (this comes up when switching `min` with `max`)
//!
//!   **Alternative Header**
//!
//!   @code
//!   #include <eve/algo.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!   @code
//!   namespace eve::algo
//!   {
//!     template <eve::algo::relaxed_range Rng, typename Less>
//!     std::optional<eve::value_type_t<Rng>> min_value(Rng&& rng, Less less);          // 1
//!
//!     template <eve::algo::relaxed_range Rng>
//!     std::optional<eve::value_type_t<Rng>> min_value(Rng&& rng);                    // 2
//!   }
//!   @endcode
//!
//!   1. Returns the minimum value, according to less. If the range is empty - returns nullopt.
//!
//!   2. Same as 1 but the less is `eve::is_less`
//!
//!   **Parameters**
//!
//!    * `rng`:  Relaxed input range to process
//!    * `less`: SIMD strict weak ordering.
//!
//!   **Return value**
//!
//!   minimum value from the range. If the input range was empty, it's `std::nullopt`.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/min.cpp}
//!
//!   @see `max_value`
//!   @see `min_element`
//!
//! @}
//================================================================================================
inline constexpr auto min_value = function_with_traits<min_value_>[default_simple_algo_traits];
}
