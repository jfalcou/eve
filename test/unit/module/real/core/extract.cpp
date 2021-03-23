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
#include <eve/function/extract.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of extract"
            , eve::test::simd::all_types
  
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::extract(T(), int(0))  , v_t);
};


//==================================================================================================
// extract  tests
//==================================================================================================
EVE_TEST( "Check behavior of extract on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  for(int i=0; i< eve::cardinal_v<T>; ++i)
    TTS_EQUAL( eve::extract(a0, i), a0.get(i));
};
