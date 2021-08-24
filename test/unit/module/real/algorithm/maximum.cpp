//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/maximum.hpp>
#include <eve/function/if_else.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::maximum(wide)", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::maximum(T())                          , v_t               );
  TTS_EXPR_IS( eve::maximum(eve::logical<T>())            , bool              );
  TTS_EXPR_IS( eve::splat(eve::maximum)(T())              , T                 );
  TTS_EXPR_IS( eve::splat(eve::maximum)(eve::logical<T>()), eve::logical<T>   );
};

//==================================================================================================
// Tests for eve::maximum
//==================================================================================================
EVE_TEST( "Check behavior of eve::maximum(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename L>(T const& a0, L const& l0)
{
  using v_t = eve::element_type_t<T>;

  v_t max_value = *std::max_element(a0.begin(),a0.end());

  TTS_EQUAL(eve::maximum(a0)            , max_value   );
  TTS_EQUAL(eve::splat(eve::maximum)(a0), T(max_value));

  TTS_EQUAL(eve::maximum(l0)            , true    );
  TTS_EQUAL(eve::splat(eve::maximum)(l0), L(true) );
  
  TTS_EQUAL(eve::maximum[l0](a0)            , eve::maximum(eve::if_else(l0, a0, eve::valmin(eve::as(a0))))   );
  TTS_EQUAL(eve::splat(eve::maximum[l0])(a0), T(eve::maximum(eve::if_else(l0, a0, eve::valmin(eve::as(a0))))));
};
