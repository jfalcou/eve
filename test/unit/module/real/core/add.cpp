//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/add.hpp>
#include <eve/function/saturated/add.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of add"
          , eve::test::simd::all_types
          , eve::test::generate(eve::test::no_data)
          )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::add(T(), T()  ) , T);
  TTS_EXPR_IS( eve::add(T(), v_t()) , T);
  TTS_EXPR_IS( eve::add(v_t(), T()) , T);
  TTS_EXPR_IS( eve::add(v_t(), v_t()) , v_t);

  //saturated
  TTS_EXPR_IS( eve::saturated(eve::add)(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::add)(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add)(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add)(v_t(), v_t()) , v_t);

  //conditionnal
  TTS_EXPR_IS( eve::add[eve::logical<T>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::add[eve::logical<T>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::add[eve::logical<T>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::add[eve::logical<v_t>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::add[eve::logical<v_t>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::add[eve::logical<v_t>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add[eve::logical<T>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::add[eve::logical<T>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add[eve::logical<T>()])(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add[eve::logical<v_t>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::add[eve::logical<v_t>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add[eve::logical<v_t>()])(v_t(), T()) , T);


  //multi
  TTS_EXPR_IS( eve::add(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::add(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::add(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::add(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::add(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::add(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::add(v_t(), v_t(), v_t()) , v_t);

  TTS_EXPR_IS( eve::saturated(eve::add)(T(), T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::add)(T(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add)(v_t(), T(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add)(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::saturated(eve::add)(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add)(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::add)(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// add tests
//==================================================================================================
EVE_TEST( "Check behavior of add on signed types"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::add;
  using eve::saturated;
  TTS_EQUAL( add(a0, a2), T([&](auto i, auto) { return add(a0.get(i), a2.get(i)); }));
  TTS_EQUAL( saturated(add)(a0, a2), T([&](auto i, auto) { return saturated(add)(a0.get(i), a2.get(i)); }));
  TTS_EQUAL( add(a0, a1, a2), T([&](auto i, auto) { return add(a0.get(i), a1.get(i), a2.get(i)); }));
  TTS_EQUAL( saturated(add)(a0, a1, a2), T([&](auto i, auto) { return saturated(add)(a0.get(i), a1.get(i), a2.get(i)); }));

};

//==================================================================================================
//==  conditional add tests
//==================================================================================================
auto mini = [] < typename T > (eve::as_<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0;};

EVE_TEST( "Check behavior of add on signed types"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              )
        )
<typename T>( T const& a0, T const& a1, T const& a2)
{
  using eve::add;
  using eve::saturated;

  TTS_EQUAL( add[a2 > T(64)](a0, a1), T([&](auto i, auto) {return a2.get(i) > 64 ? add(a0.get(i), a1.get(i)) :a0.get(i) ; }));
  TTS_EQUAL( saturated(add[a2 > T(64)])(a0, a1), T([&](auto i, auto) { return  a2.get(i) > 64 ? saturated(add)(a0.get(i), a1.get(i)):a0.get(i); }));
};
