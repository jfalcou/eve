//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/concepts.hpp>
#include <eve/module/algo/algo/for_each.hpp>
#include <eve/module/algo/algo/traits.hpp>

#include <concepts>

namespace eve::algo
{

  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!  @var fill
  //!  @brief a version of `std::fill`
  //! @}
  //================================================================================================
  template <typename TraitsSupport>
  struct fill_ : TraitsSupport
  {
    template <typename Rng>
    struct fill_delegate
    {
      using processed_range =
        decltype(preprocess_range(std::declval<TraitsSupport>().get_traits(),
                 std::declval<Rng>()));
      using I = decltype(std::declval<processed_range>().begin());
      using N = iterator_cardinal_t<I>;

      eve::wide<value_type_t<I>, N> wide_value;

      EVE_FORCEINLINE explicit fill_delegate(auto value) :
        wide_value(value_type_t<I>(value))
      {
      }

      EVE_FORCEINLINE void operator()(auto it, eve::relative_conditional_expr auto ignore) const
      {
        eve::store[ignore](wide_value, it);
      }
    };

    template <relaxed_range Rng, std::convertible_to<value_type_t<Rng>> T>
    EVE_FORCEINLINE void operator()(Rng&& rng, T x) const
    {
      for_each[TraitsSupport::get_traits()](EVE_FWD(rng), fill_delegate<Rng>{x});
    }
  };

  inline constexpr auto fill = function_with_traits<fill_>[default_simple_algo_traits];
}
