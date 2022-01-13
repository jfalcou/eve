//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mone.hpp>
#include <eve/function/plus.hpp>
#include <eve/function/saturated/plus.hpp>
#include <eve/function/diff/plus.hpp>
#include <eve/function/plus.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::plus", eve::test::simd::signed_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::plus(T())                      , T );
  TTS_EXPR_IS( eve::plus(v_t())                      , v_t );
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::plus)(T()) , T );
    TTS_EXPR_IS( eve::diff(eve::plus)(v_t()) , v_t );
  }
};



//==================================================================================================
// Test for eve::diff(eve::plus)
//==================================================================================================
EVE_TEST( "Check behavior of eve::diff(eve::plus) on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;

  TTS_EQUAL ( eve::diff(eve::plus)(a0)
            , eve::one(eve::as(a0))
            );
};
