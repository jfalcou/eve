//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/minmag.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::pedantic(eve::minmag) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::pedantic(eve::minmag)(T(0)  , T(0) ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::minmag)(v_t(0), T(0) ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::minmag)(T(0)  , v_t(0)) , T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::minmag) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::pedantic(eve::minmag)(T(0), T(0)), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(T(0), T(1)), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(T(1), T(0)), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(T(1), T(1)), T(1));

  TTS_EQUAL(eve::pedantic(eve::minmag)(v_t(0), T(0)), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(v_t(0), T(1)), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(v_t(1), T(0)), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(v_t(1), T(1)), T(1));

  TTS_EQUAL(eve::pedantic(eve::minmag)(T(0), v_t(0)), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(T(0), v_t(1)), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(T(1), v_t(0)), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(T(1), v_t(1)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(eve::nan(eve::as<T>())  , T(1)  ), eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(eve::nan(eve::as<v_t>()), T(1)  ), eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(eve::nan(eve::as<T>())  , v_t(1)), eve::nan(eve::as<T>()) );

    TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(T(1)  , eve::nan(eve::as<T>())  ), T(1) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(v_t(1), eve::nan(eve::as<T>())  ), T(1) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(T(1)  , eve::nan(eve::as<v_t>())), T(1) );
  }

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::pedantic(eve::minmag)(static_cast<T>(-3), T(2)), T(2));
    TTS_EQUAL(eve::pedantic(eve::minmag)(static_cast<T>(-1), T(2)), static_cast<T>(-1));
    TTS_EQUAL(eve::pedantic(eve::minmag)(static_cast<T>(-2), T(2)), static_cast<T>(-2));

    TTS_EQUAL(eve::pedantic(eve::minmag)(static_cast<T>(-3), T(2)), T(2));
    TTS_EQUAL(eve::pedantic(eve::minmag)(static_cast<T>(-1), T(2)), static_cast<T>(-1));
    TTS_EQUAL(eve::pedantic(eve::minmag)(static_cast<T>(-2), T(2)), static_cast<T>(-2));

    TTS_EQUAL(eve::pedantic(eve::minmag)(static_cast<T>(-3), T(2)), T(2));
    TTS_EQUAL(eve::pedantic(eve::minmag)(static_cast<T>(-1), T(2)), static_cast<T>(-1));
    TTS_EQUAL(eve::pedantic(eve::minmag)(static_cast<T>(-2), T(2)), static_cast<T>(-2));
  }
}
