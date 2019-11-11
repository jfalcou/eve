//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/extract.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check extract return type")
{
  using i_t = eve::detail::as_integer_t<Value, signed>;
  using u_t = eve::detail::as_integer_t<Value, unsigned>;

  TTS_EXPR_IS(eve::extract(Type(), i_t()), Value);
  TTS_EXPR_IS(eve::extract(Type(), u_t()), Value);
  TTS_EXPR_IS(eve::extract(Type(), int()), Value);
}

TTS_CASE("Check eve::extract behavior on arithmetic types")
{
  TTS_EQUAL(eve::extract(Type(42), 0), Value(42));

#if defined(EVE_SIMD_TESTS)
  Type arg;

  for(int i=0; i< Cardinal; ++i)
    arg[i] = static_cast<Value>(1+i);

  for(int i=0; i< Cardinal; ++i)
    TTS_EQUAL(eve::extract(arg, i), static_cast<Value>(1+i));
#endif
}

TTS_CASE("Check eve::extract behavior on logical types")
{
  using eve::logical;

  TTS_EQUAL(eve::extract(logical<Type>(42), 0), true  );
  TTS_EQUAL(eve::extract(logical<Type>( 0), 0), false );

#if defined(EVE_SIMD_TESTS)
  logical<Type> arg;

  for(int i=0; i< Cardinal; ++i)
    arg[i] = ((1+i) % 2) == 0;

  for(int i=0; i< Cardinal; ++i)
    TTS_EQUAL(eve::extract(arg, i), ((1+i) % 2) == 0);
#endif

}
