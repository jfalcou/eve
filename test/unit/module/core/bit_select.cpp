/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/arithmetic/constant/eps.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/mone.hpp>
#include <eve/function/bit_select.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of bit_select"
            , eve::test::simd::all_types
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::bit_select(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::bit_select(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::bit_select(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::bit_select(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::bit_select(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::bit_select(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::bit_select(v_t(), v_t(), v_t()) , v_t);
};


//==================================================================================================
// bit_select tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_select(simd) on integers"
        , eve::test::simd::integers
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using v_t = eve::element_type_t<T>;
  using eve::bit_select;
  using eve::detail::map;
  TTS_EQUAL(bit_select(a0, a1, a2), map([](auto x , auto y,  auto z)->v_t{ return (y& x)|(z&~x); }
                                       , a0, a1, a2
                                       ));
};
