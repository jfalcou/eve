//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/any_of.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/traits.hpp>
#include <eve/module/core.hpp>

#include <utility>

namespace eve::algo
{
template<typename TraitsSupport> struct none_of_ : TraitsSupport
{
  template<relaxed_range Rng, typename P> EVE_FORCEINLINE bool operator()(Rng&& rng, P p) const
  {
    return !any_of[TraitsSupport::get_traits()](EVE_FWD(rng), p);
  }
};
//================================================================================================
//! @addtogroup algos
//! @{
//!   @var none_of
//!
//!   @brief a SIMD version of `std::none_of`
//!
//!   Tests if none of the elements in the range match the predicate.
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
//!     bool none_of(Rng&& rng, P p);
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
//!   `true` if `p` returns `true` for no elements in the range, `false` otherwise.
//!    Returns `true` if the range is empty.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/none_of.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto none_of = function_with_traits<none_of_>;
}
