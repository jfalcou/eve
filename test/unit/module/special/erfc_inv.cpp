//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/concept/value.hpp>
#include <eve/module/core.hpp>
#include <eve/module/special.hpp>
#include <eve/platform.hpp>

#include <cmath>

#include <boost/math/special_functions/erf.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
// TTS_CASE_TPL( "Check return types of erfc_inv"
//             , eve::test::simd::ieee_reals
//             )
// <typename T>(tts::type<T>)
// {
//   using v_t = eve::element_type_t<T>;

//   TTS_EXPR_IS( eve::erfc_inv(T())  , T);
//   TTS_EXPR_IS( eve::erfc_inv(v_t()), v_t);
// };

//==================================================================================================
// erfc_inv  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of erfc_inv on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.1, 2.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;
  using eve::erfc_inv;
  TTS_ULP_EQUAL(erfc_inv(a0), map([](auto e) { return boost::math::erfc_inv(e); }, a0), 2);
  TTS_ULP_EQUAL(erfc_inv(T(0.5)), T(boost::math::erfc_inv(v_t(0.5))), 1.);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(erfc_inv(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(erfc_inv(eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(erfc_inv(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_ULP_EQUAL(erfc_inv(T(35)), eve::nan(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(erfc_inv(T(-35)), eve::nan(eve::as<T>()), 0.5);

  TTS_IEEE_EQUAL(erfc_inv(T(0)), eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(erfc_inv(T(-0.)), eve::inf(eve::as<T>()));
  TTS_ULP_EQUAL(erfc_inv(T(0.1)), T(boost::math::erfc_inv(0.1)), 0.5);
  TTS_ULP_EQUAL(erfc_inv(T(0.2)), T(boost::math::erfc_inv(0.2)), 1);
  TTS_ULP_EQUAL(erfc_inv(T(0.3)), T(boost::math::erfc_inv(0.3)), 1);
  TTS_ULP_EQUAL(erfc_inv(T(0.5)), T(boost::math::erfc_inv(0.5)), 1);
  TTS_ULP_EQUAL(erfc_inv(T(0.15)), T(boost::math::erfc_inv(0.15)), 0.5);
  TTS_ULP_EQUAL(erfc_inv(T(0.75)), T(boost::math::erfc_inv(0.75)), 0.5);
  TTS_ULP_EQUAL(erfc_inv(T(1.0)), T(boost::math::erfc_inv(1.0)), 0.5);
  TTS_ULP_EQUAL(erfc_inv(T(1.1)), T(boost::math::erfc_inv(1.1)), 1.5);
  TTS_ULP_EQUAL(erfc_inv(T(1.2)), T(boost::math::erfc_inv(1.2)), 1.5);
  TTS_ULP_EQUAL(erfc_inv(T(1.3)), T(boost::math::erfc_inv(1.3)), 0.5);
  TTS_ULP_EQUAL(erfc_inv(T(1.5)), T(boost::math::erfc_inv(1.5)), 1);
  TTS_ULP_EQUAL(erfc_inv(T(1.15)), T(boost::math::erfc_inv(1.15)), 1.5);
  TTS_ULP_EQUAL(erfc_inv(T(1.75)), T(boost::math::erfc_inv(1.75)), 0.5);
  TTS_ULP_EQUAL(erfc_inv(T(1.45984)), T(boost::math::erfc_inv(1.45984)), 1.5);
};
