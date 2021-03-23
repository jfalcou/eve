/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/div.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/saturated/div.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_eqz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of div"
          , eve::test::simd::all_types

          )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::div(T(), T()  ) , T);
  TTS_EXPR_IS( eve::div(T(), v_t()) , T);
  TTS_EXPR_IS( eve::div(v_t(), T()) , T);
  TTS_EXPR_IS( eve::div(v_t(), v_t()) , v_t);

  //saturated
  TTS_EXPR_IS( eve::saturated(eve::div)(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::div)(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div)(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div)(v_t(), v_t()) , v_t);

  //conditionnal
  TTS_EXPR_IS( eve::div[eve::logical<T>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::div[eve::logical<T>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::div[eve::logical<T>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::div[eve::logical<v_t>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::div[eve::logical<v_t>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::div[eve::logical<v_t>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<T>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<T>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<T>()])(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<v_t>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<v_t>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<v_t>()])(v_t(), T()) , T);
};

//==================================================================================================
// div tests
//==================================================================================================
EVE_TEST( "Check behavior of div on all types"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T & a1)
{
  using eve::div;
  using eve::saturated;
  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_EQUAL( div(a0, a1), T([&](auto i, auto) { return div(a0.get(i), a1.get(i)); }));
  TTS_EQUAL( saturated(div)(a0, a1), T([&](auto i, auto) { return saturated(div)(a0.get(i), a1.get(i)); }));
};

//==================================================================================================
//==  conditional div tests
//==================================================================================================
auto mini = [] < typename T > (eve::as_<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0;};

EVE_TEST( "Check behavior of div on signed types"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              )
        )
<typename T>( T const& a0, T & a1, T const& a2)
{
  using eve::div;
  using eve::saturated;
  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);

  TTS_EQUAL( div[a2 > T(64)](a0, a1), T([&](auto i, auto) {return a2.get(i) > 64 ? div(a0.get(i), a1.get(i)) :a0.get(i) ; }));
  TTS_EQUAL( saturated(div[a2 > T(64)])(a0, a1), T([&](auto i, auto) { return  a2.get(i) > 64 ? saturated(div)(a0.get(i), a1.get(i)):a0.get(i); }));
};
