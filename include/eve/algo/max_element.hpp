//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/find_last.hpp>
#include <eve/algo/max_value.hpp>

namespace eve::algo
{
template<typename TraitsSupport> struct max_element_ : TraitsSupport
{
  template<relaxed_range Rng, typename Less>
  EVE_FORCEINLINE auto operator()(Rng&& rng, Less less) const -> unaligned_iterator_t<Rng>
  {
    if( rng.begin() == rng.end() ) return unalign(rng.begin());
    auto v = *max_value[TraitsSupport::get_traits()](EVE_FWD(rng), less);
    // less(x, max) -> false only for max
    return eve::algo::find_last_if_not[TraitsSupport::get_traits()](EVE_FWD(rng), bind_second{less, v});
  }

  template<relaxed_range Rng>
  EVE_FORCEINLINE auto operator()(Rng&& rng) const -> unaligned_iterator_t<Rng>
  {
    return operator()(EVE_FWD(rng), eve::is_less);
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!   @var max_element
//!
//!   @brief SIMD variation on `std::max_element` *not exact match*
//!
//!   @note if you just need a value and not position, use `eve::algo::max_value`.
//!
//!   By default unrolls by 4 and aligned all memory accesses.
//!
//!   @note for equivalent elements we return the second amoung equal.
//!   `std::max_element* returns first but this is more correct and this is also what
//!   `std::minmax_element` will return as max.
//!
//!   @note we assume that `eve::is_less` defined for your type is total order.
//!        (this comes up when switching min with max)
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
//!      template<relaxed_range Rng, typename Less>
//!      auto max_element(Rng&& rng, Less less) -> unaligned_iterator_t<Rng>;   // 1
//!
//!      template<relaxed_range Rng>
//!      auto max_element(Rng&& rng) -> unaligned_iterator_t<Rng>;            // 2
//!   }
//!   @endcode
//!
//!   1. Returns the position of a maximum value, according to less.
//!      If the range is empty - returns past the end.
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
//!   iterator to max element (end if the range is empty).
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/max.cpp}
//!
//!   @see `max_value`
//!   @see `min_element`
//!
//! @}
//================================================================================================
inline constexpr auto max_element = function_with_traits<max_element_>[default_simple_algo_traits];

}
