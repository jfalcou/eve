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
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_equal.hpp>
#include <eve/module/core/regular/combine.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N, typename Pred>
  constexpr EVE_FORCEINLINE logical<wide<T, N>> has_equal_in_(EVE_REQUIRES(sve2_), O const& opts, wide<T, N> x, wide<T, N> match_against, Pred op) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr (std::same_as<Pred, is_equal_t<eve::options<>>> && match(c, category::int8, category::uint8, category::int16, category::uint16))
    {
      constexpr auto byte_size = sizeof(T) * N::value;

      // note: svmatch only works in lanes of 128 bits.
      if constexpr (byte_size == 16)
      {
        return svmatch(sve_true<T>(), x, match_against);
      }
      else if constexpr (byte_size < 16)
      {
        // We have less than 128 bits, we need broadcast the input values to at least 128 bits worth of space.
        // We could just build a wide of 128 bits here, but using the native size is important as it will allow the shuffle
        // operation used to build the second operand to be compiled down to a single "broadcast move" instruction.
        // There is no need to broadcast the values inside the first operand because we will just adjust the mask to only
        // consider the active lanes.
        using fw_t = wide<T, fundamental_cardinal_t<T>>;
        fw_t fx = fw_t{x};
        fw_t fmatch_against = shuffle(fw_t{match_against}, eve::as_pattern([](auto i, auto) { return i % N::value; }));

        return svmatch(sve_true_until<T>(N::value), fx, fmatch_against);
      }
      else
      {
        // If we got here, we can assume that the size of the input is a multiple of 128 bits.
        auto [xh, xl] = x.slice();
        auto [mh, ml] = match_against.slice();

        auto h = logical_or(has_equal_in.behavior(current_api, opts, xh, mh, op),
                            has_equal_in.behavior(current_api, opts, xh, ml, op));

        auto l = logical_or(has_equal_in.behavior(current_api, opts, xl, mh, op),
                            has_equal_in.behavior(current_api, opts, xl, ml, op));

        return logical<wide<T, N>>{h, l};
      }
    }
    else
    {
      return has_equal_in.behavior(cpu_{}, opts, x, match_against, op);
    }
  }
}
