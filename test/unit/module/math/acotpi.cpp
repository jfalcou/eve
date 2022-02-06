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
EVE_TEST_TYPES( "Check return types of acotpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::acotpi(T())  , T);
  TTS_EXPR_IS( eve::acotpi(v_t()), v_t);
};

//==================================================================================================
// acotpi  tests
//==================================================================================================
EVE_TEST( "Check behavior of acotpi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(-1e20, 1e20) )
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::acotpi(a0)      , map([](auto e) -> v_t { return eve::radinpi(std::atan(1/e)); }, a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::acotpi)(a0), map([](auto e) -> v_t { return  eve::radinpi(-v_t(1))/(e*e+1); }, a0), 2);
};
