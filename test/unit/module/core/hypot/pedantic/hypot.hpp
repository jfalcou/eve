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

TTS_CASE("Check hypot return type")
{

  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   EVE_TYPE(0),   EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)( EVE_VALUE(0),   EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   EVE_TYPE(0), EVE_VALUE(0)), EVE_TYPE);

  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   EVE_TYPE(0),   EVE_TYPE(0),   EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   EVE_TYPE(0),   EVE_TYPE(0), EVE_VALUE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   EVE_TYPE(0), EVE_VALUE(0),   EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)(   EVE_TYPE(0), EVE_VALUE(0), EVE_VALUE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)( EVE_VALUE(0),   EVE_TYPE(0),   EVE_TYPE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)( EVE_VALUE(0),   EVE_TYPE(0), EVE_VALUE(0)), EVE_TYPE);
  TTS_EXPR_IS(eve::pedantic(eve::hypot)( EVE_VALUE(0), EVE_VALUE(0),   EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::pedantic(eve::hypot) behavior")
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::nan(eve::as<EVE_TYPE>())  , eve::inf(eve::as<EVE_TYPE>()))  , eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_TYPE>())  , eve::nan(eve::as<EVE_TYPE>()))  , eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::nan(eve::as<EVE_VALUE>()), eve::inf(eve::as<EVE_TYPE>()))  , eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_VALUE>()), eve::nan(eve::as<EVE_TYPE>()))  , eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::nan(eve::as<EVE_TYPE>())  , eve::inf(eve::as<EVE_VALUE>())), eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_TYPE>())  , eve::nan(eve::as<EVE_VALUE>())), eve::inf(eve::as<EVE_TYPE>()));
  }

  auto tmax   = eve::valmax(eve::as<EVE_TYPE>());
  auto vmax   = eve::valmax(eve::as<EVE_VALUE>());
  auto sqrt2  = eve::sqrt_2(eve::as<EVE_TYPE>());
  auto vsqrt2 = eve::sqrt_2(eve::as<EVE_VALUE>());

  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(tmax  , EVE_TYPE(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE(0)  , tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(vmax  , EVE_TYPE(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(EVE_VALUE(0), tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(tmax  , EVE_VALUE(0)) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE(0)  , vmax  ) , tmax);


  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(tmax/2, tmax/2), tmax/sqrt2, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(vmax/2, tmax/2), tmax/sqrt2, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(tmax/2, vmax/2), tmax/sqrt2, 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_VALUE(-1), EVE_TYPE(-1)), sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_VALUE( 1), EVE_TYPE( 1)), sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_VALUE( 0), EVE_TYPE( 0)), EVE_TYPE(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(vsqrt2, sqrt2) , EVE_TYPE(2)  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE(-1), EVE_VALUE(-1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE( 1), EVE_VALUE( 1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE( 0), EVE_VALUE( 0) ) , EVE_TYPE(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(sqrt2, vsqrt2  ) , EVE_TYPE(2)  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE(-1), EVE_TYPE(-1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE( 1), EVE_TYPE( 1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE( 0), EVE_TYPE( 0) ) , EVE_TYPE(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(sqrt2, sqrt2 ) , EVE_TYPE(2)  , 0.5 );
}

TTS_CASE("Check pedantic 3 params eve::hypot behavior")
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::inf(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::inf(eve::as<EVE_TYPE>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_VALUE>()), eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::inf(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_VALUE>()), eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::inf(eve::as<EVE_TYPE>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_VALUE>()), eve::inf(eve::as<EVE_TYPE>())), eve::inf(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_VALUE>()), eve::inf(eve::as<EVE_TYPE>())), eve::inf(eve::as<EVE_TYPE>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_VALUE>()), eve::inf(eve::as<EVE_VALUE>())), eve::inf(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_VALUE>()), eve::inf(eve::as<EVE_VALUE>())), eve::inf(eve::as<EVE_TYPE>()), 0);

  }

  auto tmax   = eve::valmax(eve::as<EVE_TYPE>());
  auto sqrt2  = eve::sqrt_2(eve::as<EVE_TYPE>());

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(tmax , EVE_TYPE(0)  , EVE_TYPE(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE(0) , tmax  , EVE_TYPE(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE(-1), EVE_TYPE(-1) , sqrt2 ) , EVE_TYPE(2), 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE( 1), EVE_TYPE( 1) , sqrt2 ) , EVE_TYPE(2), 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE( 0), EVE_TYPE( 0) , EVE_TYPE( 0) ) , EVE_TYPE(0), 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(EVE_TYPE( 1), EVE_TYPE( 1), EVE_TYPE( 1)) , EVE_TYPE(std::sqrt(EVE_VALUE(3))), 0.5);
}
