//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/limit.hpp>
#include <eve/platform.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/trunc.hpp>
#include <eve/concept/value.hpp>
#include <limits>

EVE_TEST_TYPES( "Check limits"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL(eve::inf(as<T>()), T(1.0/0.0));
    TTS_EQUAL(eve::minf(as<T>()),  T(-1.0/0.0));
    TTS_EQUAL(eve::valmax(as<T>()), T(std::numeric_limits<elt_t>::max()));
    TTS_EQUAL(eve::valmin(as<T>()), T(std::numeric_limits<elt_t>::lowest()));
    TTS_EQUAL(eve::smallestposval(as<T>()), T(std::numeric_limits<elt_t>::min()));

    if constexpr(std::is_same_v<elt_t, float>)
    {
      TTS_EQUAL(eve::maxflint(as<T>()), T(16777216.0f));
      TTS_EQUAL(eve::sqrtvalmax(as<T>()), T(18446741874686296064.0));
    }
    else if constexpr(std::is_same_v<elt_t, double>)
    {
      TTS_EQUAL(eve::maxflint(as<T>()), T(9007199254740992.0));
      TTS_EQUAL(eve::sqrtvalmax(as<T>()), T(1.3407807929942595611e+154));
    }
  }
  else
  {
    TTS_EQUAL(eve::sqrtvalmax(as<T>()), T(eve::trunc(std::sqrt(eve::valmax(as<elt_t>())))));
  }
};
