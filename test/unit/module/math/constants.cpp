//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/math.hpp>
#include <limits>

EVE_TEST_TYPES("Check math constants behavior"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using elt_t = eve::element_type_t<T>;
  using eve::as;
  TTS_ULP_EQUAL(eve::pi(as<T>()), 4*eve::atan(T(1)),0.5);
  TTS_ULP_EQUAL(eve::pio_2(as<T>()), 2*eve::atan(T(1)),0.5);
  TTS_ULP_EQUAL(eve::pio_4(as<T>()),   eve::atan(T(1)),0.5);
  TTS_ULP_EQUAL(eve::sqrt_2(as<T>()), eve::sqrt(T(2)),0.5);
  TTS_ULP_EQUAL(eve::invsqrt_2(as<T>()), eve::sqrt(T(2))/2,0.5);
  TTS_ULP_EQUAL(eve::invlog_10(as<T>()), eve::rec(eve::log(T(10))),0.5);
  TTS_ULP_EQUAL(eve::invlog10_2(as<T>()), eve::rec(eve::log10(T(2))),0.5);
  TTS_ULP_EQUAL(eve::twopi(as<T>()), 8*eve::atan(T(1)),0.5);
  TTS_ULP_EQUAL(eve::twoopi(as<T>()), eve::rec(eve::pio_2(as<T>())),0.5);

  TTS_EQUAL(eve::inf(as<T>()), T(1.0/0.0));
  TTS_EQUAL(eve::minf(as<T>()),  T(-1.0/0.0));
  TTS_EQUAL(eve::valmax(as<T>()), T(std::numeric_limits<elt_t>::max()));
  TTS_EQUAL(eve::valmin(as<T>()), T(std::numeric_limits<elt_t>::lowest()));
  TTS_EQUAL(eve::smallestposval(as<T>()), T(std::numeric_limits<elt_t>::min()));

  if constexpr(std::is_same_v<elt_t, float>)
  {
    TTS_ULP_EQUAL(eve::maxflint(as<T>()), T(16777216.0f), 0.5);
    TTS_ULP_EQUAL(eve::sqrtvalmax(as<T>()), T(18446741874686296064.0), 0.5);
  }
  else if constexpr(std::is_same_v<elt_t, double>)
  {
    TTS_ULP_EQUAL(eve::maxflint(as<T>()), T(9007199254740992.0), 0.5);
    TTS_ULP_EQUAL(eve::sqrtvalmax(as<T>()), T(1.3407807929942595611e+154), 0.5);
  }
};
