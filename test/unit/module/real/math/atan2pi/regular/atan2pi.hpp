//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atan2pi.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::atan2pi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::atan2pi(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::atan2pi behavior", EVE_TYPE)
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::all;

  auto mzero = T(-0.);

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::inf(eve::as<T>());
    auto minf = eve::minf(eve::as<T>());

    TTS_ULP_EQUAL(eve::atan2pi(inf         , (T(1.))  ), (T(0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf         , (T(-1.)) ), (T(0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf        , (T(1.))  ), (T(-0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf        , (T(-1.)) ), (T(-0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((T( 1.)) , minf        ), (T(1.))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((T(-1.)) , minf        ), (T(-1.)) , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((T( 1.)) , inf         ), (T(0.))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((T(-1.)) , inf         ), mzero       , 0.5);

    TTS_EXPECT( eve::all(is_negative(eve::atan2pi((T(-1.)), inf))) );
    TTS_EXPECT( eve::all(is_positive(eve::atan2pi((T(1.)) , inf))) );

    TTS_ULP_EQUAL(eve::atan2pi(minf, minf      ),  eve::nan(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf , minf      ),  eve::nan(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf, inf       ),  eve::nan(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf , inf       ),  eve::nan(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf , (T(1.))),  (T(0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf, (T(1.))), (T(-0.5)) , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atan2pi(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(eve::nan(eve::as<T>()), (T(0.)))       , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((T(0.))      , eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(eve::atan2pi((T(0.5)) , (T(0.5)) ) , (T(0.25)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((T(-0.5)), (T(-0.5))) , (T(-0.75)), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((T(-1.)) , (T(-1.)) ) , (T(-0.75)), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((T(1.))  , (T(1.))  ) , (T(0.25)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi(mzero       , (T(-1.)) ) , (T(-1.))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((T(0.))  , (T(-1.)) ) , (T(1.))   , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((T(-1.)) , mzero       ) , (T(-0.5)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((T(-1.)) , (T(0.))  ) , (T(-0.5)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((T(1.))  , mzero       ) , (T(0.5))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((T(1.))  , (T(0.))  ) , (T(0.5))  , 0.5);

  TTS_ULP_EQUAL(eve::atan2pi((T(0.))  , (T(0.))  ) ,  eve::nan(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi(mzero       , (T(0.))  ) ,  eve::nan(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi(mzero       , mzero       ) ,  eve::nan(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((T(0.))  , mzero       ) ,  eve::nan(eve::as<T>()), 0.5);
}
