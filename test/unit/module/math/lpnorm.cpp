//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of lpnorm"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::lpnorm(int(), T(), T())  , T);
  TTS_EXPR_IS( eve::lpnorm(int(), v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::lpnorm(int(), T(), v_t()), T);
  TTS_EXPR_IS( eve::lpnorm(int(), v_t(), T()), T);
  TTS_EXPR_IS( eve::lpnorm(int(), T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::lpnorm(int(), T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::lpnorm(int(), v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::lpnorm(int(), T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::lpnorm(int(), v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::lpnorm(int(), v_t(), T(), v_t()) , T);

  TTS_EXPR_IS( eve::lpnorm(int(), v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// lpnorm  tests
//==================================================================================================

#if !defined(EVE_NO_DENORMALS)
EVE_TEST_TYPES( "Check behavior of pedantic(lpnorm(3, )"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
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

 const auto tmax   = eve::valmax(eve::as<T>());
 const auto vmax   = eve::valmax(eve::as<v_t>());
 const auto cbrt4  = T(1.587401051968199);
 const auto cbrt3  = T(1.442249570307408);
 const auto cbrt2  = T(1.259921049894873);

 TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax  , T(0)  ) , tmax);
 TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, T(0)  , tmax  ) , tmax);
 TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, vmax  , T(0)  ) , tmax);
 TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, v_t(0), tmax  ) , tmax);
 TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax  , v_t(0)) , tmax);
 TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(3, T(0)  , vmax  ) , tmax);

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax/2, tmax/2), tmax/cbrt4, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, vmax/2, tmax/2), tmax/cbrt4, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax/2, vmax/2), tmax/cbrt4, 1.0 );

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, v_t(-1), T(-1)), cbrt2 , 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, v_t( 1), T( 1)), cbrt2 , 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, v_t( 0), T( 0)), T(0)  , 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, cbrt2, cbrt2) , cbrt4  , 1.0 );

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(-1), v_t(-1) ) , cbrt2 , 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), v_t( 1) ) , cbrt2 , 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 0), v_t( 0) ) , T(0)  , 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, cbrt2, cbrt2  ) , cbrt4  , 1.0 );

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(-1), T(-1) ) , cbrt2, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), T( 1) ) , cbrt2 , 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 0), T( 0) ) , T(0)  , 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, cbrt2, cbrt2 ) , cbrt4  , 1.0 );

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

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax , T(0)  , T(0)  ) , tmax, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(0) , tmax  , T(0)  ) , tmax, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(-1), T(-1) , T(-1) ) , cbrt3, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), T( 1) , T(1)  ) , cbrt3, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 0), T( 0) , T( 0) ) , T(0), 1.0 );

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), T( 1), T( 1), T( 1)) , cbrt4, 1.0);

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), tmax , T(0)  , T(0)  ) , tmax, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T(0) , tmax  , T(0)  ) , tmax, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T(-1), T(-1) , T(-1) ) , cbrt3, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T( 1), T( 1) , T(1)  ) , cbrt3, 1.0 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T( 0), T( 0) , T( 0) ) , T(0), 1.0 );

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T( 1), T( 1), T( 1), T( 1)) , cbrt4, 1.0);
};

#endif
