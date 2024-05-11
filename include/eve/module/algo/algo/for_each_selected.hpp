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
#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/preprocess_range.hpp>
#include <eve/module/algo/algo/traits.hpp>
#include <eve/module/core.hpp>

namespace eve::algo
{

template<typename TraitsSupport> struct for_each_selected_ : TraitsSupport
{
  template<typename LoopBody, typename I> struct LoopBodyAdapter
  {
    LoopBody& loop_body;
    I         base;

    EVE_FORCEINLINE
    bool operator()(std::ptrdiff_t i) { return loop_body(base + i); }
  };

  template<typename P, typename LoopBody, typename ProcessedI, typename I> struct delegate
  {
    P          is_selected;
    LoopBody&  loop_body;
    bool       was_stopped;
    ProcessedI processed_first;
    I          first;

    EVE_FORCEINLINE I restore_iterator(const auto& it) { return first + (it - processed_first); }

    EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
    {
      auto loaded = eve::load[ignore](it);
      was_stopped = eve::iterate_selected[ignore](
          is_selected(loaded), LoopBodyAdapter<LoopBody, I> {loop_body, restore_iterator(it)});
      return was_stopped;
    }

    EVE_FORCEINLINE bool unrolled_step(auto arr)
    {
      return unroll_by_calling_single_step {}(arr, *this);
    }
  };

  template<relaxed_range Rng, typename P, irregular_predicate<unaligned_iterator_t<Rng>> LoopBody>
  EVE_FORCEINLINE bool operator()(Rng&& rng, P is_selected, LoopBody&& loop_body) const
  {
    if( rng.begin() == rng.end() ) return false;
    auto processed = preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));

    auto iteration =
        algo::for_each_iteration(processed.traits(), processed.begin(), processed.end());

    using ProcessedI = decltype(processed.begin());
    using I          = unaligned_iterator_t<Rng>;
    delegate<P, LoopBody, ProcessedI, I> d {
        is_selected, loop_body, false, processed.begin(), unalign(rng.begin())};
    iteration(d);
    return d.was_stopped;
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!  @var for_each_selected
//!
//!  @brief an algorithm to perform some scalar operation for every element, that matches a
//!  given SIMD predicate.
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/algo.hpp>
//!   @endcode
//!
//!   The scalar equivalent of this algorithm would be:
//!
//!   @code
//!   bool for_each_selected(std::ranges::forward_range auto&& r,
//!                          auto is_selected,
//!                          auto&& loop_body) {
//!     for (auto f = std::ranges::begin(r); f != std::ranges::end(r); ++f) {
//!       if (is_selected(*f) && loop_body(f)) {
//!         return true;
//!       }
//!     }
//!     return false;
//!   }
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve::algo
//!   {
//!     template<relaxed_range Rng, typename P, irregular_predicate<unaligned_iterator_t<Rng>> LoopBody>
//!     bool for_each_selected(Rng&& rng, P is_selected, LoopBody loop_body);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * rng - relaxed range which we iterate
//!    * is_selected - simd predicate to check values
//!    * loop_body - operation to perform for each value (should return true to break),
//!
//!   **Return value**
//!
//!   returns true iff the iteration was interrupted.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/for_each_selected.cpp}
//! @}
//================================================================================================

inline constexpr auto for_each_selected = function_with_traits<for_each_selected_>;

}
