//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts.hpp>
#include <eve/algo/find.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/views/zip.hpp>
#include <eve/module/core.hpp>

#include <utility>

namespace eve::algo
{
template<typename TraitsSupport> struct mismatch_ : TraitsSupport
{
  template<zipped_range_pair R, typename P> EVE_FORCEINLINE auto operator()(R&& r, P p) const
  {
    return algo::find_if_not[TraitsSupport::get_traits()](EVE_FWD(r), apply_to_zip_pair {p});
  }

  template<zipped_range_pair R> EVE_FORCEINLINE auto operator()(R&& r) const
  {
    auto rezipped     = r[common_type];
    auto rezipped_res = operator()(rezipped, eve::is_equal);
    return unalign(r.begin()) + (rezipped_res - rezipped.begin());
  }

  template<typename R1, typename R2, typename P>
  requires zip_to_range<R1, R2> EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, P p) const
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
//!   @var mismatch
//!
//!   @brief a SIMD version of `std::mismatch`
//!
//!   Finds the point where two ranges are different (accepts anything that zips together as a range of 2 things).
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
//!     auto mismatch(Rng&& rng) -> unalinged_t<decltype(rng.begin())>;       // 1
//!
//!     template <zipped_range_pair Rng, typename P>
//!     auto mismatch(Rng&& rng, P p) -> unalinged_t<decltype(rng.begin())>;  // 2
//!
//!     template<typename R1, typename R2>
//!     auto mismatch(R1&& r1, R2&& r2) requires zip_to_range<R1, R2>         // 3
//!        -> eve::views::zip_iterator;
//!
//!     template<typename R1, typename R2, typename P>
//!     auto mismatch(R1&& r1, R2&& r2, P p) requires zip_to_range<R1, R2>    // 4
//!        -> eve::views::zip_iterator;
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
//!   `eve::views::zip_iterator` to the place where the mismatch happend.
//!   (if not found, will point past the end of both halves).
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/mismatch.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto mismatch = function_with_traits<mismatch_>[find_if.get_traits()];
}
