//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/algo/all_of.hpp>
#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/views/zip.hpp>
#include <eve/module/core.hpp>

#include <utility>

namespace eve::algo
{
template<typename TraitsSupport> struct equal_ : TraitsSupport
{
  template<zipped_range_pair R, typename P> EVE_FORCEINLINE bool operator()(R&& r, P p) const
  {
    return algo::all_of[TraitsSupport::get_traits()](EVE_FWD(r), apply_to_zip_pair {p});
  }

  template<zipped_range_pair R> EVE_FORCEINLINE bool operator()(R&& r) const
  {
    return operator()(r[common_type], eve::is_equal);
  }

  template<typename R1, typename R2, typename P>
  requires zip_to_range<R1, R2> EVE_FORCEINLINE bool operator()(R1&& r1, R2&& r2, P p) const
  {
    return operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)), p);
  }

  template<typename R1, typename R2>
  requires zip_to_range<R1, R2> EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2) const
  {
    return operator()(views::zip(EVE_FWD(r1), EVE_FWD(r2)));
  }
};


//================================================================================================
//! @addtogroup algos
//! @{
//!   @var equal
//!
//!   @brief a SIMD version of `std::equal`
//!
//!   Tests wether two ranges are equal (accepts anything that zips together as a range of 2 things)
//!   By default aligns and unrolls 4 times.
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
//!
//!     template <zipped_range_pair Rng>
//!     bool equal(Rng&& rng);                                             // 1
//!
//!     template <zipped_range_pair Rng, typename P>
//!     bool equal(Rng&& rng, P p);                                        // 2
//!
//!     template<typename R1, typename R2>
//!     bool equal(R1&& r1, R2&& r2) requires zip_to_range<R1, R2>;        // 3
//!
//!     template<typename R1, typename R2, typename P>
//!     bool equal(R1&& r1, R2&& r2, P p) requires zip_to_range<R1, R2>;  // 4
//!   }
//!   @endcode
//!
//!   1. Compare both halves of zipped_range_pair for equality
//!   2. Compare both halves of zipped_range_pair for equivalence using predicate P
//!   3. Compare r1 and r2 that zip together to zip_range_pair for equality
//!   4. Compare r1 and r2 that zip together to zip_range_pair for equivalence using predicate P
//!
//!   @note 1. and 3. will convert to common type to do equality comparison if necessary
//!         to get the same for custom predicate, use `[common_type]` trait on your `zip`.
//!
//!   @note to better understand the `zip` interfaces,
//!         have a look at `examples/algorithms/using_existing/memcmp_...`
//!         or `examples/algorithms/using_existing/case_insensitive...`.
//!
//!   **Parameters**
//!
//!    * `rng`: zipped pair of 2 ranges to compare
//!    * 'r1`, `r2` - two separate components that `zip` to a `zipped_range_pair`
//!    * `p` - binary predicate for equivelence testing.
//!
//!   **Return value**
//!
//!   bool wether any values matched the predicate
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/equal.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto equal = function_with_traits<equal_>[all_of.get_traits()];
}
