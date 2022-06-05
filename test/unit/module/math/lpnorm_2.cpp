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
// lpnorm(2, ...) tests
//==================================================================================================
EVE_TEST( "Check behavior of lpnorm on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0.0, eve::valmax)
                             , eve::test::randoms(0.0, eve::valmax)
                             , eve::test::randoms(0.5, 2.0)
                             , eve::test::randoms(0.5, 2.0)
                             , eve::test::randoms(0.0, eve::valmax)
                             , eve::test::randoms(0.5, 2.0)
                             )
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4, T const& a5)
{
  using eve::detail::map;

  TTS_ULP_EQUAL(eve::lpnorm(2, a0, a1)      , eve::hypot(a0, a1), 2);
  TTS_ULP_EQUAL(eve::lpnorm(2, a2, a3)      , eve::hypot(a2, a3), 2);
  
  
  
  
  TTS_ULP_EQUAL(eve::lpnorm(2, a0, a1, a4)      , eve::hypot(a0, a1, a4), 2);
  TTS_ULP_EQUAL(eve::lpnorm(2, a2, a3, a5)      , eve::hypot(a2, a3, a5), 2);
};

#if !defined(EVE_NO_DENORMALS)
EVE_TEST_TYPES( "Check behavior of pedantic(lpnorm(2, ...))"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  const auto tmax   = eve::valmax(eve::as<T>());
  const auto vmax   = eve::valmax(eve::as<v_t>());
  const auto sqrt2  = eve::sqrt_2(eve::as<T>());
  const auto vsqrt2 = eve::sqrt_2(eve::as<v_t>());
  const auto sqrt3  = T(1.732050807568877);

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::nan(eve::as<T>())  , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>())  , eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::nan(eve::as<v_t>()), eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<v_t>()), eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::nan(eve::as<T>())  , eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>())  , eve::nan(eve::as<v_t>())), eve::inf(eve::as<T>()));
  }


  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, T(0)  , tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, vmax  , T(0)  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, v_t(0), tmax  ) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax  , v_t(0)) , tmax);
  TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, T(0)  , vmax  ) , tmax);


  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax/2, tmax/2), tmax/sqrt2, 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, vmax/2, tmax/2), tmax/sqrt2, 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax/2, vmax/2), tmax/sqrt2, 1.0 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, v_t(-1), T(-1)), sqrt2 , 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, v_t( 1), T( 1)), sqrt2 , 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, v_t( 0), T( 0)), T(0)  , 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, vsqrt2, sqrt2) , T(2)  , 1.0 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(-1), v_t(-1) ) , sqrt2 , 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), v_t( 1) ) , sqrt2 , 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 0), v_t( 0) ) , T(0)  , 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, sqrt2, vsqrt2  ) , T(2)  , 1.0 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(-1), T(-1) ) , sqrt2 , 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1) ) , sqrt2 , 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 0), T( 0) ) , T(0)  , 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, sqrt2, sqrt2 ) , T(2)  , 1.0 );


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

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax , T(0)  , T(0)  ) , tmax, 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(0) , tmax  , T(0)  ) , tmax, 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(-1), T(-1) , sqrt2 ) , T(2), 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1) , sqrt2 ) , T(2), 1.0 );
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 0), T( 0) , T( 0) ) , T(0), 1.0 );

  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1), T( 1)) , sqrt3, 0.5);
  TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1), T( 1), T( 1)) , T(2), 0.5);
};
#endif
