//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/atan2d.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check pedantic(eve::atan2d) return type", EVE_TYPE)
{
  using eve::pedantic;
  TTS_EXPR_IS(eve::pedantic(eve::atan2d)(T(0), T(0)), T);
}

TTS_CASE_TPL("Check pedantic(eve::atan2d)  behavior", EVE_TYPE)
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::pedantic;
  using eve::all;

  auto mzero = T(-0.);

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::inf(eve::as<T>());
    auto minf = eve::minf(eve::as<T>());

    TTS_ULP_EQUAL(pedantic(eve::atan2d)(inf         , (T(1.))  ), (T(90))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(inf         , (T(-1.)) ), (T(90))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(minf        , (T(1.))  ), -(T(90)) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(minf        , (T(-1.)) ), -(T(90)) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)((T( 1.)) , minf        ), (T(180)) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(-1.)) , minf        ), (T(-180)), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)((T( 1.)) , inf         ), (T(0.))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(-1.)) , inf         ), mzero       , 0.5);

    TTS_EXPECT( eve::all(is_negative(pedantic(eve::atan2d)((T(-1.)), inf))) );
    TTS_EXPECT( eve::all(is_positive(pedantic(eve::atan2d)((T(1.)) , inf))) );

    TTS_ULP_EQUAL(pedantic(eve::atan2d)(minf, minf      ), -3*(T(45)), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(inf , minf      ),  3*(T(45)), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(minf, inf       ), -(T(45))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(inf , inf       ),  (T(45))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(inf , (T(1.))),  (T(90))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(minf, (T(1.))), -(T(90))  , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)(eve::nan(eve::as<T>()), (T(0.)))       , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(0.))      , eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(0.5)) , (T(0.5)) ) ,  (T(45))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(-0.5)), (T(-0.5))) , -3*(T(45)), 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(-1.)) , (T(-1.)) ) , -3*(T(45)), 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(1.))  , (T(1.))  ) ,  (T(45))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(0.))  , (T(0.))  ) ,  (T(0.))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)(mzero       , (T(0.))  ) ,  mzero       , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)(mzero       , mzero       ) ,  (T(-180)) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)(mzero       , (T(-1.)) ) ,  (T(-180)) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(0.))  , mzero       ) ,  (T(180))   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(0.))  , (T(-1.)) ) ,  (T(180))   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(-1.)) , mzero       ) , -(T(90))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(-1.)) , (T(0.))  ) , -(T(90))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(1.))  , mzero       ) ,  (T(90))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2d)((T(1.))  , (T(0.))  ) ,  (T(90))  , 0.5);
}
