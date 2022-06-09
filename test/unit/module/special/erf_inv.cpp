//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/special.hpp>
#include <boost/math/special_functions/erf.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of erf_inv"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::erf_inv(T())  , T);
  TTS_EXPR_IS( eve::erf_inv(v_t()), v_t);
};

//==================================================================================================
// erf_inv  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of erf_inv on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  using eve::erf_inv;
  using eve::as;
  TTS_ULP_EQUAL( erf_inv(a0),  map([](auto e){return boost::math::erf_inv(e);}, a0), 2);
  TTS_ULP_EQUAL(erf_inv(T(0.5)), T(boost::math::erf_inv(v_t(0.5))), 1. );

  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL ( erf_inv(T(eve::smallestposval(as<T>())))
                  , T(boost::math::erf_inv(eve::smallestposval(as<v_t>())))
                  , 0.5
                  );
  }

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(erf_inv(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(erf_inv(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(erf_inv(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(erf_inv(T(35)), eve::nan(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(erf_inv(T(-35)), eve::nan(eve::as<T>()), 0.5);

  TTS_IEEE_EQUAL(erf_inv(T( 0 )),T(0)  );
  TTS_IEEE_EQUAL(erf_inv(T(-0.)), T(0) );
  TTS_ULP_EQUAL(erf_inv(T( 0.1 )), T( boost::math::erf_inv(0.1)), 0.5 );
  TTS_ULP_EQUAL(erf_inv(T( 0.2 )), T( boost::math::erf_inv(0.2)), 0.5 );
  TTS_ULP_EQUAL(erf_inv(T( 0.3 )), T( boost::math::erf_inv(0.3)), 0.5 );
  TTS_ULP_EQUAL(erf_inv(T( 0.5 )), T( boost::math::erf_inv(0.5)),  1 );
  TTS_ULP_EQUAL(erf_inv(T( 0.15)), T( boost::math::erf_inv(0.15)), 0.5 );
  TTS_ULP_EQUAL(erf_inv(T( 0.75)), T( boost::math::erf_inv(0.75)), 0.5 );
  TTS_ULP_EQUAL(erf_inv(T(- 0.1 )), T( boost::math::erf_inv(-0.1)), 0.5 );
  TTS_ULP_EQUAL(erf_inv(T( -0.2 )), T( boost::math::erf_inv(-0.2)), 0.5 );
  TTS_ULP_EQUAL(erf_inv(T( -0.3 )), T( boost::math::erf_inv(-0.3)), 0.5 );
  TTS_ULP_EQUAL(erf_inv(T( -0.5 )), T( boost::math::erf_inv(-0.5)),  1 );
  TTS_ULP_EQUAL(erf_inv(T( -0.15)), T( boost::math::erf_inv(-0.15)), 0.5 );
  TTS_ULP_EQUAL(erf_inv(T( -0.75)), T( boost::math::erf_inv(-0.75)), 0.5 );
};
