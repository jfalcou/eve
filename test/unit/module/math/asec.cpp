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
EVE_TEST_TYPES( "Check return types of asec"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::asec(T())  , T);
  TTS_EXPR_IS( eve::asec(v_t()), v_t);
};

//==================================================================================================
// asec  tests
//==================================================================================================
EVE_TEST( "Check behavior of asec on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(1.0, 100.0)
                             , eve::test::randoms(1.0, eve::valmax)
                             , eve::test::randoms(eve::valmin, -1.0)
                             , eve::test::randoms(-100.0, -1.0))
        )
<typename T>(T const& a0, T const& a1,T const& a2, T const& a3 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto sasec = [](auto e) -> v_t { return std::acos(1/e); };
  TTS_ULP_EQUAL(eve::asec(a0)           , map(sasec, a0), 2);
  
  TTS_ULP_EQUAL(eve::asec(a1)           , map(sasec, a1), 2);
  
  TTS_ULP_EQUAL(eve::asec(a2)           , map(sasec, a2), 2);
  
  TTS_ULP_EQUAL(eve::asec(a3)           , map(sasec, a3), 2);
  

};
