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
#include <eve/module/algo/algo/concepts.hpp>
#include <eve/module/algo/algo/common_forceinline_lambdas.hpp>
#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/preprocess_range.hpp>
#include <eve/module/algo/algo/traits.hpp>

#include <array>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct transform_keep_if_ : TraitsSupport
  {
    template <typename UnalignedI, typename Func>
    struct delegate
    {
      explicit delegate(UnalignedI out, Func func) : out(out), func(func) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
      {
        auto loaded       = eve::load[ignore](it);
        auto [vals, mask] = func(loaded);
        out               = compress_store[unsafe][ignore](vals, mask, out);
        return false;
      }

      template <typename I, std::size_t size>
      EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
      {
        array_map(arr, call_single_step(this));
        return false;
      }

      UnalignedI out;
      Func func;
    };

    template <relaxed_range Rng, typename Func>
    EVE_FORCEINLINE auto operator()(Rng&& rng, Func func) const
    {
      if (rng.begin() == rng.end()) return unalign(rng.begin());

      auto processed = preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));

      auto iteration = algo::for_each_iteration(processed.traits(), processed.begin(), processed.end());
      auto out = iteration.base;
      delegate<unaligned_t<decltype(out)>, Func> d{unalign(out), func};
      iteration(d);
      return unalign(rng.begin()) + (d.out - processed.begin());
    }
  };

  //================================================================================================
  //! @addtogroup algos
  //! @{
  //!   @var transform_keep_if
  //!   @brief In-place version of `eve::algo::transform_copy_if`
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/algo.hpp>
  //!   @endcode
  //!
  //!   Transforms the range but only keeps the elements that pass a certain predicate.
  //!
  //!   @note
  //!   If the scalar operation is cheap enough, `::keep_if` + `views::map` might be slightly faster.
  //!
  //!   @note See `::transform_copy_if` and `::keep_if` for more details.
  //!
  //!   @groupheader{Callable Signatures}
  //!   
  //!   @code
  //!   {
  //!     template<relaxed_range Rng, typename Func>
  //!     auto transform_keep_if(Rng&& rng, Func func) -> unaligned_iterator_t<Rng>
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!    * `rng`: Range to modify
  //!    * `func`: Function that takes elements from `rng` as SIMD registers and returns a pair of:
  //!        - the transformed values
  //!        - a logical mask
  //!
  //!   **Return value**
  //!
  //!   Iterator past the last written element.
  //!
  //!   @see `keep_if`
  //!   @see `transform_copy_if`
  //!   @see `transform_inplace`
  //!   @see `views::map`
  //!
  //! @}
  //================================================================================================
  inline constexpr auto transform_keep_if = function_with_traits<transform_keep_if_>[no_traits];
}
