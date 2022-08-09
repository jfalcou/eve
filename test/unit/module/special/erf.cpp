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
TTS_CASE_TPL("Check return types of erf", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::erf(T()), T);
  TTS_EXPR_IS(eve::erf(v_t()), v_t);
};

//==================================================================================================
// erf  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of erf on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10000.0, 10000.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;
  using eve::erf;
  TTS_ULP_EQUAL(erf(a0), map([&](auto e) -> v_t { return std::erf(e); }, a0), 2);
  TTS_ULP_EQUAL(erf(T(0.5)), T(std::erf(v_t(0.5))), 1.);
  TTS_ULP_EQUAL(erf(T(-35)), T(std::erf(v_t(-35))), 0.5);
  TTS_ULP_EQUAL(
      erf(T(eve::smallestposval(as<T>()))), T(std::erf(eve::smallestposval(as<v_t>()))), 0.5);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(erf(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(erf(eve::inf(eve::as<T>())), eve::one(eve::as<T>()));
    TTS_IEEE_EQUAL(erf(eve::minf(eve::as<T>())), eve::mone(eve::as<T>()));
  }
  TTS_IEEE_EQUAL(erf(T(0)), eve::zero(eve::as<T>()));
  TTS_IEEE_EQUAL(erf(T(-0.)), eve::zero(eve::as<T>()));
  TTS_EXPECT(eve::all(eve::is_negative(erf(T(-0.0)))));
  TTS_EXPECT(eve::all(eve::is_positive(erf(T(0.0)))));
};
