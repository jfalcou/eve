//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of exp10"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::exp10(T())  , T);
  TTS_EXPR_IS( eve::exp10(v_t()), v_t);
};

//==================================================================================================
// exp10  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of exp10 on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(eve::minlog10, eve::maxlog10)
                              , tts::randoms(-1.0, 1.0)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  long double l10 = std::log(10.0l);
  TTS_ULP_EQUAL(eve::exp10(a0), map([l10](auto e) -> v_t { return std::exp(l10*e); }, a0), 380);
  TTS_ULP_EQUAL(eve::exp10(a1), map([l10](auto e) -> v_t { return std::exp(l10*e); }, a1), 2);




  TTS_ULP_EQUAL(eve::pedantic(eve::exp10)(a0), map([l10](auto e) -> v_t { return std::exp(l10*e); }, a0), 380);
  TTS_ULP_EQUAL(eve::pedantic(eve::exp10)(a1), map([l10](auto e) -> v_t { return std::exp(l10*e); }, a1), 2);
};

TTS_CASE_TPL( "Check corner-cases of exp10"
              , eve::test::simd::ieee_reals
              )
<typename T>(tts::type<T>)
{
  TTS_ULP_EQUAL ( eve::pedantic(eve::exp10)(T(1)), T(10), 0.5);
  TTS_IEEE_EQUAL( eve::pedantic(eve::exp10)(T(0)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    using elt_t =  eve::element_type_t<T>;
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::exp10(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::exp10(eve::inf(eve::as<T>())) , (eve::inf(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::exp10(eve::minf(eve::as<T>())), (T( 0 )) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp10)(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp10)(eve::inf(eve::as<T>())) , (eve::inf(eve::as<T>())) );
      TTS_IEEE_EQUAL(eve::pedantic(eve::exp10)(eve::minf(eve::as<T>())), (T( 0 )) );
    }

    TTS_ULP_EQUAL ( eve::exp10(T(-1)) , T(0.1), 0.5);
    TTS_IEEE_EQUAL( eve::exp10(T(-0.)), T(1));
    TTS_ULP_EQUAL (eve::exp10(eve::minlog10(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL (eve::exp10(eve::prev(eve::minlog10(eve::as<T>()))), T(0), 0);

    TTS_ULP_EQUAL (eve::exp10(eve::minlog10denormal(eve::as<T>())), T(0), 0);

    TTS_ULP_EQUAL ( eve::pedantic(eve::exp10)(T(-1)) , T(0.1), 0.5);
    TTS_IEEE_EQUAL( eve::pedantic(eve::exp10)(T(-0.)), T(1));
    if constexpr( eve::platform::supports_denormals )
    {
      TTS_ULP_EQUAL (eve::pedantic(eve::exp10)(eve::minlog10(eve::as<T>())), T(std::exp(elt_t(std::log(10.0))*eve::minlog10(eve::as<elt_t>()))), 256);
      TTS_ULP_EQUAL (eve::pedantic(eve::exp10)(eve::prev(eve::minlog10(eve::as<T>()))), T(std::exp(elt_t(std::log(10.0))*eve::prev(eve::minlog10(eve::as<elt_t>())))), 256);
    }
    TTS_ULP_EQUAL (eve::pedantic(eve::exp10)(eve::minlog10denormal(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL (eve::pedantic(eve::exp10)(eve::prev(eve::minlog10denormal(eve::as<T>()))), T(0), 0);
  }
};
