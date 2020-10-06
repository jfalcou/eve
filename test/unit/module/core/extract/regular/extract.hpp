//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/extract.hpp>

TTS_CASE("Check extract return type")
{
  using i_t = eve::detail::as_integer_t<EVE_VALUE, signed>;
  using u_t = eve::detail::as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS(eve::extract(EVE_TYPE(), i_t()), EVE_VALUE);
  TTS_EXPR_IS(eve::extract(EVE_TYPE(), u_t()), EVE_VALUE);
  TTS_EXPR_IS(eve::extract(EVE_TYPE(), int()), EVE_VALUE);
}

TTS_CASE("Check eve::extract behavior on arithmetic types")
{
  TTS_EQUAL(eve::extract(EVE_TYPE(42), 0), EVE_VALUE(42));

#if defined(EVE_SIMD_TESTS)
  EVE_TYPE arg;

  for(int i=0; i< EVE_CARDINAL; ++i)
    arg.set(i, static_cast<EVE_VALUE>(1+i));

  for(int i=0; i< EVE_CARDINAL; ++i)
    TTS_EQUAL(eve::extract(arg, i), static_cast<EVE_VALUE>(1+i));
#endif
}

TTS_CASE("Check eve::extract behavior on logical types")
{
  using eve::logical;

  TTS_EQUAL(eve::extract(logical<EVE_TYPE>(42), 0), true  );
  TTS_EQUAL(eve::extract(logical<EVE_TYPE>( 0), 0), false );

#if defined(EVE_SIMD_TESTS)
  logical<EVE_TYPE> arg;

  for(int i=0; i< EVE_CARDINAL; ++i)
    arg.set(i, ((1+i) % 2) == 0);

  for(int i=0; i< EVE_CARDINAL; ++i)
    TTS_EQUAL(eve::extract(arg, i), (((1+i) % 2) == 0));
#endif
}
