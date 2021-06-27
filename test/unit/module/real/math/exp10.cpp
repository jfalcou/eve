//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/minlog10.hpp>
#include <eve/constant/minlog10denormal.hpp>
#include <eve/constant/maxlog10.hpp>
#include <eve/function/pedantic/exp10.hpp>
#include <eve/function/diff/exp10.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of exp10"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::exp10(T())  , T);
  TTS_EXPR_IS( eve::exp10(v_t()), v_t);
};

//==================================================================================================
// exp10  tests
//==================================================================================================
EVE_TEST( "Check behavior of exp10 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::minlog10, eve::maxlog10)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  long double l10 = std::log(10.0l);
  TTS_ULP_EQUAL(eve::exp10(a0)      , map([l10](auto e) -> v_t { return std::exp(l10*e); }, a0), 30);
  TTS_ULP_EQUAL(eve::exp10(a1)      , map([l10](auto e) -> v_t { return std::exp(l10*e); }, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::exp10)(a0), l10*eve::exp10(a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::exp10)(a1), l10*eve::exp10(a1), 2);
  TTS_ULP_EQUAL(eve::pedantic(eve::exp10)(a0)      , map([l10](auto e) -> v_t { return std::exp(l10*e); }, a0), 30);
  TTS_ULP_EQUAL(eve::pedantic(eve::exp10)(a1)      , map([l10](auto e) -> v_t { return std::exp(l10*e); }, a1), 2);
};

EVE_TEST_TYPES( "Check return types of exp10"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
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
