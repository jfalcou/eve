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
#include <eve/constant/nan.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/pedantic/rem.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
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
  using eve::rem;
  using eve::pedantic;

  //regular
  TTS_EXPR_IS( rem(T(), T()  ) , T);
  TTS_EXPR_IS( rem(T(), v_t()) , T);
  TTS_EXPR_IS( rem(v_t(), T()) , T);
  TTS_EXPR_IS( rem(v_t(), v_t()) , v_t);

  //conditionnal
  TTS_EXPR_IS( rem[eve::logical<T>()](T(), T()  ) , T);
  TTS_EXPR_IS( rem[eve::logical<T>()](T(), v_t()) , T);
  TTS_EXPR_IS( rem[eve::logical<T>()](v_t(), T()) , T);
  TTS_EXPR_IS( rem[eve::logical<v_t>()](T(), T()  ) , T);
  TTS_EXPR_IS( rem[eve::logical<v_t>()](T(), v_t()) , T);
  TTS_EXPR_IS( rem[eve::logical<v_t>()](v_t(), T()) , T);

  //pedantic
  TTS_EXPR_IS( pedantic(rem)(T(), T()  ) , T);
  TTS_EXPR_IS( pedantic(rem)(T(), v_t()) , T);
  TTS_EXPR_IS( pedantic(rem)(v_t(), T()) , T);
  TTS_EXPR_IS( pedantic(rem)(v_t(), v_t()) , v_t);

  //pedantic conditionnal
  TTS_EXPR_IS( pedantic(rem[eve::logical<T>()])(T(), T()  ) , T);
  TTS_EXPR_IS( pedantic(rem[eve::logical<T>()])(T(), v_t()) , T);
  TTS_EXPR_IS( pedantic(rem[eve::logical<T>()])(v_t(), T()) , T);
  TTS_EXPR_IS( pedantic(rem[eve::logical<v_t>()])(T(), T()  ) , T);
  TTS_EXPR_IS( pedantic(rem[eve::logical<v_t>()])(T(), v_t()) , T);
  TTS_EXPR_IS( pedantic(rem[eve::logical<v_t>()])(v_t(), T()) , T);
};

//==================================================================================================
//==  rem simd tests
//==================================================================================================
auto mini = [] < typename T > (eve::as_<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -100 : 0;};

EVE_TEST( "Check behavior of rem on wide"
        , eve::test::simd::ieee_reals//all_types
        , eve::test::generate ( eve::test::randoms(mini, 100)
                              , eve::test::randoms(mini, 100)
                              )
        )
  <typename T>(T a0, T a1)
{
  using eve::rem;
  using eve::pedantic;
  using eve::detail::map;
  TTS_ULP_EQUAL( pedantic(rem)(a0, a1), map([](auto e, auto f) { return eve::rem(e, f); }, a0, a1), 30);//fma not avail scalar double it seems
  a1 =  eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_ULP_EQUAL( rem(a0, a1), map([](auto e, auto f) { return eve::rem(e, f); }, a0, a1), 30);
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
  using eve::rem;

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(rem(  T(-1),   T(2)), T(-1));
    TTS_EQUAL(rem(v_t(-1),   T(2)), T(-1));
    TTS_EQUAL(rem(  T(-1), v_t(2)), T(-1));
    TTS_EQUAL(rem(  T(-4),   T(3)), T(-1));
    TTS_EQUAL(rem(v_t(-4),   T(3)), T(-1));
    TTS_EQUAL(rem(  T(-4), v_t(3)), T(-1));
  }

  TTS_EQUAL(rem(T(12), T(4)), T(0));
  TTS_EQUAL(rem(T( 1), T(2)), T(1));
  TTS_EQUAL(rem(T( 4), T(3)), T(1));

  TTS_EQUAL(rem(v_t(12), T(4)), T(0));
  TTS_EQUAL(rem(v_t( 1), T(2)), T(1));
  TTS_EQUAL(rem(v_t( 4), T(3)), T(1));

  TTS_EQUAL(rem(T(12), v_t(4)), T(0));
  TTS_EQUAL(rem(T( 1), v_t(2)), T(1));
  TTS_EQUAL(eve::toward_zero(rem)(T( 4), v_t(3)), T(1));
  if (eve::floating_real_value<T>)
    TTS_IEEE_EQUAL(eve::pedantic(rem)(T( 4), T(0)), eve::nan(eve::as<T>()));
  else
    TTS_EQUAL(eve::pedantic(rem)(T( 4), T(0)), T(4));
};


//==================================================================================================
//==  conditional rem tests
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
  using eve::pedantic;
  using eve::detail::map;
  TTS_ULP_EQUAL( pedantic(rem[is_nez(a2)])(a0, a2), map([](auto e, auto f) {return is_nez(f) ? rem(e, f) : e ; }, a0, a2), 8);
  a2 = eve::if_else(a2 >= 0, eve::one, a2);
  TTS_ULP_EQUAL( rem[is_nez(a2)](a0, a2), map([](auto e, auto f) {return rem(e, f); }, a0, a2), 2);

  TTS_ULP_EQUAL( rem[a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) {return g > 64 ? rem(e, f) : e ; }, a0, a1, a2), 2);
  a1 =  eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_ULP_EQUAL( rem[a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) {return g > 64 ? rem(e, f) : e ; }, a0, a1, a2), 2);
};
