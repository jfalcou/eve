//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/lpnorm.hpp>
#include <eve/function/cbrt.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check lpnorm return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,    T(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,  v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,    T(0), v_t(0)), T);

  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,    T(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,    T(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,    T(0), v_t(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,    T(0), v_t(0), v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,  v_t(0),   T(0),   T(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,  v_t(0),   T(0), v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic(eve::lpnorm)(2,  v_t(0), v_t(0),   T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::lpnorm) behavior", EVE_TYPE)
{
 using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::nan(eve::as<T>())  , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<T>())  , eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::nan(eve::as<v_t>()), eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<v_t>()), eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::nan(eve::as<T>())  , eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<T>())  , eve::nan(eve::as<v_t>())), eve::inf(eve::as<T>()));
  }

  auto tmax   = eve::valmax(eve::as<T>());
  auto vmax   = eve::valmax(eve::as<v_t>());
  auto cbrt4  = eve::cbrt(T(4));
  auto cbrt2  = eve::cbrt(T(2));

  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, T(0)  , tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, vmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, v_t(0), tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax  , v_t(0)) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, T(0)  , vmax  ) , tmax);


 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax/2, tmax/2), tmax/cbrt4, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, vmax/2, tmax/2), tmax/cbrt4, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax/2, vmax/2), tmax/cbrt4, 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, v_t(-1), T(-1)), cbrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, v_t( 1), T( 1)), cbrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, v_t( 0), T( 0)), T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, cbrt2, cbrt2) , cbrt4  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(-1), v_t(-1) ) , cbrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), v_t( 1) ) , cbrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 0), v_t( 0) ) , T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, cbrt2, cbrt2  ) , cbrt4  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(-1), T(-1) ) , cbrt2, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), T( 1) ) , cbrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 0), T( 0) ) , T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, cbrt2, cbrt2 ) , cbrt4  , 0.5 );
}

TTS_CASE_TPL("Check pedantic 3 params eve::lpnorm behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()), 0);

  }

  auto tmax   = eve::valmax(eve::as<T>());
  auto cbrt3  = eve::cbrt(T(3));

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax , T(0)  , T(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(0) , tmax  , T(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(-1), T(-1) , T(-1) ) , cbrt3, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), T( 1) , T(1)  ) , cbrt3, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 0), T( 0) , T( 0) ) , T(0), 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), T( 1), T( 1), T( 1)) , eve::cbrt(T(4)), 0.5);
}


TTS_CASE_TPL("Check eve::pedantic(eve::lpnorm) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::nan(eve::as<T>())  , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>())  , eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::nan(eve::as<v_t>()), eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<v_t>()), eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::nan(eve::as<T>())  , eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>())  , eve::nan(eve::as<v_t>())), eve::inf(eve::as<T>()));
  }

  auto tmax   = eve::valmax(eve::as<T>());
  auto vmax   = eve::valmax(eve::as<v_t>());
  auto sqrt2  = eve::sqrt_2(eve::as<T>());
  auto vsqrt2 = eve::sqrt_2(eve::as<v_t>());

  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, T(0)  , tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, vmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, v_t(0), tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax  , v_t(0)) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, T(0)  , vmax  ) , tmax);


  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax/2, tmax/2), tmax/sqrt2, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, vmax/2, tmax/2), tmax/sqrt2, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax/2, vmax/2), tmax/sqrt2, 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, v_t(-1), T(-1)), sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, v_t( 1), T( 1)), sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, v_t( 0), T( 0)), T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, vsqrt2, sqrt2) , T(2)  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(-1), v_t(-1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), v_t( 1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 0), v_t( 0) ) , T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, sqrt2, vsqrt2  ) , T(2)  , 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(-1), T(-1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1) ) , sqrt2 , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 0), T( 0) ) , T(0)  , 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, sqrt2, sqrt2 ) , T(2)  , 0.5 );
 }

TTS_CASE_TPL("Check pedantic 3 params eve::lpnorm behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);

    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>()), eve::inf(eve::as<v_t>()), eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()), 0);

  }

  auto tmax   = eve::valmax(eve::as<T>());
  auto sqrt2  = eve::sqrt_2(eve::as<T>());

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax , T(0)  , T(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(0) , tmax  , T(0)  ) , tmax, 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(-1), T(-1) , sqrt2 ) , T(2), 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1) , sqrt2 ) , T(2), 0.5 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 0), T( 0) , T( 0) ) , T(0), 0.5 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1), T( 1)) , T(std::sqrt(v_t(3))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1), T( 1), T( 1)) , T(2), 0.5);
}
