//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of atanpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::atanpi(T())  , T);
  TTS_EXPR_IS( eve::atanpi(v_t()), v_t);
};

//==================================================================================================
// atanpi  tests
//==================================================================================================
EVE_TEST( "Check behavior of atanpi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::atanpi(a0)      , map([](auto e) -> v_t { return eve::radinpi(std::atan(e)); }, a0), 2);
  TTS_ULP_EQUAL(eve::atanpi(a1)      , map([](auto e) -> v_t { return eve::radinpi(std::atan(e)); }, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::atanpi)(a0), map([](auto e) -> v_t { return  eve::radinpi(v_t(1)/(e*e+1)); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::atanpi)(a1), map([](auto e) -> v_t { return  eve::radinpi(v_t(1)/(e*e+1)); }, a1), 2);
};
