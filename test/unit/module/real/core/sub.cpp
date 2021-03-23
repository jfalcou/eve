/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/saturated/sub.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sub"
          , eve::test::simd::all_types
          )
  <typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::sub(T(), T()  ) , T);
  TTS_EXPR_IS( eve::sub(T(), v_t()) , T);
  TTS_EXPR_IS( eve::sub(v_t(), T()) , T);
  TTS_EXPR_IS( eve::sub(v_t(), v_t()) , v_t);

  //saturated
  TTS_EXPR_IS( eve::saturated(eve::sub)(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub)(v_t(), v_t()) , v_t);

  //conditionnal
  TTS_EXPR_IS( eve::sub[eve::logical<T>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<T>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<T>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<v_t>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<v_t>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::sub[eve::logical<v_t>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<T>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<T>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<T>()])(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<v_t>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<v_t>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::sub[eve::logical<v_t>()])(v_t(), T()) , T);
};

//==================================================================================================
// sub tests
//==================================================================================================
EVE_TEST( "Check behavior of sub on all types"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T const& a2)
{
  using eve::sub;
  using eve::saturated;
  TTS_EQUAL( sub(a0, a2), T([&](auto i, auto) { return sub(a0.get(i), a2.get(i)); }));
  TTS_EQUAL( saturated(sub)(a0, a2), T([&](auto i, auto) { return saturated(sub)(a0.get(i), a2.get(i)); }));
};

//==================================================================================================
//==  conditional sub tests
//==================================================================================================
auto mini = [] < typename T > (eve::as_<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0;};

EVE_TEST( "Check behavior of conditional sub on all types"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              )
        )
<typename T>( T const& a0, T const& a1, T const& a2)
{
  using eve::sub;
  using eve::saturated;

  TTS_EQUAL( sub[a2 > T(64)](a0, a1), T([&](auto i, auto) {return a2.get(i) > 64 ? sub(a0.get(i), a1.get(i)) :a0.get(i) ; }));
  TTS_EQUAL( saturated(sub[a2 > T(64)])(a0, a1), T([&](auto i, auto) { return  a2.get(i) > 64 ? saturated(sub)(a0.get(i), a1.get(i)):a0.get(i); }));
};
