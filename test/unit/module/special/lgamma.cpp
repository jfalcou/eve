//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of lgamma", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::lgamma(T()), T);
  TTS_EXPR_IS(eve::lgamma(v_t()), v_t);
};

//==================================================================================================
// lgamma  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of lgamma on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10000.0, 10000.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using eve::lgamma;
  TTS_RELATIVE_EQUAL(lgamma(a0), map([&](auto e) -> v_t { return std::lgamma(e); }, a0), 5e-2);

  TTS_ULP_EQUAL(lgamma(T(0.5)), T(std::lgamma(v_t(0.5))), 1.);
  TTS_ULP_EQUAL(lgamma(T(-35)), T(std::lgamma(v_t(-35))), 0.5);
  TTS_ULP_EQUAL(lgamma(T(-75.3)), T(std::lgamma(v_t(-75.3))), 0.5);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(lgamma(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(lgamma(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(lgamma(eve::minf(eve::as<T>())), eve::inf(eve::as<T>()));
  }
  TTS_IEEE_EQUAL(lgamma(T(0)), eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(lgamma(T(-0.)), eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(lgamma(T(1)), T(0));
  TTS_IEEE_EQUAL(lgamma(T(2)), T(0));
  TTS_IEEE_EQUAL(lgamma(T(3)), T(std::log(2.0)));
  TTS_IEEE_EQUAL(lgamma(T(5)), T(std::log(24.0)));
};
