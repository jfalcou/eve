//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
EVE_TEST_TYPES( "Check return types of expm1"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::expm1(T())  , T);
  TTS_EXPR_IS( eve::expm1(v_t()), v_t);
};

//==================================================================================================
// expm1  tests
//==================================================================================================
EVE_TEST( "Check behavior of expm1 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::minlog, eve::maxlog)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::expm1(a0)      , map([](auto e) -> v_t { return std::expm1(e); }, a0), 30);
  TTS_ULP_EQUAL(eve::expm1(a1)      , map([](auto e) -> v_t { return std::expm1(e); }, a1), 2);
  
  
  TTS_ULP_EQUAL(eve::pedantic(eve::expm1)(a0)      , map([](auto e) -> v_t { return std::expm1(e); }, a0), 30);
  TTS_ULP_EQUAL(eve::pedantic(eve::expm1)(a1)      , map([](auto e) -> v_t { return std::expm1(e); }, a1), 2);
};

EVE_TEST_TYPES( "Check return types of expm1"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::expm1(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::expm1(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::expm1(eve::minf(eve::as<T>())), T(-1)        );
  }

  TTS_EXPECT(eve::all(eve::is_negative(eve::expm1(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::expm1(T( 0.)))));

  TTS_IEEE_EQUAL(eve::expm1(T(0))   , T(0) );
  TTS_IEEE_EQUAL(eve::expm1(T(-0.)) , T(0) );

  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::expm1(T(1))    , T(std::expm1(v_t(1))), 0.5);
  TTS_ULP_EQUAL(eve::expm1(T(-1))   ,T(std::expm1(v_t(-1))), 0.5);
};
