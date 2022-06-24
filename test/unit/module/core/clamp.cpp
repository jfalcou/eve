/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of clamp"
        , eve::test::simd::all_types
        )<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  //multi
  TTS_EXPR_IS( eve::clamp(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::clamp(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::clamp(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::clamp(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::clamp(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::clamp(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::clamp(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// clamp simd tests
//==================================================================================================
auto val1 = []< typename T>(eve::as<T> const &){return (eve::valmax(eve::as(eve::element_type_t<T>()))/6); ;};
auto val2 = []< typename T>(eve::as<T> const &){return (eve::valmax(eve::as(eve::element_type_t<T>()))/6)*2;};
auto val3 = []< typename T>(eve::as<T> const &){return (eve::valmax(eve::as(eve::element_type_t<T>()))/6)*3;};
auto val4 = []< typename T>(eve::as<T> const &){return (eve::valmax(eve::as(eve::element_type_t<T>()))/6)*4;};

EVE_TEST( "Check behavior of clamp(wide) and diff  on all types"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(val1       , val4)
                              , eve::test::randoms(eve::valmin, val2)
                              , eve::test::randoms(val3, eve::valmax)
                              )
        )<typename T>( T const& a0, T const& a1, T const& a2 )
{
  using eve::clamp;
  
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL( clamp(a0, a1, a2), map([&](auto e, auto f, auto g) -> v_t{ return std::clamp(e, f, g); }, a0, a1, a2));

  if constexpr(eve::floating_real_value<T>)
  {
    
    
    
    using eve::min;
    using eve::max;
    
    
    
  }
};
