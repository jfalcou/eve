//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

// This example was provided by @the-moisrex.
// In this example we will have a look at how we can use eve's conditional
// version of operations to implement a case-insensetive string comparison.
//
// NOTE: if we replace `eve::algo::equal` with `eve::algo::mismatch` with a modification
//       we can get lexicograpgical case-insesetive compare.

#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>

#include <cstdint>
#include <string_view>

namespace ascii
{
  struct
  {
    // Making this work for scalar is a bit tricky because scalar code tends to convert to ints alot.
    // So we are only doing wides.
    EVE_FORCEINLINE auto operator()(eve::wide<std::uint8_t> c) const
    {
      // eve::sub[condition](a, b) is an equivalent to `eve::if_else(condition, a - b, a)`
      // but it will also use masked instructions when those are avaliable.

      // Traditional `to_upper` is written like 'a' <= c && c <= 'z`.
      // However, we can utilize underflow(overflow?) when subtracting unsigned numbers.
      // c - 'a' <= 'z' -'a' if and only if 'a' <= c && c <= 'z'
      constexpr std::uint8_t alphabet_length = 'z' - 'a';
      constexpr std::uint8_t a_A_offset      = 'a' - 'A';

      return eve::sub[(c - std::uint8_t('a')) <= alphabet_length](c, a_A_offset);
    }

  } inline constexpr to_upper;

  bool iequals(std::string_view a, std::string_view b)
  {
    // `eve::algo::equals` requires that both of the input ranges are of the same size.
    // if they are not - the strings are not equal.
    if ( a.size() != b.size() ) return false;

    // converting them to uint8_t; because our to upper algorithm relies on unsigned integers.
    auto *f1 = reinterpret_cast<std::uint8_t const *>(a.begin());
    auto *l1 = reinterpret_cast<std::uint8_t const *>(a.end());
    auto *f2 = reinterpret_cast<std::uint8_t const *>(b.begin());

    return eve::algo::equal(eve::algo::as_range(f1, l1),
                            f2,
                            [](eve::wide<std::uint8_t> a, eve::wide<std::uint8_t> b)
                            {
                              // convert both to uppercase and then check if they're equal
                              return to_upper(a) == to_upper(b);
                            });
  }
}


// -----------------------

#include "test.hpp"

TTS_CASE("to_upper")
{
  for (std::uint8_t x = 0; x != 128; ++x)
  {
    std::uint8_t expected = x;
    if (std::uint8_t('a') <= x && x <= std::uint8_t('z')) expected = x - std::uint8_t('a' - 'A');
    std::uint8_t actual = ascii::to_upper(eve::wide<std::uint8_t>(x)).get(0);
    TTS_EQUAL(expected, actual);
  }
};

TTS_CASE("IEquals, basics")
{
  TTS_EQUAL(ascii::iequals("123 One Two aZ", "123 oNe TWo Az"), true);
  TTS_EQUAL(ascii::iequals("103 One Two aZ", "123 oNe TWo Az"), false);
  TTS_EQUAL(ascii::iequals("not the same size as", "123 oNe TWo Az"), false);
  TTS_EQUAL(ascii::iequals("Short", "SHorT"), true);
  TTS_EQUAL(ascii::iequals("Shor", "Short"), false);
};
