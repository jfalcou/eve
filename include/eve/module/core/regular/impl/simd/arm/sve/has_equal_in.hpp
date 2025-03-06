  //==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/callable.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_equal.hpp>
#include <eve/module/core/regular/combine.hpp>
#include <eve/module/core/regular/rotate.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N, typename Pred>
  constexpr EVE_FORCEINLINE logical<wide<T, N>> has_equal_in_(EVE_REQUIRES(sve2_), O const& opts, wide<T, N> x, wide<T, N> match_against, Pred op) noexcept
    requires (sve_abi<abi_t<T, N>> && (sizeof(T) <= 2) && integral_scalar_value<T>)
  {
    constexpr auto c = categorize<wide<T, N>>();
    
    if constexpr (!same_callable<Pred, eve::is_equal>)
    {
      return has_equal_in.behavior(cpu_{}, opts, x, match_against, op);
    }
    else
    {
      using fw_t = wide<T, fundamental_cardinal_t<T>>;
      constexpr auto byte_size = sizeof(T) * N::value;

      // note: svmatch only works in lanes of 128 bits.
      if constexpr (byte_size == 16)
      {
        return svmatch(sve_true<T>(), x, match_against);
      }
      else if constexpr (byte_size < 16)
      {
        const fw_t haystack{x};
        const fw_t needle = broadcast_lane(fw_t{match_against}, N{}, index<0>);

        return svmatch(keep_first(N::value).mask(as<fw_t>{}), haystack, needle);
      }
      else
      {
        auto all_rotations = try_each_group_position(match_against, eve::lane<16 / sizeof(T)>);
        
        auto all_tests = kumi::map([&](auto needle) -> eve::logical<wide<T, N>> {
            return svmatch(sve_true<T>(), x, needle);
        }, all_rotations);

        return kumi::fold_left(eve::logical_or, all_tests);
      }
    }
  }
}
