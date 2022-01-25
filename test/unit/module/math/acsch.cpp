//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of acsch"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acsch(T())  , T);
  TTS_EXPR_IS( eve::acsch(v_t()), v_t);
};

//==================================================================================================
// acsch  tests
//==================================================================================================
EVE_TEST( "Check behavior of acsch on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-1e20,1e20)
                              , eve::test::randoms(-100.0, 100.0)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acsch(a0)      , map([](auto e) -> v_t { return std::asinh(1/e); }, a0), 2);
  TTS_ULP_EQUAL(eve::acsch(a1)      , map([](auto e) -> v_t { return std::asinh(1/e); }, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acsch)(a0), map([](auto e) -> v_t { return  v_t(-1)/(std::abs(e)*std::sqrt(1+e*e)); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acsch)(a1), map([](auto e) -> v_t { return  v_t(-1)/(std::abs(e)*std::sqrt(1+e*e)); }, a1), 2);
};
