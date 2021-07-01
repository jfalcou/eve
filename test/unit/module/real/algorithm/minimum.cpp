//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/minimum.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::minimum(wide)", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::minimum(T())                          , v_t               );
  TTS_EXPR_IS( eve::minimum(eve::logical<T>())            , bool              );
  TTS_EXPR_IS( eve::splat(eve::minimum)(T())              , T                 );
  TTS_EXPR_IS( eve::splat(eve::minimum)(eve::logical<T>()), eve::logical<T>   );
};

//==================================================================================================
// Tests for eve::abs
//==================================================================================================
EVE_TEST( "Check behavior of eve::minimum(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmin)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename L>(T const& a0, L const& l0)
{
  using v_t = eve::element_type_t<T>;

  v_t min_value = *std::min_element(a0.begin(),a0.end());

  TTS_EQUAL(eve::minimum(a0)            , min_value   );
  TTS_EQUAL(eve::splat(eve::minimum)(a0), T(min_value));

  TTS_EQUAL(eve::minimum(l0)            , (l0.size() == 1)  );
  TTS_EQUAL(eve::splat(eve::minimum)(l0), L(l0.size() == 1) );
};
