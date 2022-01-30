//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of div"
          , eve::test::simd::all_types
          )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

 //  //regular
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


 //  //multi
  TTS_EXPR_IS( eve::div(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::div(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::div(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::div(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::div(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::div(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::div(v_t(), v_t(), v_t()) , v_t);

  TTS_EXPR_IS( eve::saturated(eve::div)(T(), T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::div)(T(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div)(v_t(), T(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div)(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::saturated(eve::div)(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div)(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div)(v_t(), v_t(), v_t()) , v_t);

  //diff
  if constexpr(eve::floating_value<T>)
  {
    using eve::diff_1st;
    using eve::diff_2nd;
    TTS_EXPR_IS( diff_1st(eve::div)(T(), T()  ) , T);
    TTS_EXPR_IS( diff_1st(eve::div)(T(), v_t()) , T);
    TTS_EXPR_IS( diff_1st(eve::div)(v_t(), T()) , T);
    TTS_EXPR_IS( diff_1st(eve::div)(v_t(), v_t()) , v_t);
    TTS_EXPR_IS( diff_2nd(eve::div)(T(), T()  ) , T);
    TTS_EXPR_IS( diff_2nd(eve::div)(T(), v_t()) , T);
    TTS_EXPR_IS( diff_2nd(eve::div)(v_t(), T()) , T);
    TTS_EXPR_IS( diff_2nd(eve::div)(v_t(), v_t()) , v_t);
  }
};

//==================================================================================================
//==  div simd tests
//==================================================================================================
EVE_TEST( "Check behavior of div on wide"
        , eve::test::simd::ieee_reals//all_types
        , eve::test::generate ( eve::test::randoms(0, 100)
                              , eve::test::randoms(1, 11)
                              , eve::test::randoms(1, 11)
                              )
        )
  <typename T>(T a0, T a1, T a2)
{
  using eve::div;
  using eve::mul;
  using eve::saturated;
  using eve::detail::map;
  TTS_ULP_EQUAL( eve::div(a0, a2), map([](auto e, auto f) { return eve::div(e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL( saturated(div)(a0, a2), map([&](auto e, auto f) { return saturated(div)(e, f); }, a0, a2), 0.5);
  TTS_ULP_EQUAL( div(a0, a1, a2), map([&](auto e, auto f, auto g) { return div(e, mul(f, g)); }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL(saturated(div)(a0, a1, a2), map([&](auto e, auto f, auto g) { return saturated(div)(e, saturated(mul)(f, g)); }, a0, a1, a2), 0.5);
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL( eve::diff_1st(div)(a0, a1), eve::rec(a1));
    TTS_EQUAL( eve::diff_2nd(div)(a0, a1), -a0*eve::rec(eve::sqr(a1)));
    TTS_EQUAL( eve::diff_1st(div)(a0, a1, a2), eve::rec(a2*a1));
    TTS_ULP_EQUAL( eve::diff_2nd(div)(a0, a1, a2), -a0*eve::rec(a2*eve::sqr(a1)), 2);
    TTS_ULP_EQUAL( eve::diff_3rd(div)(a0, a1, a2), -a0*eve::rec(a1*eve::sqr(a2)), 2);
  }
};


//==================================================================================================
//== Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::div variants on wide"
        , eve::test::simd::signed_integers
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::div;
  using eve::saturated;
  TTS_EQUAL     ( saturated(div)(cases.valmin, type(-1)) , cases.valmax);
  TTS_EQUAL     ( saturated(div)(type(3)     , type(0))  , cases.valmax);
  TTS_EQUAL     ( saturated(div)(type(-3)    , type(0))  , cases.valmin);
};


//==================================================================================================
//==  conditional div tests on simd
//==================================================================================================
auto mini = [] < typename T > (eve::as<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0;};

EVE_TEST( "Check behavior of div on signed types"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              , eve::test::randoms(mini, 127)
                              )
        )
  <typename T>( T a0, T a1, T a2)
{
  using eve::div;
  using eve::saturated;
  using eve::is_nez;
  using eve::detail::map;
  a2 = eve::if_else(a2 > 0, eve::zero, a2);
  TTS_ULP_EQUAL( div[is_nez(a2)](a0, a2), map([](auto e, auto f) {return is_nez(f) ? div(e, f) : e ; }, a0, a2), 0.5);
  TTS_ULP_EQUAL( saturated(div[is_nez(a0)&&is_nez(a2)])(a0, a2), map([](auto e, auto f) { return  is_nez(e)&&is_nez(f) ? saturated(div)(e, f): e; }, a0, a2), 0.5);

  a1 =  eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_ULP_EQUAL( div[a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) {return g > 64 ? div(e, f) : e ; }, a0, a1, a2), 0.5);
  TTS_ULP_EQUAL( saturated(div[a2 > T(64)])(a0, a1), map([](auto e, auto f, auto g) { return  g > 64 ? saturated(div)(e, f): e; }, a0, a1, a2), 0.5);
};
