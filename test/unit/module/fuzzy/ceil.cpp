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
#include <eve/constant/zero.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/fuzzy/ceil.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ceil"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::tolerant(eve::ceil)(T())  , T);
  TTS_EXPR_IS( eve::tolerant(eve::ceil)(v_t()), v_t);
};

//==================================================================================================
// tolerant tests
//==================================================================================================
EVE_TEST_TYPES( "Check tolerant(ceil) with specific values"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-2)), T(-2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(0)), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1)), T(1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(2)), T(2));

  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.3)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.5)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.6)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.3)) , T(2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.5)) , T(2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.6)) , T(2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(2*eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(3*eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(4*eve::eps(eve::as<T>())), T(1));
};
