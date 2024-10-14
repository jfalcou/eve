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
  struct remove_if_ : TraitsSupport
  {
    template <typename UnalignedI, typename P>
    struct delegate
    {
      explicit delegate(UnalignedI o, P pr) : out(o), p(pr) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
      {
        auto loaded = eve::load[ignore](it);
        auto mask   = !p(loaded); // we decied that ! can be optimized well enough
        auto density   = density_for_compress_copy<typename TraitsSupport::traits_type>();
        out            = compress_copy[unsafe][density][ignore](it, loaded, mask, out);
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
  //!  @var remove_if
  //!  @brief SIMD version of std::remove_if
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/algo.hpp>
  //!   @endcode
  //!
  //!   TODO: docs
  //!
  //!   @see keep_if
  //!   @see copy_if
  //!   @see transform_keep_if
  //!   @see transform_copy_if
  //!
  //! @}
  //================================================================================================
  inline constexpr auto remove_if = function_with_traits<remove_if_>[no_traits];

  template <typename TraitsSupport>
  struct remove_ : TraitsSupport
  {
    template <relaxed_range Rng, typename T>
    EVE_FORCEINLINE auto operator()(Rng&& rng, T v) const
    {
      return remove_if[TraitsSupport::get_traits()](EVE_FWD(rng), equal_to{v});
    }
  };

 //================================================================================================
  //! @addtogroup algos
  //! @{
  //!  @var remove
  //!  @brief SIMD version of std::remove
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/algo.hpp>
  //!   @endcode
  //!
  //!   TODO: docs
  //!
  //! @}
  //================================================================================================
  inline constexpr auto remove = function_with_traits<remove_>[no_traits];
}
