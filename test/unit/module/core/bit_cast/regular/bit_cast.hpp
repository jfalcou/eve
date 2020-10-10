//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_cast.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_andnot return type", EVE_TYPE)
{
  using ut_t = eve::detail::as_integer_t<T, unsigned>;
  using it_t = eve::detail::as_integer_t<T, signed>;

  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<it_t>()), it_t  );
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<ut_t>()), ut_t  );
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<T>()), T);
}

TTS_CASE_TPL("Check eve::bit_cast behavior", EVE_TYPE)
{
  using ut_t = eve::detail::as_integer_t<T, unsigned>;
  using it_t = eve::detail::as_integer_t<T, signed>;
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::bit_cast((T(0)), eve::as<it_t>()), it_t(0));
    TTS_EQUAL(eve::bit_cast((T(0)), eve::as<ut_t>()), ut_t(0));
    TTS_EQUAL(eve::bit_cast((T(0)), eve::as<T>()), (T(0)));

    TTS_EQUAL(eve::bit_cast(eve::allbits(eve::as<T>()), eve::as<it_t>()), eve::allbits(eve::as<it_t>()));
    TTS_EQUAL(eve::bit_cast(eve::allbits(eve::as<T>()), eve::as<ut_t>()), eve::allbits(eve::as<ut_t>()));

    if constexpr(sizeof(v_t)==4)
    {
      TTS_EQUAL(eve::bit_cast(T(1.f)       , eve::as<ut_t>()) , ut_t(0x3F800000) );
      TTS_EQUAL(eve::bit_cast((ut_t)(0x3F800000) , eve::as<T>()), (T(1.f))     );
    }
    else if constexpr(sizeof(v_t)==8)
    {
      TTS_EQUAL(eve::bit_cast(T(1.)      , eve::as<ut_t>()) , ut_t(0x3ff0000000000000ULL) );
      TTS_EQUAL(eve::bit_cast((ut_t)(0x3ff0000000000000ULL) , eve::as<T>()), (T(1.))     );
    }
  }

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::bit_cast((T(0)), eve::as<it_t>()), it_t(0));
    TTS_EQUAL(eve::bit_cast((T(0)), eve::as<ut_t>()), ut_t(0));
    TTS_EQUAL(eve::bit_cast(eve::allbits(eve::as<T>()), eve::as<it_t>()), eve::allbits(eve::as<it_t>()));
    TTS_EQUAL(eve::bit_cast(eve::allbits(eve::as<T>()), eve::as<ut_t>()), eve::allbits(eve::as<ut_t>()));
  }
}
