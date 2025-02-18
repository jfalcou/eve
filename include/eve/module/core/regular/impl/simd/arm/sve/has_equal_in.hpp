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

        // Because of the way we perform the match, we want to broadcast the needle to at least twice its initial size.
        // Say the needle occupies the first N lanes of the vector.
        // We can use a first svext to rotate the needle around, resulting in a vector with only the last N lanes active.
        // We can then use a second svext to select these lanes and append the first N lanes of the original needle to it.
        // This will result in a vector with the needle occupying the first 2N lanes.
        //
        // Example for SVE2-1024 with 512 bits worth of input data:
        // Haystack: [ H0 | H1 | H2 | H3 | UD | UD | UD | UD ]  Needle: [ N0 | N1 | N2 | N3 | UD | UD | UD | UD ]
        //
        // Step 1: Rotate the needle: [ UD | UD | UD | UD | N0 | N1 | N2 | N3 ]
        fw_t rotated_needle = svext(needle, needle, fundamental_cardinal_v<T> - N::value);


        // Step 2: Select from the needle and the rotated needle:
        // [ UD | UD | UD | UD | N0 | N1 | N2 | N3 ] [ N0 | N1 | N2 | N3 | UD | UD | UD | UD ]
        //                      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        //                     [ N0 | N1 | N2 | N3  |  N0 | N1 | N2 | N3 ]
        needle = svext(rotated_needle, needle, fundamental_cardinal_v<T> - N::value);

        // Step 3: Match the needle against the haystack.
        // [ H0 | H1 | H2 | H3 | UD | UD | UD | UD ]
        // [ N0 | N1 | N2 | N3 | N0 | N1 | N2 | N3 ]
        logical<fw_t> res = svmatch(sve_true<T>(), haystack, needle);

        // Step 4: rotate the needle by 128 bits and perform the match again until we have matched all the lanes.
        // GCC is capable of unrolling and breaking the dependency chain in this loop.
        //
        // [ H0 | H1 | H2 | H3 | UD | UD | UD | UD ] => [ H0 | H1 | H2 | H3 | UD | UD | UD | UD ] => ...
        // [ N1 | N2 | N3 | N0 | N1 | N2 | N3 | N0 ]    [ N2 | N3 | N0 | N1 | N2 | N3 | N0 | N1 ]
        for (size_t i = 16; i < byte_size; i += 16)
        {
          needle = svext(needle, needle, 16 / sizeof(T));
          res = logical_or(res, logical<fw_t>{ svmatch(sve_true<T>(), haystack, needle) });
        }

        // Cast back the result to the expected wide size.
        return simd_cast(res, as<logical<wide<T, N>>>());
      }
    }
    else
    {
      return has_equal_in.behavior(cpu_{}, opts, x, match_against, op);
    }
  }
}
