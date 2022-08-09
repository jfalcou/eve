//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// type tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of shift operators on eve::wide", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  using i_t = eve::as_integer_t<T>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EXPR_IS( T() << i_t() , T);
  TTS_EXPR_IS( T() << vi_t(), T);
  TTS_EXPR_IS( T() >> i_t() , T);
  TTS_EXPR_IS( T() >> vi_t(), T);
};

//==================================================================================================
// wide tests
//==================================================================================================
TTS_CASE_WITH ( "Check behavior of shift operators on eve::wide"
              , eve::test::simd::integers
              , tts::generate(tts::randoms(-50,50), tts::random_bits())
              )
<typename T, typename I>(T a0, I s)
{
  TTS_EQUAL( (a0 << s), T([&](auto i, auto) { return eve::shl(a0.get(i), s.get(i)); }) );
  TTS_EQUAL( (a0 >> s), T([&](auto i, auto) { return eve::shr(a0.get(i), s.get(i)); }) );
};

//==================================================================================================
// Scalar tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of shift operators on wide and scalars"
        , eve::test::simd::integers
        , tts::generate(tts::randoms(eve::valmin,eve::valmax), tts::random_bits())
        )
<typename T, typename I>(T a0, I s)
{
  auto val = s.get(0);
  TTS_EQUAL( (a0 >> val), T([&](auto i, auto) { return a0.get(i) >> val; }) );
  TTS_EQUAL( (a0 << val), T([&](auto i, auto) { return a0.get(i) << val; }) );
};
