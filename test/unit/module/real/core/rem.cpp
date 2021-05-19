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
#include <eve/constant/one.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of rem"
          , eve::test::simd::all_types
          )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

 //  //regular
  TTS_EXPR_IS( eve::rem(T(), T()  ) , T);
  TTS_EXPR_IS( eve::rem(T(), v_t()) , T);
  TTS_EXPR_IS( eve::rem(v_t(), T()) , T);
  TTS_EXPR_IS( eve::rem(v_t(), v_t()) , v_t);

  //conditionnal
  TTS_EXPR_IS( eve::rem[eve::logical<T>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::rem[eve::logical<T>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::rem[eve::logical<T>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::rem[eve::logical<v_t>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::rem[eve::logical<v_t>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::rem[eve::logical<v_t>()](v_t(), T()) , T);
};

//==================================================================================================
//==  rem simd tests
//==================================================================================================
auto mini = [] < typename T > (eve::as_<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -100 : 1;};

EVE_TEST( "Check behavior of rem on wide"
        , eve::test::simd::ieee_reals//all_types
        , eve::test::generate ( eve::test::randoms(mini, 100)
                              , eve::test::randoms(mini, 100)
                              )
        )
  <typename T>(T a0, T a1)
{
  using eve::rem;
  using eve::detail::map;
  TTS_ULP_EQUAL( eve::rem(a0, a1), map([](auto e, auto f) { return eve::rem(e, f); }, a0, a1), 30);//fma not avail scalar double it seems

};


//==================================================================================================
//== Test for fixed values
//==================================================================================================
EVE_TEST( "Check fixed-cases behavior of eve::rem"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::limits())
        )
<typename Z>(Z)
{
  using T =  typename Z::type;
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::rem(  T(-1),   T(2)), T(-1));
    TTS_EQUAL(eve::rem(v_t(-1),   T(2)), T(-1));
    TTS_EQUAL(eve::rem(  T(-1), v_t(2)), T(-1));
    TTS_EQUAL(eve::rem(  T(-4),   T(3)), T(-1));
    TTS_EQUAL(eve::rem(v_t(-4),   T(3)), T(-1));
    TTS_EQUAL(eve::rem(  T(-4), v_t(3)), T(-1));
  }

  TTS_EQUAL(eve::rem(T(12), T(4)), T(0));
  TTS_EQUAL(eve::rem(T( 1), T(2)), T(1));
  TTS_EQUAL(eve::rem(T( 4), T(3)), T(1));

  TTS_EQUAL(eve::rem(v_t(12), T(4)), T(0));
  TTS_EQUAL(eve::rem(v_t( 1), T(2)), T(1));
  TTS_EQUAL(eve::rem(v_t( 4), T(3)), T(1));

  TTS_EQUAL(eve::rem(T(12), v_t(4)), T(0));
  TTS_EQUAL(eve::rem(T( 1), v_t(2)), T(1));
  TTS_EQUAL(eve::toward_zero(eve::rem)(T( 4), v_t(3)), T(1));
};


//==================================================================================================
//==  conditional rem tests on simd
//==================================================================================================
EVE_TEST( "Check behavior of rem on signed types"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              )
        )
  <typename T>( T a0, T a1, T a2)
{
  using eve::rem;
  using eve::is_nez;
  using eve::detail::map;
  a2 = eve::if_else(a2 >= 0, eve::one, a2);
  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_ULP_EQUAL( rem[is_nez(a2)](a0, a2), map([](auto e, auto f) {return is_nez(f) ? rem(e, f) : e ; }, a0, a2), 2);

  a1 =  eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_ULP_EQUAL( rem[a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) {return g > 64 ? rem(e, f) : e ; }, a0, a1, a2), 2);
};
