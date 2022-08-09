//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/find.hpp>
#include <eve/algo/min_value.hpp>

namespace eve::algo
{
template<typename TraitsSupport> struct min_element_ : TraitsSupport
{
  template<relaxed_range Rng, typename Less>
  EVE_FORCEINLINE auto operator()(Rng&& rng, Less less) const -> unaligned_iterator_t<Rng>
  {
    if( rng.begin() == rng.end() ) return unalign(rng.begin());

    auto v = *min_value[TraitsSupport::get_traits()](EVE_FWD(rng), less);
    // We use user provided less to compare here (less(min, min) -> false but less(min, anything_else) - true).
    // Maybe we should use bit wise equality instead, would also work if everything is well behaived.
    return eve::algo::find_if_not[TraitsSupport::get_traits()](EVE_FWD(rng), bind_first{less, v});
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
//!   @var min_element
//!
//!   @brief SIMD version of `std::min_element`
//!
//!   @note if you just need a value and not position, use `eve::algo::min_value`.
//!
//!   By default unrolls by 4 and aligned all memory accesses.
//!
//!   @note for equivalent elements we return the first amoung equal.
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
//!      auto min_element(Rng&& rng, Less less) -> unaligned_iterator_t<Rng>;   // 1
//!
//!      template<relaxed_range Rng>
//!      auto min_element(Rng&& rng) -> unaligned_iterator_t<Rng>;            // 2
//!   }
//!   @endcode
//!
//!   1. Returns the position of a minimum value, according to less.
//!      If the range is empty - returns past the end.
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
//!   iterator to min element (end if the range is empty).
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/min.cpp}
//!
//!   @see `min_value`
//!   @see `max_element`
//!
//! @}
//================================================================================================
inline constexpr auto min_element = function_with_traits<min_element_>[default_simple_algo_traits];

}
