//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/saturated/mul.hpp>

#include <type_traits>

TTS_CASE_TPL("Check saturated(eve::mul) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::saturated(eve::mul)(T()  , T()   ), T);
  TTS_EXPR_IS(eve::saturated(eve::mul)(v_t(), T()   ), T);
  TTS_EXPR_IS(eve::saturated(eve::mul)(T()  , v_t() ), T);
}

TTS_CASE_TPL("Check saturated(eve::mul) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::integral_value<T>)
  {
    auto tvmax = eve::valmax(eve::as<T>());
    auto vmax = eve::valmax(eve::as<v_t>());

    if constexpr(eve::signed_value<T>)
    {
      auto tvmin = eve::valmin(eve::as<T>());
      auto vmin = eve::valmin(eve::as<v_t>());

      TTS_EQUAL(eve::saturated(eve::mul)(tvmin , T(-2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax , T(-2)), tvmin);
      TTS_EQUAL(eve::saturated(eve::mul)(T(-1) , T( 0)), T(0) );
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax , tvmax), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax , tvmin), tvmin);

      TTS_EQUAL(eve::saturated(eve::mul)(vmax      , T(-2)), tvmin);
      TTS_EQUAL(eve::saturated(eve::mul)(vmin      , T(-2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)((v_t(-1)) , T( 0)), T(0) );
      TTS_EQUAL(eve::saturated(eve::mul)(vmax      , tvmax), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(vmax      , tvmin), tvmin);

      TTS_EQUAL(eve::saturated(eve::mul)(tvmax, v_t(-2)), tvmin);
      TTS_EQUAL(eve::saturated(eve::mul)(tvmin, v_t(-2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(T(-1), v_t( 0)), T(0) );
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax, vmax   ), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax, vmin   ), tvmin);
    }
    else
    {
      TTS_EQUAL(eve::saturated(eve::mul)(tvmax , T(2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(T(2), tvmax ), tvmax);

      TTS_EQUAL(eve::saturated(eve::mul)(vmax  , T(2)) , tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(v_t(2), tvmax), tvmax);

      TTS_EQUAL(eve::saturated(eve::mul)(tvmax, v_t(2)), tvmax);
      TTS_EQUAL(eve::saturated(eve::mul)(T(2) , vmax  ), tvmax);
    }
  }
  else
  {
    TTS_EQUAL(eve::saturated(eve::mul)(T( 0) , T(1)), T(0  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(T( 1) , T(1)), T(1  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(T(12) , T(4)), T(48 ) );

    TTS_EQUAL(eve::saturated(eve::mul)(v_t( 0) , T(1)), T(0  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(v_t( 1) , T(1)), T(1  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(v_t(12) , T(4)), T(48 ) );

    TTS_EQUAL(eve::saturated(eve::mul)(T( 0) , v_t(1)), T(0  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(T( 1) , v_t(1)), T(1  ) );
    TTS_EQUAL(eve::saturated(eve::mul)(T(12) , v_t(4)), T(48 ) );
  }
}
