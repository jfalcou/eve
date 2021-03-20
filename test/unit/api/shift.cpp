//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/shl.hpp>
#include <eve/function/shr.hpp>

//================================================================================================
// random size values
//================================================================================================
inline auto const random_bits = []<typename T>(eve::as_<T>, auto& gen)
{
  using i_t = eve::as_integer_t<eve::element_type_t<T>>;
  eve::prng<i_t> dist(0,8*sizeof(i_t)-1);

  std::array<i_t,eve::cardinal_v<T>> d;
  std::for_each(d.begin(), d.end(), [&](auto& e) { e = dist(gen); });

  return d;
};

//==================================================================================================
// type tests
//==================================================================================================
auto type_tests = []<typename T>(T)
{
  using i_t = eve::as_integer_t<T>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EXPR_IS( T() << i_t() , T);
  TTS_EXPR_IS( T() << vi_t(), T);
  TTS_EXPR_IS( T() >> i_t() , T);
  TTS_EXPR_IS( T() >> vi_t(), T);
};

EVE_TEST_BED( "Check behavior of shift operators on eve::wide"
            , eve::test::simd::integers
            , eve::test::generate ( eve::test::no_data)
            , type_tests
            );

//==================================================================================================
// wide tests
//==================================================================================================
auto simd_tests = []<typename T, typename I>(T a0, I s)
{
  TTS_EQUAL( (a0 << s), T([&](auto i, auto) { return eve::shl(a0.get(i), s.get(i)); }) );
  TTS_EQUAL( (a0 >> s), T([&](auto i, auto) { return eve::shr(a0.get(i), s.get(i)); }) );
};

EVE_TEST_BED( "Check behavior of shift operators on eve::wide"
            , eve::test::simd::integers
            , eve::test::generate(eve::test::randoms(-50,50), random_bits)
            , simd_tests
            );

//==================================================================================================
// Scalar tests
//==================================================================================================
auto mixed_tests  = []<typename T, typename I>(T a0, I s)
{
  auto val = s.get(0);
  TTS_EQUAL( (a0 >> val), T([&](auto i, auto) { return eve::shr(a0.get(i), val); }) );
  TTS_EQUAL( (a0 << val), T([&](auto i, auto) { return eve::shl(a0.get(i), val); }) );
};

EVE_TEST_BED( "Check behavior of shift operators on wide and scalars"
            , eve::test::simd::integers
            , eve::test::generate(eve::test::randoms(-50,50), random_bits)
            , mixed_tests
            );
