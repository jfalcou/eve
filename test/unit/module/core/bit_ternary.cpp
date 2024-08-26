//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_ternary return type" , eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<T, unsigned>;
  constexpr std::integral_constant<std::uint8_t, 0x0f>  ik;
  TTS_EXPR_IS(eve::bit_ternary(ik, T() ,   T() ,   T() ), T);
  TTS_EXPR_IS(eve::bit_ternary(ik, T() ,   T() , v_t()), T);
  TTS_EXPR_IS(eve::bit_ternary(ik,  T() , v_t() ,   T()), T);
  TTS_EXPR_IS(eve::bit_ternary(ik,i_t() ,   T() ,   T()), i_t);
  TTS_EXPR_IS(eve::bit_ternary(ik,i_t() ,   T() , v_t()), i_t);
  TTS_EXPR_IS(eve::bit_ternary(ik,i_t() , v_t() ,   T()), i_t);
};

TTS_CASE_WITH("Check behavior of bit_ternary",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(-1000, +1000),
                            tts::randoms(-1000, +1000),
                            tts::randoms(-1000, +1000)))
  <typename T>(T const& a, T const& b, T const& c)
{
  using eve::as;
  using eve::bit_xor;
  using eve::bit_or;
  using eve::bit_and;
  using eve::bit_notand;
  using eve::bit_notor;
  using eve::bit_ornot;
  using eve::bit_not;
  using eve::bit_select;
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x00>(), a, b, c),  eve::zero(eve::as(a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x01>(), a, b, c),  bit_not(bit_or(a, b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x02>(), a, b, c),  bit_notand(bit_or(a, b), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x03>(), a, b, c),  bit_not(bit_or(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x04>(), a, b, c),  bit_notand(bit_or(a, c), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x05>(), a, b, c),  bit_not(bit_or(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x06>(), a, b, c),  bit_notand(a,bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x07>(), a, b, c),  bit_not(bit_or(a, bit_and(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x08>(), a, b, c),  bit_and(bit_notand(a, b), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x09>(), a, b, c),  bit_not(bit_or(a, bit_xor(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x0a>(), a, b, c),  bit_notand(a, c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x0b>(), a, b, c),  bit_notand(a, bit_notor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x0c>(), a, b, c),  bit_notand(a, b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x0d>(), a, b, c),  bit_notand(a, bit_ornot(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x0e>(), a, b, c),  bit_notand(a, bit_or(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x0f>(), a, b, c),  bit_not(a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x10>(), a, b, c),  bit_notand(bit_or(b, c), a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x11>(), a, b, c),  bit_not(bit_or(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x12>(), a, b, c),  bit_notand(b, bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x13>(), a, b, c),  bit_not(bit_or(b, bit_and(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x14>(), a, b, c),  bit_notand(c, bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x15>(), a, b, c),  bit_not(bit_or(c, bit_and(a, b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x16>(), a, b, c),  bit_or(bit_notand(bit_or(b, c), a), bit_notand(a, bit_xor(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x17>(), a, b, c),  bit_or(bit_not(bit_or(b, c)), bit_notand(a,bit_xor(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x18>(), a, b, c),  bit_and(bit_xor(a, c), bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x19>(), a, b, c),  bit_notand(bit_and(a, b), bit_not(bit_xor(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x1a>(), a, b, c),  bit_notand(bit_and(a, b), bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x1b>(), a, b, c),  bit_or(bit_notand(a, c), bit_notand(c, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x1c>(), a, b, c),  bit_notand(bit_and(a, c), bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x1d>(), a, b, c),  bit_or(bit_notand(a, b),  bit_notand(b, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x1e>(), a, b, c),  bit_xor(a, bit_or(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x1f>(), a, b, c),  bit_not(bit_and(a, bit_or(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x20>(), a, b, c),  bit_and(bit_notand(b, a), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x21>(), a, b, c),  bit_not(bit_or(b, bit_xor(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x22>(), a, b, c),  bit_notand(b, c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x23>(), a, b, c),  bit_notand(b, bit_notor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x24>(), a, b, c),  bit_and(bit_xor(a, b), bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x25>(), a, b, c),  bit_notand(bit_and(a, b), bit_xor(a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x26>(), a, b, c),  bit_notand(bit_and(a, b), bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x27>(), a, b, c),  bit_or(bit_notand(b, c), bit_notand(c, bit_not(a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x28>(), a, b, c),  bit_and(c, bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x29>(), a, b, c),  bit_or(bit_and(c, bit_xor(b, a)), bit_notand(c, bit_not(bit_or(b, a)))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x2a>(), a, b, c),  bit_notand(bit_and(b, a), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x2b>(), a, b, c),  bit_or(bit_notand(bit_and(b, a), c), bit_notand(c,bit_not( bit_or(b, a)))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x2c>(), a, b, c),  bit_and(bit_or(b, c), bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x2d>(), a, b, c),  bit_xor(a, bit_or(b, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x2e>(), a, b, c),  bit_xor(bit_or(b, c), bit_and(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x2f>(), a, b, c),  bit_or(bit_notand(b, c), bit_not(a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x30>(), a, b, c),  bit_notand(b, a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x31>(), a, b, c),  bit_notand(b,bit_ornot(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x32>(), a, b, c),  bit_notand(b, bit_or(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x33>(), a, b, c),  bit_not(b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x34>(), a, b, c),  bit_notand(bit_and(b, c), bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x35>(), a, b, c),  bit_or(bit_notand(b, a), bit_notand(a,bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x36>(), a, b, c),  bit_xor(b, bit_or(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x37>(), a, b, c),  bit_not(bit_and(b, bit_or(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x38>(), a, b, c),  bit_and(bit_or(a, c), bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x39>(), a, b, c),  bit_xor(b, bit_or(a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x3a>(), a, b, c),  bit_or(bit_notand(b, a), bit_notand(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x3b>(), a, b, c),  bit_or(bit_notand(a, c), bit_not(b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x3c>(), a, b, c),  bit_xor(b, a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x3d>(), a, b, c),  bit_or(bit_xor(a, b), bit_not(bit_or(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x3e>(), a, b, c),  bit_or(bit_notand(a, c), bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x3f>(), a, b, c),  bit_not(bit_and(b, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x40>(), a, b, c),  bit_and(bit_notand(c, a), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x41>(), a, b, c),  bit_not(bit_or(c, bit_xor(b, a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x42>(), a, b, c),  bit_and(bit_xor(a, c), bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x43>(), a, b, c),  bit_notand(bit_and(a, c), bit_xor(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x44>(), a, b, c),  bit_notand(c, b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x45>(), a, b, c),  bit_notand(c, bit_or(bit_not(a), b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x46>(), a, b, c),  bit_notand(bit_and(a, c), bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x47>(), a, b, c),  bit_or(bit_notand(c, b), bit_notand(b, bit_not(a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x48>(), a, b, c),  bit_and(b, bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x49>(), a, b, c),  bit_or(bit_and(b, bit_xor(a, c)), bit_notand(b, bit_not(bit_or(a, c)))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x4a>(), a, b, c),  bit_and(bit_or(b, c), bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x4b>(), a, b, c),  bit_xor(a, bit_or(bit_not(b), c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x4c>(), a, b, c),  bit_notand(bit_and(a, c), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x4d>(), a, b, c),  bit_or(bit_notand(bit_and(a, c), b), bit_notand(b, bit_not(bit_or(a, c)))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x4e>(), a, b, c),  bit_or(bit_notand(a, c), bit_notand(c, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x4f>(), a, b, c),  bit_or(bit_not(a), bit_notand(c, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x50>(), a, b, c),  bit_notand(c, a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x51>(), a, b, c),  bit_notand(c, bit_or(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x52>(), a, b, c),  bit_notand(bit_and(b, c), bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x53>(), a, b, c),  bit_or(bit_notand(c, a), bit_notand(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x54>(), a, b, c),  bit_notand(c, bit_or(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x55>(), a, b, c),  bit_not(c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x56>(), a, b, c),  bit_xor(c, bit_or(b, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x57>(), a, b, c),  bit_not(bit_and(c, bit_or(b, a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x58>(), a, b, c),  bit_and(bit_or(a, b), bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x59>(), a, b, c),  bit_xor(c, bit_or(a,bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x5a>(), a, b, c),  bit_xor(c, a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x5b>(), a, b, c),  bit_or(bit_xor(a, c), bit_not(bit_or(a, b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x5c>(), a, b, c),  bit_or(bit_notand(c, a), bit_notand(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x5d>(), a, b, c),  bit_or(bit_notand(a, b), bit_not(c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x5e>(), a, b, c),  bit_or(bit_notand(c, b), bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x5f>(), a, b, c),  bit_not(bit_and(c, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x60>(), a, b, c),  bit_and(a, bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x61>(), a, b, c),  bit_or(bit_and(a, bit_xor(b, c)), bit_notand(a, bit_not(bit_or(b, c)))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x62>(), a, b, c),  bit_and(bit_or(a, c), bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x63>(), a, b, c),  bit_xor(b, bit_or(bit_not(a), c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x64>(), a, b, c),  bit_and(bit_or(a, b), bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x65>(), a, b, c),  bit_xor(c, bit_or(bit_not(a), b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x66>(), a, b, c),  bit_xor(c, b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x67>(), a, b, c),  bit_or(bit_xor(b, c), bit_not(bit_or(a, b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x68>(), a, b, c),  bit_or(bit_and(a,bit_xor(b, c)), bit_notand(a, bit_and(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x69>(), a, b, c),  bit_not(bit_xor(a, b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x6a>(), a, b, c),  bit_xor(c, bit_and(b, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x6b>(), a, b, c),  bit_or(bit_notand(a, c), bit_xor(bit_not(a), b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x6c>(), a, b, c),  bit_xor(b, bit_and(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x6d>(), a, b, c),  bit_or(bit_notand(a, b), bit_xor(bit_not(a), b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x6e>(), a, b, c),  bit_or(bit_notand(a, b), bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x6f>(), a, b, c),  bit_or(bit_xor(b, c), bit_not(a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x70>(), a, b, c),  bit_notand(bit_and(b, c), a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x71>(), a, b, c),  bit_or(bit_not(bit_or(b, c)), bit_and(a, bit_xor(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x72>(), a, b, c),  bit_or(bit_notand(b, c), bit_notand(c, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x73>(), a, b, c),  bit_or(bit_notand(c, a), bit_not(b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x74>(), a, b, c),  bit_or(bit_notand(c, b), bit_notand(b, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x75>(), a, b, c),  bit_or(bit_notand(b, a), bit_not(c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x76>(), a, b, c),  bit_or(bit_notand(b, a), bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x77>(), a, b, c),  bit_not(bit_and(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x78>(), a, b, c),  bit_xor(a, bit_and(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x79>(), a, b, c),  bit_or(bit_notand(b, a), bit_xor(bit_not(b), bit_xor(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x7a>(), a, b, c),  bit_or(bit_notand(b, a), bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x7b>(), a, b, c),  bit_or(bit_xor(a, c), bit_not(b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x7c>(), a, b, c),  bit_or(bit_notand(c, a), bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x7d>(), a, b, c),  bit_or(bit_xor(a, b), bit_not(c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x7e>(), a, b, c),  bit_or(bit_xor(a, b), bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x7f>(), a, b, c),  bit_not(bit_and(a, b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x80>(), a, b, c),  bit_and(a, b, c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x81>(), a, b, c),  bit_notand(bit_xor(a, c), bit_xor(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x82>(), a, b, c),  bit_notand(bit_xor(b, a), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x83>(), a, b, c),  bit_notand(bit_xor(a, b), bit_or(bit_not(a), c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x84>(), a, b, c),  bit_notand(bit_xor(a, c), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x85>(), a, b, c),  bit_notand(bit_xor(a, c), bit_or(b, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x86>(), a, b, c),  bit_and(bit_or(b, c),  bit_xor(c, a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x87>(), a, b, c),  bit_not(bit_xor(a, bit_and(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x88>(), a, b, c),  bit_and(c, b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x89>(), a, b, c),  bit_notand(bit_xor(b, c), bit_notor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x8a>(), a, b, c),  bit_notand(bit_notand(b, a), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x8b>(), a, b, c),  bit_or(bit_and(b, c),  bit_notand(b, bit_not(a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x8c>(), a, b, c),  bit_notand(bit_notand(c, a), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x8d>(), a, b, c),  bit_or(bit_and(c, b), bit_notand(c,bit_not(a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x8e>(), a, b, c),  bit_or(bit_and(b, c), bit_notand(a, bit_xor(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x8f>(), a, b, c),  bit_or(bit_and(b, c), bit_not(a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x90>(), a, b, c),  bit_notand(bit_xor(b, c), a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x91>(), a, b, c),  bit_notand(bit_xor(b, c),  bit_ornot(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x92>(), a, b, c),  bit_and(bit_or(a, c),  bit_xor(c, a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x93>(), a, b, c),  bit_not(bit_xor(b, bit_and(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x94>(), a, b, c),  bit_and(bit_or(a, b),  bit_xor(b, a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x95>(), a, b, c),  bit_not(bit_xor(c, bit_and(b, a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x96>(), a, b, c),  bit_xor(a, b, c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x97>(), a, b, c),  bit_or(bit_notand(bit_xor(b, c), a), bit_notand(a, bit_not(bit_and(b, c)))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x98>(), a, b, c),  bit_notand(bit_xor(b, c), bit_or(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x99>(), a, b, c),  bit_not(bit_xor(c, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x9a>(), a, b, c),  bit_xor(bit_notand(b, a), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x9b>(), a, b, c),  bit_or(bit_notand(a, c), bit_xor(b, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x9c>(), a, b, c),  bit_xor(bit_notand(c, a), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x9d>(), a, b, c),  bit_or(bit_notand(a, b), bit_xor(b, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x9e>(), a, b, c),  bit_or(bit_and(b, c), bit_xor(c, a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0x9f>(), a, b, c),  bit_not(bit_and(a, bit_xor(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa0>(), a, b, c),  bit_and(c, a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa1>(), a, b, c),  bit_notand(bit_xor(a, c), bit_ornot(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa2>(), a, b, c),  bit_notand(bit_notand(a, b), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa3>(), a, b, c),  bit_or(bit_and(a, c), bit_notand(a,bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa4>(), a, b, c),  bit_notand( bit_xor(a, c), bit_or(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa5>(), a, b, c),  bit_not(bit_xor(c, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa6>(), a, b, c),  bit_xor(bit_notand(a, b), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa7>(), a, b, c),  bit_or(bit_notand(b, c), bit_xor(a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa8>(), a, b, c),  bit_and(c, bit_or(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xa9>(), a, b, c),  bit_not(bit_xor(c, bit_or(b, a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xaa>(), a, b, c),  c);
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xab>(), a, b, c),  bit_or(c, bit_not(bit_or(b, a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xac>(), a, b, c),  bit_select(a, c, b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xad>(), a, b, c),  bit_or(bit_and(b, c), bit_xor(a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xae>(), a, b, c),  bit_or(c, bit_notand(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xaf>(), a, b, c),  bit_ornot(c, a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb0>(), a, b, c),  bit_notand(bit_notand(c, b), a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb1>(), a, b, c),  bit_select(c, a, bit_not(b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb2>(), a, b, c),  bit_select(b, bit_and(a, c), bit_or(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb3>(), a, b, c),  bit_or(bit_and(a, c), bit_not(b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb4>(), a, b, c),  bit_xor(bit_notand(c, b), a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb5>(), a, b, c),  bit_or(bit_notand(b, a), bit_xor(a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb6>(), a, b, c),  bit_or(bit_and(a, c), bit_xor(a, b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb7>(), a, b, c),  bit_not(bit_and(b, bit_xor(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb8>(), a, b, c),  bit_or(bit_and(b, c), bit_notand(b, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xb9>(), a, b, c),  bit_or(bit_and(a, c), bit_xor(b, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xba>(), a, b, c),  bit_or(bit_notand(b, a), c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xbb>(), a, b, c),  bit_or(c, bit_not(b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xbc>(), a, b, c),  bit_or(bit_and(a, c), bit_xor(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xbd>(), a, b, c),  bit_or(bit_xor(a, b), bit_xor(a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xbe>(), a, b, c),  bit_or(c, bit_xor(b, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xbf>(), a, b, c),  bit_or(c,bit_not(bit_and(b, a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc0>(), a, b, c),  bit_and(b, a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc1>(), a, b, c),  bit_notand(bit_xor(a, b), bit_or(a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc2>(), a, b, c),  bit_notand(bit_xor(b, a), bit_or(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc3>(), a, b, c),  bit_not(bit_xor(b, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc4>(), a, b, c),  bit_notand(bit_notand(a, c), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc5>(), a, b, c),  bit_or(bit_and(a, b), bit_notand(a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc6>(), a, b, c),  bit_xor(bit_notand(a, c), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc7>(), a, b, c),  bit_or(bit_notand(c, b), bit_xor(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc8>(), a, b, c),  bit_and(b, bit_or(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xc9>(), a, b, c),  bit_not(bit_xor(b, bit_or(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xca>(), a, b, c),  bit_or(bit_and(a, b), bit_notand(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xcb>(), a, b, c),  bit_or(bit_and(b, c), bit_xor(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xcc>(), a, b, c),  b);
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xcd>(), a, b, c),  bit_or(b, bit_not(bit_or(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xce>(), a, b, c),  bit_or(bit_notand(a, c), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xcf>(), a, b, c),  bit_or(b,bit_not(a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd0>(), a, b, c),  bit_notand(bit_notand(b, c), a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd1>(), a, b, c),  bit_or(bit_not(bit_or(b, c)), bit_and(a, b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd2>(), a, b, c),  bit_xor(bit_notand(b, c), a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd3>(), a, b, c),  bit_or(bit_notand(c, a), bit_xor(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd4>(), a, b, c),  bit_or(bit_notand(c, b),  bit_notand(bit_xor(b, c), a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd5>(), a, b, c),  bit_or(bit_and(a, b), bit_not(c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd6>(), a, b, c),  bit_or(bit_and(a, b), bit_xor(b, a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd7>(), a, b, c),  bit_not(bit_and(c, bit_xor(b, a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd8>(), a, b, c),  bit_or(bit_and(c, b), bit_notand(c, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xd9>(), a, b, c),  bit_or(bit_and(a, b), bit_xor(b, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xda>(), a, b, c),  bit_or(bit_and(a, b), bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xdb>(), a, b, c),  bit_or(bit_xor(a, c), bit_xor(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xdc>(), a, b, c),  bit_or(bit_notand(c, a), b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xdd>(), a, b, c),  bit_or(b, bit_not(c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xde>(), a, b, c),  bit_or(b, bit_xor(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xdf>(), a, b, c),  bit_or(b, bit_not(bit_and(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe0>(), a, b, c),  bit_and(a, bit_or(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe1>(), a, b, c),  bit_not(bit_xor(a, bit_or(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe2>(), a, b, c),  bit_or(bit_and(b, a),  bit_notand(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe3>(), a, b, c),  bit_or(bit_and(a, c), bit_xor(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe4>(), a, b, c),  bit_select(c, a, b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe5>(), a, b, c),  bit_or(bit_and(a, b), bit_xor(a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe6>(), a, b, c),  bit_or(bit_and(a, b), bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe7>(), a, b, c),  bit_or(bit_xor(b, c), bit_xor(a, bit_not(b))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe8>(), a, b, c),  bit_or(bit_and(b, c), bit_and(a, bit_xor(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xe9>(), a, b, c),  bit_or(bit_and(a, b), bit_xor(b, a, bit_not(c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xea>(), a, b, c),  bit_or(c, bit_and(b, a)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xeb>(), a, b, c),  bit_or(c, bit_not( bit_xor(b, a))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xec>(), a, b, c),  bit_or(b, bit_and(a, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xed>(), a, b, c),  bit_or(b, bit_not(bit_xor(a, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xee>(), a, b, c),  bit_or(c, b));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xef>(), a, b, c),  bit_or(b, bit_or(bit_not(a), c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf0>(), a, b, c),  a);
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf1>(), a, b, c),  bit_or(a, bit_not(bit_or(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf2>(), a, b, c),  bit_or(bit_notand(b, c), a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf3>(), a, b, c),  bit_or(a, bit_not(b)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf4>(), a, b, c),  bit_or(bit_notand(c, b), a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf5>(), a, b, c),  bit_or(a, bit_not(c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf6>(), a, b, c),  bit_or(a, bit_xor(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf7>(), a, b, c),  bit_or(a, bit_not(bit_and(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf8>(), a, b, c),  bit_or(a, bit_and(b, c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xf9>(), a, b, c),  bit_or(a, bit_not(bit_xor(b, c))));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xfa>(), a, b, c),  bit_or(c, a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xfb>(), a, b, c),  bit_or(a, bit_or(bit_not(b), c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xfc>(), a, b, c),  bit_or(b, a));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xfd>(), a, b, c),  bit_or(a, b, bit_not(c)));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xfe>(), a, b, c),  bit_or(a, b, c));
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<std::uint8_t, 0xff>(), a, b, c),  eve::allbits(as(a)));
};
