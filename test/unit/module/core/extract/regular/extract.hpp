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

TTS_CASE_TPL("Check extract return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::detail::as_integer_t<v_t, signed>;
  using u_t = eve::detail::as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::extract(T(), i_t()), v_t);
  TTS_EXPR_IS(eve::extract(T(), u_t()), v_t);
  TTS_EXPR_IS(eve::extract(T(), int()), v_t);
}

TTS_CASE_TPL("Check eve::extract behavior on arithmetic types", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::extract(T(42), 0), v_t(42));

#if defined(EVE_SIMD_TESTS)
  T arg;

  for(int i=0; i< EVE_CARDINAL; ++i)
    arg.set(i, static_cast<v_t>(1+i));

  for(int i=0; i< EVE_CARDINAL; ++i)
    TTS_EQUAL(eve::extract(arg, i), static_cast<v_t>(1+i));
#endif
}

TTS_CASE_TPL("Check eve::extract behavior on logical types", EVE_TYPE)
{
  using eve::logical;

  TTS_EQUAL(eve::extract(logical<T>(42), 0), true  );
  TTS_EQUAL(eve::extract(logical<T>( 0), 0), false );

#if defined(EVE_SIMD_TESTS)
  logical<T> arg;

  for(int i=0; i< EVE_CARDINAL; ++i)
    arg.set(i, ((1+i) % 2) == 0);

  for(int i=0; i< EVE_CARDINAL; ++i)
    TTS_EQUAL(eve::extract(arg, i), ((1+i) % 2) == 0);
#endif
}
