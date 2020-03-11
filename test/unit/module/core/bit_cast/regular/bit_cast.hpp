//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_cast.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_andnot return type")
{
  using ut_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;
  using it_t = eve::detail::as_integer_t<EVE_TYPE, signed>;

  TTS_EXPR_IS(eve::bit_cast(EVE_TYPE(), eve::as<it_t>()), it_t  );
  TTS_EXPR_IS(eve::bit_cast(EVE_TYPE(), eve::as<ut_t>()), ut_t  );
  TTS_EXPR_IS(eve::bit_cast(EVE_TYPE(), eve::as<EVE_TYPE>()), (EVE_TYPE));
}

TTS_CASE("Check eve::bit_cast behavior")
{
  using ut_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;
  using it_t = eve::detail::as_integer_t<EVE_TYPE, signed>;

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::bit_cast((EVE_TYPE(0)), eve::as<it_t>()), it_t(0));
    TTS_EQUAL(eve::bit_cast((EVE_TYPE(0)), eve::as<ut_t>()), ut_t(0));
    TTS_EQUAL(eve::bit_cast((EVE_TYPE(0)), eve::as<EVE_TYPE>()), (EVE_TYPE(0)));

    TTS_EQUAL(eve::bit_cast(eve::Allbits<EVE_TYPE>(), eve::as<it_t>()), eve::Allbits<it_t>());
    TTS_EQUAL(eve::bit_cast(eve::Allbits<EVE_TYPE>(), eve::as<ut_t>()), eve::Allbits<ut_t>());
    TTS_IEEE_EQUAL(eve::bit_cast(eve::Allbits<EVE_TYPE>(),eve::as_<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));

    if constexpr(sizeof(EVE_VALUE)==4)
    {
      TTS_EQUAL(eve::bit_cast((EVE_TYPE)(1.f)       , eve::as<ut_t>()) , ut_t(0x3F800000) );
      TTS_EQUAL(eve::bit_cast((ut_t)(0x3F800000) , eve::as<EVE_TYPE>()), (EVE_TYPE(1.f))     );
    }
    else if constexpr(sizeof(EVE_VALUE)==8)
    {
      TTS_EQUAL(eve::bit_cast((EVE_TYPE)(1.)      , eve::as<ut_t>()) , ut_t(0x3ff0000000000000ULL) );
      TTS_EQUAL(eve::bit_cast((ut_t)(0x3ff0000000000000ULL) , eve::as<EVE_TYPE>()), (EVE_TYPE(1.))     );
    }
  }

  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::bit_cast((EVE_TYPE(0)), eve::as<it_t>()), it_t(0));
    TTS_EQUAL(eve::bit_cast((EVE_TYPE(0)), eve::as<ut_t>()), ut_t(0));
    TTS_EQUAL(eve::bit_cast(eve::Allbits<EVE_TYPE>(), eve::as<it_t>()), eve::Allbits<it_t>());
    TTS_EQUAL(eve::bit_cast(eve::Allbits<EVE_TYPE>(), eve::as<ut_t>()), eve::Allbits<ut_t>());
  }
}

