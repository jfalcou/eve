//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/hypot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check hypot return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)( v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   T(0), v_t(0)), T);

  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   T(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   T(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   T(0), v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   T(0), v_t(0), v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)( v_t(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)( v_t(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)( v_t(0), v_t(0),   T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::hypot) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::nan(eve::as<T>())  , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<T>())  , eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::nan(eve::as<v_t>()), eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<v_t>()), eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::nan(eve::as<T>())  , eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<T>())  , eve::nan(eve::as<v_t>())), eve::inf(eve::as<T>()));
  }

  auto tmax   = eve::valmax(eve::as<T>());
  auto vmax   = eve::valmax(eve::as<v_t>());
  auto sqrt2  = eve::sqrt_2(eve::as<T>());
  auto vsqrt2 = eve::sqrt_2(eve::as<v_t>());

  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(tmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(T(0)  , tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(vmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(v_t(0), tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(tmax  , v_t(0)) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(T(0)  , vmax  ) , tmax);


  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(tmax/2, tmax/2), tmax/sqrt2, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(vmax/2, tmax/2), tmax/sqrt2, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(tmax/2, vmax/2), tmax/sqrt2, 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(v_t(-1), T(-1)), sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(v_t( 1), T( 1)), sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(v_t( 0), T( 0)), T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(vsqrt2, sqrt2) , T(2)  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T(-1), v_t(-1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T( 1), v_t( 1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T( 0), v_t( 0) ) , T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(sqrt2, vsqrt2  ) , T(2)  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T(-1), T(-1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T( 1), T( 1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T( 0), T( 0) ) , T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(sqrt2, sqrt2 ) , T(2)  , 0.5 );
}

TTS_CASE_TPL("Check pedantic 3 params eve::hypot behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()), 0);

  }

  auto tmax   = eve::valmax(eve::as<T>());
  auto sqrt2  = eve::sqrt_2(eve::as<T>());

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(tmax , T(0)  , T(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T(0) , tmax  , T(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T(-1), T(-1) , sqrt2 ) , T(2), 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T( 1), T( 1) , sqrt2 ) , T(2), 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T( 0), T( 0) , T( 0) ) , T(0), 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(T( 1), T( 1), T( 1)) , T(std::sqrt(v_t(3))), 0.5);
}
