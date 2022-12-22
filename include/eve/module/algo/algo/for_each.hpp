//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/array_utils.hpp>
#include <eve/module/algo/algo/common_forceinline_lambdas.hpp>
#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/preprocess_range.hpp>
#include <eve/module/algo/algo/traits.hpp>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!  @var for_each
  //!  @brief a basic for_each algorithm.
  //!    * The operation is called with `iterator` and `ignore`.
  //!    * Result of the operation is ignored.
  //!    * Operation is passed by value.
  //!    * There is no default traits.
  //!    * We do not return anything.
  //!    * The unrolling just calls the single step.
  //!    * Will align by default.
  //!
  //!    If you you have a more advanced unrolling, consider using the `for_each_iteration`.
  //!
  //!   **Required header:** `#include <eve/module/algo/algo/for_each.hpp>`
  //! @}
  //================================================================================================

  template <typename TraitsSupport>
  struct for_each_ : TraitsSupport
  {
    template <typename Op>
    struct delegate
    {
      Op op;

      explicit delegate(Op op) : op(op) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
      {
        op(it, ignore);
        return false;
      }

      template<typename I, std::size_t size>
      EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
      {
        array_map(arr, call_single_step(this));
        return false;
      }
    };

    template <relaxed_range Rng, typename Op>
    EVE_FORCEINLINE void operator()(Rng&& rng, Op op) const
    {
      auto processed = preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));
      if( processed.begin() == processed.end() ) return;

      delegate<Op> d{op};
      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
    }
  };

  inline constexpr auto for_each = function_with_traits<for_each_>;
}
