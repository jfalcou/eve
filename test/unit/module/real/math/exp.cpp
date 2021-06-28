//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/minlogdenormal.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/function/pedantic/exp.hpp>
#include <eve/function/diff/exp.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of exp"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::exp(T())  , T);
  TTS_EXPR_IS( eve::exp(v_t()), v_t);
};

//==================================================================================================
// exp  tests
//==================================================================================================
EVE_TEST( "Check behavior of exp on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::minlog, eve::maxlog)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::exp(a0)      , map([](auto e) -> v_t { return std::exp(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::exp(a1)      , map([](auto e) -> v_t { return std::exp(e); }, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::exp)(a0), eve::exp(a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::exp)(a1), eve::exp(a1), 2);
  TTS_ULP_EQUAL(eve::pedantic(eve::exp)(a0)      , map([](auto e) -> v_t { return std::exp(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::pedantic(eve::exp)(a1)      , map([](auto e) -> v_t { return std::exp(e); }, a1), 2);
};

EVE_TEST_TYPES( "Check return types of exp"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_IEEE_EQUAL( eve::exp(T( 0.)), T(1));
  TTS_IEEE_EQUAL( eve::exp(T(-0.)), T(1));
  TTS_ULP_EQUAL (eve::exp(eve::minlog(eve::as<T>())), T(0), 0.5);
  TTS_ULP_EQUAL (eve::exp(eve::next(eve::minlog(eve::as<T>()))),T(std::exp(eve::minlog(eve::as<v_t>()))), 256.5);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::exp(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::exp(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::exp(eve::minf(eve::as<T>())), T( 0 ) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::exp)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::exp)(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::exp)(eve::minf(eve::as<T>())), T( 0 ) );
  }

  TTS_ULP_EQUAL(eve::pedantic(eve::exp)(T(1)), T(std::exp(v_t(1))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic(eve::exp)(T(-1)),T(std::exp(v_t(-1))), 0.5);

  TTS_IEEE_EQUAL( eve::pedantic(eve::exp)(T( 0.)), T(1));
  TTS_IEEE_EQUAL( eve::pedantic(eve::exp)(T(-0.)), T(1));
  if constexpr( eve::platform::supports_denormals )
  {
    TTS_ULP_EQUAL (eve::pedantic(eve::exp)(eve::minlog(eve::as<T>())), T(std::exp(eve::minlog(eve::as<v_t>()))), 0.5);
    TTS_ULP_EQUAL (eve::pedantic(eve::exp)(eve::prev(eve::minlog(eve::as<T>()))), T(std::exp(eve::prev(eve::minlog(eve::as<v_t>())))), 0.5);
  }
  TTS_ULP_EQUAL (eve::pedantic(eve::exp)(eve::minlogdenormal(eve::as<T>())), T(std::exp(eve::minlogdenormal(eve::as<v_t>()))), 0);
  TTS_ULP_EQUAL (eve::pedantic(eve::exp)(eve::prev(eve::minlogdenormal(eve::as<T>()))), T(std::exp(eve::prev(eve::minlogdenormal(eve::as<v_t>())))), 0);
};
