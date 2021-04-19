//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/prod.hpp>
#include <numeric>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::prod(wide)", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::prod(T())             , v_t );
  TTS_EXPR_IS( eve::splat(eve::prod)(T()) , T   );
};

//==================================================================================================
// Tests for eve::abs
//==================================================================================================
EVE_TEST( "Check behavior of eve::prod(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(1, 3) )
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  v_t prod_value = std::accumulate(a0.begin(),a0.end(), v_t{1}, eve::mul);

  TTS_ULP_EQUAL(eve::prod(a0)            , prod_value   , 1);
  TTS_ULP_EQUAL(eve::splat(eve::prod)(a0), T(prod_value), 1);
};
