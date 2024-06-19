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
  struct keep_if_ : TraitsSupport
  {
    template <typename UnalignedI, typename P>
    struct delegate
    {
      explicit delegate(UnalignedI out, P p) : out(out), p(p) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
      {
        auto loaded  = eve::load[ignore](it);
        auto mask    = p(loaded);
        auto density = density_for_compress_copy<typename TraitsSupport::traits_type>();
        out          = compress_copy[unsafe][density][ignore](it, loaded, mask, out);
        return false;
      }

      template <typename I, std::size_t size>
      EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
      {
        array_map(arr, call_single_step(this));
        return false;
      }

      UnalignedI out;
      P p;
    };

    template <relaxed_range Rng, typename P>
    EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
    {
      if (rng.begin() == rng.end()) return unalign(rng.begin());

      auto processed = preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));

      auto iteration = algo::for_each_iteration(processed.traits(), processed.begin(), processed.end());
      auto out = iteration.base;
      delegate<unaligned_t<decltype(out)>, P> d{unalign(out), p};
      iteration(d);
      return unalign(rng.begin()) + (d.out - processed.begin());
    }
  };

  //================================================================================================
  //! @addtogroup algos
  //! @{
  //!   @var keep_if
  //!   @brief In-place version of `eve::algo::copy_if`
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/algo.hpp>
  //!   @endcode
  //!
  //!   Takes values that pass the predicate, and copies them to the beginning of the range.
  //!   Values past the returned sentinel are to be considered garbage.
  //!
  //!   Acts like an in-place version of `::copy_if`, or an eager version of filter.
  //!
  //!   **Tuning**
  //!
  //!   `::dense_output`/`::sparse_output`: if you expect very sparse output (one or two `true`s per register),
  //!   you can call `::keep_if[::sparse_output](...)` to optimize for that scenario.
  //!
  //!   @groupheader{Callable Signatures}
  //!   
  //!   @code
  //!   {
  //!     template<relaxed_range Rng, typename P>
  //!     auto keep_if(Rng&& rng, P p) -> unaligned_iterator_t<Rng>
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!    * `rng`: Range to modify
  //!    * `p`: SIMD predicate over elements of `rng`
  //!
  //!   **Return value**
  //!
  //!   Iterator past the last written element.
  //!
  //!   @see `copy_if`
  //!   @see `remove_if`
  //!
  //! @}
  //================================================================================================
  inline constexpr auto keep_if = function_with_traits<keep_if_>[no_traits];
}
