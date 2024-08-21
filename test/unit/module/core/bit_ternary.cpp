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
  constexpr std::integral_constant<int, 0x0f>  ik;
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
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x00>(), a, b, c),  eve::zero(eve::as(a)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x01>(), a, b, c),  bit_not(bit_or(a, b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x02>(), a, b, c),  bit_notand(bit_or(a, b), c));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x03>(), a, b, c),  bit_not(bit_or(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x04>(), a, b, c),  bit_notand(bit_or(a, c), b));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x05>(), a, b, c),  bit_not(bit_or(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x06>(), a, b, c),  bit_notand(a,bit_xor(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x07>(), a, b, c),  bit_not(bit_or(a, bit_and(b, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x08>(), a, b, c),  bit_and(bit_notand(a, b), c));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x09>(), a, b, c),  bit_not(bit_or(a, bit_xor(b, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x0a>(), a, b, c),  bit_notand(a, c));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x0b>(), a, b, c),  bit_notand(a, bit_notor(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x0c>(), a, b, c),  bit_notand(a, b));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x0d>(), a, b, c),  bit_notand(a, bit_ornot(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x0e>(), a, b, c),  bit_notand(a, bit_or(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x0f>(), a, b, c),  bit_not(a));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x10>(), a, b, c),  bit_notand(bit_or(b, c), a));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x11>(), a, b, c),  bit_not(bit_or(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x12>(), a, b, c),  bit_notand(b, bit_xor(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x13>(), a, b, c),  bit_not(bit_or(b, bit_and(a, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x14>(), a, b, c),  bit_notand(c, bit_xor(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x15>(), a, b, c),  bit_not(bit_or(c, bit_and(a, b))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x16>(), a, b, c),  bit_or(bit_notand(bit_or(b, c), a), bit_notand(a, bit_xor(b, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x17>(), a, b, c),  bit_or(bit_not(bit_or(b, c)), bit_notand(a,bit_xor(b, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x18>(), a, b, c),  bit_and(bit_xor(a, c), bit_xor(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x19>(), a, b, c),  bit_notand(bit_and(a, b), bit_not(bit_xor(b, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x1a>(), a, b, c),  bit_notand(bit_and(a, b), bit_xor(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x1b>(), a, b, c),  bit_or(bit_notand(a, c), bit_notand(c, bit_not(b))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x1c>(), a, b, c),  bit_notand(bit_and(a, c), bit_xor(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x1d>(), a, b, c),  bit_or(bit_notand(a, b),  bit_notand(b, bit_not(c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x1e>(), a, b, c),  bit_xor(a, bit_or(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x1f>(), a, b, c),  bit_not(bit_and(a, bit_or(b, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x20>(), a, b, c),  bit_and(bit_notand(b, a), c));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x21>(), a, b, c),  bit_not(bit_or(b, bit_xor(a, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x22>(), a, b, c),  bit_notand(b, c));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x23>(), a, b, c),  bit_notand(b, bit_notor(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x24>(), a, b, c),  bit_and(bit_xor(a, b), bit_xor(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x25>(), a, b, c),  bit_notand(bit_and(a, b), bit_xor(a, bit_not(c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x26>(), a, b, c),  bit_notand(bit_and(a, b), bit_xor(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x27>(), a, b, c),  bit_or(bit_notand(b, c), bit_notand(c, bit_not(a))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x28>(), a, b, c),  bit_and(c, bit_xor(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x29>(), a, b, c),  bit_or(bit_and(c, bit_xor(b, a)), bit_notand(c, bit_not(bit_or(b, a)))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x2a>(), a, b, c),  bit_notand(bit_and(b, a), c));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x2b>(), a, b, c),  bit_or(bit_notand(bit_and(b, a), c), bit_notand(c,bit_not( bit_or(b, a)))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x2c>(), a, b, c),  bit_and(bit_or(b, c), bit_xor(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x2d>(), a, b, c),  bit_xor(a, bit_or(b, bit_not(c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x2e>(), a, b, c),  bit_xor(bit_or(b, c), bit_and(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x2f>(), a, b, c),  bit_or(bit_notand(b, c), bit_not(a)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x30>(), a, b, c),  bit_notand(b, a));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x31>(), a, b, c),  bit_notand(b,bit_ornot(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x32>(), a, b, c),  bit_notand(b, bit_or(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x33>(), a, b, c),  bit_not(b));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x34>(), a, b, c),  bit_notand(bit_and(b, c), bit_xor(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x35>(), a, b, c),  bit_or(bit_notand(b, a), bit_notand(a,bit_not(c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x36>(), a, b, c),  bit_xor(b, bit_or(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x37>(), a, b, c),  bit_not(bit_and(b, bit_or(a, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x38>(), a, b, c),  bit_and(bit_or(a, c), bit_xor(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x39>(), a, b, c),  bit_xor(b, bit_or(a, bit_not(c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x3a>(), a, b, c),  bit_or(bit_notand(b, a), bit_notand(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x3b>(), a, b, c),  bit_or(bit_notand(a, c), bit_not(b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x3c>(), a, b, c),  bit_xor(b, a));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x3d>(), a, b, c),  bit_or(bit_xor(a, b), bit_not(bit_or(a, c))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x3e>(), a, b, c),  bit_or(bit_notand(a, c), bit_xor(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x3f>(), a, b, c),  bit_not(bit_and(b, a)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x40>(), a, b, c),  bit_and(bit_notand(c, a), b));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x41>(), a, b, c),  bit_not(bit_or(c, bit_xor(b, a))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x42>(), a, b, c),  bit_and(bit_xor(a, c), bit_xor(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x43>(), a, b, c),  bit_notand(bit_and(a, c), bit_xor(a, bit_not(b))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x44>(), a, b, c),  bit_notand(c, b));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x45>(), a, b, c),  bit_notand(c, bit_or(bit_not(a), b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x46>(), a, b, c),  bit_notand(bit_and(a, c), bit_xor(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x47>(), a, b, c),  bit_or(bit_notand(c, b), bit_notand(b, bit_not(a))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x48>(), a, b, c),  bit_and(b, bit_xor(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x49>(), a, b, c),  bit_or(bit_and(b, bit_xor(a, c)), bit_notand(b, bit_not(bit_or(a, c)))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x4a>(), a, b, c),  bit_and(bit_or(b, c), bit_xor(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x4b>(), a, b, c),  bit_xor(a, bit_or(bit_not(b), c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x4c>(), a, b, c),  bit_notand(bit_and(a, c), b));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x4d>(), a, b, c),  bit_or(bit_notand(bit_and(a, c), b), bit_notand(b, bit_not(bit_or(a, c)))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x4e>(), a, b, c),  bit_or(bit_notand(a, c), bit_notand(c, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x4f>(), a, b, c),  bit_or(bit_not(a), bit_notand(c, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x50>(), a, b, c),  bit_notand(c, a));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x51>(), a, b, c),  bit_notand(c, bit_or(a, bit_not(b))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x52>(), a, b, c),  bit_notand(bit_and(b, c), bit_xor(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x53>(), a, b, c),  bit_or(bit_notand(c, a), bit_notand(a, bit_not(b))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x54>(), a, b, c),  bit_notand(c, bit_or(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x55>(), a, b, c),  bit_not(c));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x56>(), a, b, c),  bit_xor(c, bit_or(b, a)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x57>(), a, b, c),  bit_not(bit_and(c, bit_or(b, a))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x58>(), a, b, c),  bit_and(bit_or(a, b), bit_xor(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x59>(), a, b, c),  bit_xor(c, bit_or(a,bit_not(b))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x5a>(), a, b, c),  bit_xor(c, a));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x5b>(), a, b, c),  bit_or(bit_xor(a, c), bit_not(bit_or(a, b))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x5c>(), a, b, c),  bit_or(bit_notand(c, a), bit_notand(a, b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x5d>(), a, b, c),  bit_or(bit_notand(a, b), bit_not(c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x5e>(), a, b, c),  bit_or(bit_notand(c, b), bit_xor(a, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x5f>(), a, b, c),  bit_not(bit_and(c, a)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x60>(), a, b, c),  bit_and(a, bit_xor(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x61>(), a, b, c),  bit_or(bit_and(a, bit_xor(b, c)), bit_notand(a, bit_not(bit_or(b, c)))));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x62>(), a, b, c),  bit_and(bit_or(a, c), bit_xor(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x63>(), a, b, c),  bit_xor(b, bit_or(bit_not(a), c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x64>(), a, b, c),  bit_and(bit_or(a, b), bit_xor(b, c)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x65>(), a, b, c),  bit_xor(c, bit_or(bit_not(a), b)));
//   TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x66>(), a, b, c),  bit_xor(c, b));                                                               
  TTS_EQUAL(eve::bit_ternary(std::integral_constant<int, 0x67>(), a, b, c),  bit_or(bit_xor(b, c), bit_not(bit_or(a, b)))); 

};
