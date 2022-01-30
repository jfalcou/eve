//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of copysign"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::copysign(T(), T())  , T);
  TTS_EXPR_IS( eve::copysign(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::copysign(T(), v_t()), T);
  TTS_EXPR_IS( eve::copysign(v_t(), T()), T);
};

//==================================================================================================
// copysign  simd tests
//==================================================================================================
EVE_TEST( "Check behavior of copysign on wide and scalar"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0, T const& a1 )
{
  using eve::detail::map;
  auto val1 = a1.get(0);
  auto val0 = a0.get(0);
  TTS_EQUAL( eve::copysign(a0, a1), map([&](auto e,  auto f){return eve::abs(e)*eve::sign(f);}, a0, a1));
  TTS_EQUAL( eve::copysign(val0, a1), map([&](auto f ){return eve::abs(val0)*eve::sign(f);}, a1));
  TTS_EQUAL( eve::copysign(a0, val1), map([&](auto e){return eve::abs(e)*eve::sign(val1);}, a0));

};
