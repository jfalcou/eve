//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/saturated/mul.hpp>
#include <eve/function/diff/mul.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of mul"
          , eve::test::simd::all_types
          )
<typename T>(eve::as<T>)
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

  //diff
  if constexpr(eve::floating_value<T>)
  {
    using eve::diff_1st;
    using eve::diff_2nd;
    TTS_EXPR_IS( diff_1st(eve::mul)(T(), T()  ) , T);
    TTS_EXPR_IS( diff_1st(eve::mul)(T(), v_t()) , T);
    TTS_EXPR_IS( diff_1st(eve::mul)(v_t(), T()) , T);
    TTS_EXPR_IS( diff_1st(eve::mul)(v_t(), v_t()) , v_t);
    TTS_EXPR_IS( diff_2nd(eve::mul)(T(), T()  ) , T);
    TTS_EXPR_IS( diff_2nd(eve::mul)(T(), v_t()) , T);
    TTS_EXPR_IS( diff_2nd(eve::mul)(v_t(), T()) , T);
    TTS_EXPR_IS( diff_2nd(eve::mul)(v_t(), v_t()) , v_t);
  }
};

//==================================================================================================
//==  mul simd tests
//==================================================================================================
EVE_TEST( "Check behavior of mul on wide"
            , eve::test::simd::integers
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::mul;
  using eve::saturated;
  using eve::detail::map;
  TTS_EQUAL( mul(a0, a2), map([](auto e, auto f) { return mul(e, f); }, a0, a2));
  TTS_EQUAL( saturated(mul)(a0, a2), map([&](auto e, auto f) { return saturated(mul)(e, f); }, a0, a2));
  TTS_EQUAL( mul(a0, a1, a2), map([&](auto e, auto f, auto g) { return mul(mul(e, f), g); }, a0, a1, a2));
  TTS_EQUAL( saturated(mul)(a0, a1, a2), map([&](auto e, auto f, auto g) { return saturated(mul)(saturated(mul)(e, f), g); }, a0, a1, a2));
};

EVE_TEST( "Check behavior of mul on wide"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(-100.0, 100.0)
                                  , eve::test::randoms(-100.0, 100.0)
                                  , eve::test::randoms(-100.0, 100.0)
                                  )
            )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::mul;
  using eve::detail::map;

  TTS_EQUAL( eve::diff_1st(mul)(a0, a2), a2);
  TTS_EQUAL( eve::diff_2nd(mul)(a0, a2), a0);
  TTS_EQUAL( eve::diff_3rd(mul)(a0, a1, a2), a1*a0);

};

//==================================================================================================
//==  conditional mul tests on simd
//==================================================================================================
auto mini = [] < typename T > (eve::as<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0;};

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
  using eve::detail::map;
  TTS_EQUAL( mul[a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) {return g > 64 ? mul(e, f) : e ; }, a0, a1, a2));
  TTS_EQUAL( saturated(mul[a2 > T(64)])(a0, a1), map([](auto e, auto f, auto g) { return  g > 64 ? saturated(mul)(e, f): e; }, a0, a1, a2));
};
