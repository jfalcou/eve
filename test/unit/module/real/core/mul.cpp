/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/saturated/mul.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of mul"
          , eve::test::simd::all_types

          )
  <typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::mul(T(), T()  ) , T);
  TTS_EXPR_IS( eve::mul(T(), v_t()) , T);
  TTS_EXPR_IS( eve::mul(v_t(), T()) , T);
  TTS_EXPR_IS( eve::mul(v_t(), v_t()) , v_t);

  //saturated
  TTS_EXPR_IS( eve::saturated(eve::mul)(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul)(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul)(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul)(v_t(), v_t()) , v_t);

  //conditionnal
  TTS_EXPR_IS( eve::mul[eve::logical<T>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::mul[eve::logical<T>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::mul[eve::logical<T>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::mul[eve::logical<v_t>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::mul[eve::logical<v_t>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::mul[eve::logical<v_t>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul[eve::logical<T>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul[eve::logical<T>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul[eve::logical<T>()])(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul[eve::logical<v_t>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul[eve::logical<v_t>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul[eve::logical<v_t>()])(v_t(), T()) , T);


  //multi
  TTS_EXPR_IS( eve::mul(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::mul(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::mul(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::mul(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::mul(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::mul(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::mul(v_t(), v_t(), v_t()) , v_t);

  TTS_EXPR_IS( eve::saturated(eve::mul)(T(), T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul)(T(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul)(v_t(), T(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul)(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul)(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul)(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::mul)(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// mul tests
//==================================================================================================
EVE_TEST( "Check behavior of mul on signed types"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::mul;
  using eve::saturated;
  TTS_EQUAL( mul(a0, a2), T([&](auto i, auto) { return mul(a0.get(i), a2.get(i)); }));
  TTS_EQUAL( saturated(mul)(a0, a2), T([&](auto i, auto) { return saturated(mul)(a0.get(i), a2.get(i)); }));
  TTS_EQUAL( mul(a0, a1, a2), T([&](auto i, auto) { return mul(a0.get(i), a1.get(i), a2.get(i)); }));
  TTS_EQUAL( saturated(mul)(a0, a1, a2), T([&](auto i, auto) { return saturated(mul)(a0.get(i), a1.get(i), a2.get(i)); }));

};

//==================================================================================================
//==  conditional mul tests
//==================================================================================================
auto mini = [] < typename T > (eve::as_<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0;};

EVE_TEST( "Check behavior of mul on signed types"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              )
        )
<typename T>( T const& a0, T const& a1, T const& a2)
{
  using eve::mul;
  using eve::saturated;

  TTS_EQUAL( mul[a2 > T(64)](a0, a1), T([&](auto i, auto) {return a2.get(i) > 64 ? mul(a0.get(i), a1.get(i)) :a0.get(i) ; }));
  TTS_EQUAL( saturated(mul[a2 > T(64)])(a0, a1), T([&](auto i, auto) { return  a2.get(i) > 64 ? saturated(mul)(a0.get(i), a1.get(i)):a0.get(i); }));
};
