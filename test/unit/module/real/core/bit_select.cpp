/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/function/bit_select.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST( "Check return types of bit_select"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
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
EVE_TEST( "Check behavior of bit_select on all types full range"
        , eve::test::simd::integers
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::bit_select;
  TTS_EQUAL(bit_select(a0, a1, a2), T([&](auto i , auto) { auto x = a0.get(i);
                                        auto y = a1.get(i);
                                        auto z = a2.get(i);
                                        return (y& x)|(z&~x); }
                                     ));
};
