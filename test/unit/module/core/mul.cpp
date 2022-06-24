//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

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


  if constexpr(eve::floating_value<T>)
  {










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
