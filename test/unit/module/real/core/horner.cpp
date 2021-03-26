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
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/horner.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of horner on wide"
        , eve::test::simd::all_types

        )
<typename T>(eve::as_<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using wi_t = eve::as_wide_t<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::horner(T(), T())  , T);
  TTS_EXPR_IS( eve::horner(T()

};

//==================================================================================================
//== horner tests
//==================================================================================================
EVE_TEST( "Check behavior of horner on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  

};
