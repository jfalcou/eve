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
#include <eve/function/average.hpp>
#include <eve/function/diff/average.hpp>
#include <numeric>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of average"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::no_data)
        )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::average(T(), T()  ) , T);
  TTS_EXPR_IS( eve::average(T(), v_t()) , T);
  TTS_EXPR_IS( eve::average(v_t(), T()) , T);
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
    TTS_EXPR_IS( eve::average(v_t(), v_t(), v_t()) , v_t);
  }
};

//==================================================================================================
// average tests
//==================================================================================================
EVE_TEST( "Check behavior of average on integer types"
            , eve::test::simd::integers
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T const& a1 )
{
  using eve::average;
  //values can differ by one.
  TTS_ULP_EQUAL( average(a0, a1), T([&](auto i, auto) { return std::midpoint(a0.get(i), a1.get(i)); }), 1);
};

EVE_TEST( "Check behavior of average on integer types"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(eve::valmin, eve::valmax)
                              )
            )
<typename T>( T const& a0, T const& a1, T const& a2 )
{
  using eve::average;
  using eve::diff;
  using eve::as;
  using v_t =  eve::element_type_t<T>;
  TTS_ULP_EQUAL( average(a0, a1), T([&](auto i, auto) { return std::midpoint(a0.get(i), a1.get(i)); }), 2);
  TTS_EQUAL( diff(average)(a0, a2), T([&](auto , auto) { return eve::half(as(v_t())); }));
  TTS_ULP_EQUAL( average(a0, a1, a2), T([&](auto i, auto) { return a0.get(i)/3 + a1.get(i)/3 + a2.get(i)/3; }), 2);
  TTS_EQUAL( diff(average)(a0, a1, a2), T([&](auto , auto) { return v_t(1.0/3.0); }));
};


//==================================================================================================
//  conditional average tests
//==================================================================================================
EVE_TEST( "Check behavior of conditional average on signed types"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(-128, 127)
                              , eve::test::randoms(-128, 127)
                              , eve::test::randoms(-128, 127)
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::average;
  using v_t =  eve::element_type_t<T>;
  //values can differ by one on integral types from scalar to simd implementations (intrinsics may be at work)
  TTS_ULP_EQUAL( average[a2 > T(64)](a0, a1), T([&](auto i, auto) {return a2.get(i) > v_t(64) ? average(a0.get(i), a1.get(i)) :a0.get(i) ; }), 1);
};
