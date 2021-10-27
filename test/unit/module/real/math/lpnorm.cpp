//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/lpnorm.hpp>
#include <eve/function/cbrt.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/function/diff/lpnorm.hpp>
#include <eve/function/diff/hypot.hpp>
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
  TTS_ULP_EQUAL(eve::diff_1st(eve::lpnorm)(2, a0, a1), eve::diff_1st(eve::hypot)(a0, a1), 2);
  TTS_ULP_EQUAL(eve::diff_1st(eve::lpnorm)(2, a2, a3), eve::diff_1st(eve::hypot)(a2, a3), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::lpnorm)(2, a0, a1), eve::diff_2nd(eve::hypot)(a0, a1), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::lpnorm)(2, a2, a3), eve::diff_2nd(eve::hypot)(a2, a3), 2);
  TTS_ULP_EQUAL(eve::lpnorm(2, a0, a1, a4)      , eve::hypot(a0, a1, a4), 2);
  TTS_ULP_EQUAL(eve::lpnorm(2, a2, a3, a5)      , eve::hypot(a2, a3, a5), 2);
};

/// TODO : Fix lpnorm on arm v7
#if !defined(EVE_NO_DENORMALS)
EVE_TEST_TYPES( "Check behavior of pedantic(lpnorm)"
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

 auto cbrt3  = eve::cbrt(T(3));

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, tmax , T(0)  , T(0)  ) , tmax, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(0) , tmax  , T(0)  ) , tmax, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T(-1), T(-1) , T(-1) ) , cbrt3, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), T( 1) , T(1)  ) , cbrt3, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 0), T( 0) , T( 0) ) , T(0), 0.5 );

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(3, T( 1), T( 1), T( 1), T( 1)) , eve::cbrt(T(4)), 0.5);

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), tmax , T(0)  , T(0)  ) , tmax, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T(0) , tmax  , T(0)  ) , tmax, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T(-1), T(-1) , T(-1) ) , cbrt3, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T( 1), T( 1) , T(1)  ) , cbrt3, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T( 0), T( 0) , T( 0) ) , T(0), 0.5 );

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(T(3), T( 1), T( 1), T( 1), T( 1)) , eve::cbrt(T(4)), 0.5);

 if constexpr(eve::platform::supports_invalids)
 {
   TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::nan(eve::as<T>())  , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
   TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>())  , eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
   TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::nan(eve::as<v_t>()), eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()));
   TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<v_t>()), eve::nan(eve::as<T>()))  , eve::inf(eve::as<T>()));
   TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::nan(eve::as<T>())  , eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>()));
   TTS_IEEE_EQUAL(eve::pedantic(eve::lpnorm)(2, eve::inf(eve::as<T>())  , eve::nan(eve::as<v_t>())), eve::inf(eve::as<T>()));
 }

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

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, tmax , T(0)  , T(0)  ) , tmax, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(0) , tmax  , T(0)  ) , tmax, 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T(-1), T(-1) , sqrt2 ) , T(2), 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1) , sqrt2 ) , T(2), 0.5 );
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 0), T( 0) , T( 0) ) , T(0), 0.5 );

 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1), T( 1)) , T(std::sqrt(v_t(3))), 0.5);
 TTS_ULP_EQUAL(eve::pedantic(eve::lpnorm)(2, T( 1), T( 1), T( 1), T( 1)) , T(2), 0.5);
};
#endif
