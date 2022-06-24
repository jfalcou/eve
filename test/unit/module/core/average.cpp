//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of average"
        , eve::test::simd::all_types
        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::average(T(), T()  ) , T);
  TTS_EXPR_IS( eve::average(T(), v_t()) , T);
  TTS_EXPR_IS( eve::average(v_t(), T()) , T);
  TTS_EXPR_IS( eve::average(T(),int()) , T);
  TTS_EXPR_IS( eve::average(int(), T()) , T);
  TTS_EXPR_IS( eve::average(v_t(), v_t()) , v_t);

  //multi
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::average(T(), T(), T()  )  , T);
    TTS_EXPR_IS( eve::average(T(), v_t(), T())  , T);
    TTS_EXPR_IS( eve::average(v_t(), T(), T())  , T);
    TTS_EXPR_IS( eve::average(T(), T(), v_t() ) , T);
    TTS_EXPR_IS( eve::average(v_t(), v_t(), T()) , T);
    TTS_EXPR_IS( eve::average(v_t(), T(), v_t()) , T);

    TTS_EXPR_IS( eve::average(T(), int(), T())  , T);
    TTS_EXPR_IS( eve::average(int(), T(), T())  , T);
    TTS_EXPR_IS( eve::average(T(), T(), int() ) , T);
    TTS_EXPR_IS( eve::average(int(), v_t(), T()) , T);
    TTS_EXPR_IS( eve::average(int(), T(), v_t()) , T);
    TTS_EXPR_IS( eve::average(v_t(), int(), T()) , T);
    TTS_EXPR_IS( eve::average(v_t(), T(), int()) , T);
    TTS_EXPR_IS( eve::average(v_t(), v_t(), v_t()) , v_t);
  }
};

//==================================================================================================
//== average tests
//==================================================================================================
EVE_TEST( "Check behavior of average(wide)"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T const& a1, T const& a2 )
{
  using eve::average;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL( average(a0, a1), map([](auto e, auto f) -> v_t { return std::midpoint(e, f); }, a0, a1), 2);
  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL( average(a0, a1, a2), map([](auto e, auto f,  auto g) { return e/3 + f/3 + g/3; }, a0, a1, a2), 2);
  }
};


//==================================================================================================
//==  conditional average tests
//==================================================================================================
EVE_TEST( "Check behavior of  average[cond](wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(0, 127)
                              , eve::test::randoms(0, 127)
                              , eve::test::randoms(0, 127)
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::average;
  using eve::detail::map;
  using v_t =  eve::element_type_t<T>;
  //values can differ by one on integral types from scalar to simd implementations (intrinsics may be at work)
  TTS_ULP_EQUAL( average[a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) {return g > v_t(64) ? average(e, f) :e; }, a0, a1, a2), 2);
};
