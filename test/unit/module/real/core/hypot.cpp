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
#include <eve/constant/half.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/diff/hypot.hpp>
#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of hypot"
        , eve::test::simd::all_types
        )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::hypot(T(), T()  ) , T);
  TTS_EXPR_IS( eve::hypot(T(), v_t()) , T);
  TTS_EXPR_IS( eve::hypot(v_t(), T()) , T);
  TTS_EXPR_IS( eve::hypot(T(),int()) , T);
  TTS_EXPR_IS( eve::hypot(int(), T()) , T);
  TTS_EXPR_IS( eve::hypot(v_t(), v_t()) , v_t);

  //multi
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::hypot(T(), T(), T()  )  , T);
    TTS_EXPR_IS( eve::hypot(T(), v_t(), T())  , T);
    TTS_EXPR_IS( eve::hypot(v_t(), T(), T())  , T);
    TTS_EXPR_IS( eve::hypot(T(), T(), v_t() ) , T);
    TTS_EXPR_IS( eve::hypot(v_t(), v_t(), T()) , T);
    TTS_EXPR_IS( eve::hypot(v_t(), T(), v_t()) , T);

    TTS_EXPR_IS( eve::hypot(T(), int(), T())  , T);
    TTS_EXPR_IS( eve::hypot(int(), T(), T())  , T);
    TTS_EXPR_IS( eve::hypot(T(), T(), int() ) , T);
    TTS_EXPR_IS( eve::hypot(int(), v_t(), T()) , T);
    TTS_EXPR_IS( eve::hypot(int(), T(), v_t()) , T);
    TTS_EXPR_IS( eve::hypot(v_t(), int(), T()) , T);
    TTS_EXPR_IS( eve::hypot(v_t(), T(), int()) , T);
    TTS_EXPR_IS( eve::hypot(v_t(), v_t(), v_t()) , v_t);
  }
};

//==================================================================================================
//== hypot tests
//==================================================================================================
EVE_TEST( "Check behavior of hypot(wide)"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(-100, 100)
                                  , eve::test::randoms(-100, 100)
                                  , eve::test::randoms(-100, 100)
                                  )
            )
<typename T>(T const& a0, T const& a1, T const& a2 )
{
  using eve::hypot;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL( hypot(a0, a1), map([](auto e, auto f) -> v_t { return std::hypot(e, f); }, a0, a1), 2);
  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL( hypot(a0, a1, a2), map([](auto e, auto f,  auto g) { return std::hypot(e, f, g); }, a0, a1, a2), 2);
  }
};

//==================================================================================================
//== diff(hypot) tests
//==================================================================================================
EVE_TEST( "Check behavior of diff(hypot)(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-100, 100)
                              , eve::test::randoms(-100, 100)
                              , eve::test::randoms(-100, 100)
                              )
            )
<typename T>( T const& a0, T const& a1, T const& a2 )
{
  using eve::hypot;
  using eve::as;
  using v_t =  eve::element_type_t<T>;
  TTS_ULP_EQUAL( eve::diff_1st(hypot)(a0, a1), map([](auto e , auto f) -> v_t { return e/std::hypot(e, f); }, a0, a1), 2);
  TTS_ULP_EQUAL( eve::diff_2nd(hypot)(a0, a1), map([](auto e , auto f) -> v_t { return f/std::hypot(e, f); }, a0, a1), 2);
  TTS_ULP_EQUAL( eve::diff_1st(hypot)(a0, a1, a2), map([](auto e, auto f, auto g) -> v_t { return e/std::hypot(e, f, g); }, a0, a1, a2), 2);
  TTS_ULP_EQUAL( eve::diff_2nd(hypot)(a0, a1, a2), map([](auto e, auto f, auto g) -> v_t { return f/std::hypot(e, f, g); }, a0, a1, a2), 2);
  TTS_ULP_EQUAL( eve::diff_3rd(hypot)(a0, a1, a2), map([](auto e, auto f, auto g) -> v_t { return g/std::hypot(e, f, g); }, a0, a1, a2), 2);
};
