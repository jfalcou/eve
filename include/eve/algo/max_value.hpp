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
template<typename TraitsSupport> struct max_value_ : TraitsSupport
{
  template<relaxed_range Rng, typename Less>
  EVE_FORCEINLINE std::optional<eve::value_type_t<Rng>> operator()(Rng&& rng, Less less) const
  {
    if( rng.begin() == rng.end() ) return std::nullopt;

    auto ul             = eve::unalign(rng.begin()) + (rng.end() - rng.begin());
    auto default_answer = eve::read(--ul);

    return eve::algo::reduce[TraitsSupport::get_traits()](
        EVE_FWD(rng), std::pair {eve::max(less), default_answer}, default_answer);
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
//!   @var max_value
//!
//!   @brief SIMD algorithm that returns maximum value in the range.
//!
//!   The standard only has `_element` versions of `min/max` algorithms. However, in SIMD
//!   finding the value is much faster then also finding the position - hense this algorithm.
//!
//!   @note for equivalent elements we return the second amoung equal.
//!   @note we assume that `eve::is_less` defined for your type is total order.
//!        (this comes up when switching `max` with `min`)
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
//!     std::optional<eve::value_type_t<Rng>> max_value(Rng&& rng, Less less);          // 1
//!
//!     template <eve::algo::relaxed_range Rng>
//!     std::optional<eve::value_type_t<Rng>> max_value(Rng&& rng);                    // 2
//!   }
//!   @endcode
//!
//!   1. Returns the maximum value, according to less. If the range is empty - returns nullopt.
//!
//!   2. Same as 1 but the `less` is `eve::is_less`
//!
//!   **Parameters**
//!
//!    * `rng`:  Relaxed input range to process
//!    * `less`: SIMD strict weak ordering.
//!
//!   **Return value**
//!
//!   maximum value from the range. If the input range was empty, it's `std::nullopt`.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/max.cpp}
//!
//!   @see `min_value`
//!   @see `max_element`
//!
//! @}
inline constexpr auto max_value = function_with_traits<max_value_>[default_simple_algo_traits];
}
