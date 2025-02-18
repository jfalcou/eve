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
#include <eve/module/core/regular/rotate.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N, typename Pred>
  constexpr EVE_FORCEINLINE logical<wide<T, N>> has_equal_in_(EVE_REQUIRES(sve2_), O const& opts, wide<T, N> x, wide<T, N> match_against, Pred op) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr (std::same_as<Pred, is_equal_t<eve::options<>>> && match(c, category::int8, category::uint8, category::int16, category::uint16))
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
        // We have less than 128 bits, we need broadcast the input values to at least 128 bits worth of space.
        // We could just build a wide of 128 bits here, but using the native size is important as it will allow the shuffle
        // operation used to build the second operand to be compiled down to a single "broadcast move" instruction.
        // There is no need to broadcast the values inside the first operand because we will just adjust the mask to only
        // consider the active lanes.
        fw_t haystack{x};
        fw_t needle = shuffle(fw_t{match_against}, eve::as_pattern([](auto i, auto) { return i % N::value; }));

        return svmatch(sve_true_until<T>(N::value), haystack, needle);
      }
      else
      {
        // If we got here, we can assume that the size of the input is a multiple of 128 bits.
        // We can use svmatch and rotate the needle to ensure that we match every 128-bits lanes with eatch other.
        fw_t haystack{x};
        fw_t needle{match_against};

        // std::cout << "\n\nbyte_size: " << byte_size << std::endl;
        // std::cout << "x: " << x << std::endl;
        // std::cout << "base_needle: " << match_against << std::endl;


        // rotate the needle by half
        fw_t rotated_needle = svext(needle, needle, fundamental_cardinal_v<T> - N::value);

        // std::cout << "rotated_needle: " << rotated_needle << std::endl;

        // concat the high part of the needle with the low part of the rotated needle
        needle = svext(rotated_needle, needle, fundamental_cardinal_v<T> - N::value);

        // std::cout << "broadcast_needle: " << needle << std::endl;


        // shuffle_v2(needle, eve::as_pattern([](auto i, auto) { return (i + N::value); }));

        logical<fw_t> res = svmatch(sve_true<T>(), haystack, needle);

        for (size_t i = 16; i < byte_size; i += 16)
        {
          needle = rotate(needle, eve::index<16 / sizeof(T)>);
          res = logical_or(res, logical<fw_t>{ svmatch(sve_true<T>(), haystack, needle) });
          // std::cout << "rotation by " << i << " " << std::endl;
          // std::cout << "match_against: " << match_against << std::endl;
          // std::cout << "res: " << res << std::endl;

        }

        // std::cout << std::endl;

        return simd_cast(res, as<logical<wide<T, N>>>());

        // logical<wide<T, N>> res = svmatch(mask, x, match_against);

        // // std::cout << "\n\nbyte_size: " << byte_size << std::endl;
        // // std::cout << "x: " << x << std::endl;
        // // std::cout << "match_against: " << match_against << std::endl;

        // for (size_t i = 16; i < byte_size; i += 16)
        // {
        //   match_against = rotate(match_against, eve::index<16 / sizeof(T)>);
        //   // match_against = shuffle(match_against, eve::as_pattern([](auto j, auto) { return (j + (16 / sizeof(T))) % N::value; }));
        //   res = logical_or(res, logical<wide<T, N>>{ svmatch(mask, x, match_against) });
        //   // std::cout << "rotation by " << i << " " << std::endl;
        //   // std::cout << "match_against: " << match_against << std::endl;
        //   // std::cout << "res: " << res << std::endl;

        // }

        // // std::cout << std::endl;

        // return res;
      }
    }
    else
    {
      return has_equal_in.behavior(cpu_{}, opts, x, match_against, op);
    }
  }
}
