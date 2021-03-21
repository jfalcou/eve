//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/cbrt.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/diff/cbrt.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of cbrt"
            , eve::test::simd::ieee_reals
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::cbrt(T())  , T);
  TTS_EXPR_IS( eve::cbrt(v_t()), v_t);
  TTS_EXPR_IS( eve::cbrt[eve::logical<T>()](T())  , T);
  TTS_EXPR_IS( eve::cbrt[eve::logical<T>()](v_t()), T);
  TTS_EXPR_IS( eve::cbrt[eve::logical<v_t>()](T())  , T);
  TTS_EXPR_IS( eve::cbrt[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS( eve::cbrt[bool()](T())  , T);
  TTS_EXPR_IS( eve::cbrt[bool()](v_t()), v_t);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::cbrt)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::cbrt)(v_t()), v_t);
  }
};

//==================================================================================================
// cbrt tests
//==================================================================================================
EVE_TEST( "Check behavior of cbrt on  wide"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
            )
<typename T>(T const& a0 )
{
  TTS_ULP_EQUAL( eve::cbrt(a0), T([&](auto i, auto) { return std::cbrt(a0.get(i)); }), 2);
};
