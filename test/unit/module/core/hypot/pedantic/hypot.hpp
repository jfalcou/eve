//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/hypot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check hypot return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)( v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(   T(0), v_t(0)), T);

  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(   T(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(   T(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(   T(0), v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(   T(0), v_t(0), v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)( v_t(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)( v_t(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)( v_t(0), v_t(0),   T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic_(eve::hypot) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(eve::nan(eve::as<T>())  , eve::Inf<T>())  , eve::Inf<T>());
    TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<T>()  , eve::nan(eve::as<T>()))  , eve::Inf<T>());
    TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(eve::nan(eve::as<v_t>()), eve::Inf<T>())  , eve::Inf<T>());
    TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<v_t>(), eve::nan(eve::as<T>()))  , eve::Inf<T>());
    TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(eve::nan(eve::as<T>())  , eve::Inf<v_t>()), eve::Inf<T>());
    TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<T>()  , eve::nan(eve::as<v_t>())), eve::Inf<T>());
  }

  auto tmax   = eve::Valmax<T>();
  auto vmax   = eve::Valmax<v_t>();
  auto sqrt2  = eve::Sqrt_2<T>();
  auto vsqrt2 = eve::Sqrt_2<v_t>();

  TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(tmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(T(0)  , tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(vmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(v_t(0), tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(tmax  , v_t(0)) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic_(eve::hypot)(T(0)  , vmax  ) , tmax);


  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(tmax/2, tmax/2), tmax/sqrt2, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(vmax/2, tmax/2), tmax/sqrt2, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(tmax/2, vmax/2), tmax/sqrt2, 0.5 );

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(v_t(-1), T(-1)), sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(v_t( 1), T( 1)), sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(v_t( 0), T( 0)), T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(vsqrt2, sqrt2) , T(2)  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T(-1), v_t(-1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T( 1), v_t( 1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T( 0), v_t( 0) ) , T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(sqrt2, vsqrt2  ) , T(2)  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T(-1), T(-1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T( 1), T( 1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T( 0), T( 0) ) , T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(sqrt2, sqrt2 ) , T(2)  , 0.5 );
}

TTS_CASE_TPL("Check pedantic_ 3 params eve::hypot behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<T>(), eve::Inf<T>(), eve::Inf<T>()), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<T>(), eve::Inf<T>(), eve::Inf<T>()), eve::Inf<T>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<v_t>(), eve::Inf<T>(), eve::Inf<T>()), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<v_t>(), eve::Inf<T>(), eve::Inf<T>()), eve::Inf<T>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<T>(), eve::Inf<v_t>(), eve::Inf<T>()), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<T>(), eve::Inf<v_t>(), eve::Inf<T>()), eve::Inf<T>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<T>(), eve::Inf<v_t>(), eve::Inf<v_t>()), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<T>(), eve::Inf<v_t>(), eve::Inf<v_t>()), eve::Inf<T>(), 0);

  }

  auto tmax   = eve::Valmax<T>();
  auto sqrt2  = eve::Sqrt_2<T>();

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(tmax , T(0)  , T(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T(0) , tmax  , T(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T(-1), T(-1) , sqrt2 ) , T(2), 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T( 1), T( 1) , sqrt2 ) , T(2), 0.5 );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T( 0), T( 0) , T( 0) ) , T(0), 0.5 );

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(T( 1), T( 1), T( 1)) , T(std::sqrt(v_t(3))), 0.5);
}
