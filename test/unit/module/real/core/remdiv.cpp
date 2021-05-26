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
#include <eve/function/remdiv.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/div.hpp>


//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of remdiv"
          , eve::test::simd::all_types
          )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  using tup_t = kumi::tuple < T, T >;
  //regular
  TTS_EXPR_IS( eve::remdiv(T(), T()  ) , tup_t);
  TTS_EXPR_IS( eve::remdiv(T(), v_t()) , tup_t);
  TTS_EXPR_IS( eve::remdiv(v_t(), T()) , tup_t);
  TTS_EXPR_IS( eve::remdiv(v_t(), v_t()) , (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
//==  remdiv simd tests
//==================================================================================================
auto mini = [] < typename T > (eve::as_<T> const &){ return std::is_signed_v<eve::element_type_t<T>> ? -100 : 1;};

EVE_TEST( "Check behavior of remdiv on wide"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(mini, 100)
                              , eve::test::randoms(mini, 100)
                              )
        )
  <typename T>(T a0, T a1)
{
  using eve::remdiv;
  using eve::detail::map;
  using eve::toward_zero;
  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  auto [r, d] = eve::remdiv(a0, a1);
  TTS_ULP_EQUAL( r, map([](auto e, auto f) { return eve::rem(e, f); }, a0, a1), 30);//fma not avail scalar double it seems
  TTS_ULP_EQUAL( d, map([](auto e, auto f) { return toward_zero(eve::div)(e, f); }, a0, a1), 30);//fma not avail scalar double it seems

};


//==================================================================================================
//== Test for fixed values
//==================================================================================================
EVE_TEST( "Check fixed-cases behavior of eve::remdiv"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::limits())
        )
<typename Z>(Z)
{
  using T =  typename Z::type;
  using v_t = eve::element_type_t<T>;
  using eve::toward_zero;

  if constexpr(eve::signed_value<T>)
  {
    {
      auto [r, d] = eve::remdiv(T(-1),   T(2));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(0));
    }
    {
      auto [r, d] = eve::remdiv(v_t(-1), T(2));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(0));
    }
    {
      auto [r, d] = eve::remdiv(T(-1), v_t(2));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(0));
    }
    {
      auto [r, d] = eve::remdiv(T(-4),   T(3));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(-1));
    }
    {
      auto [r, d] = eve::remdiv(T(-4), v_t(3));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(-1));
    }
    {
      auto [r, d] = eve::remdiv(T(4),   T(-3));
      TTS_EQUAL(r, T( 1));
      TTS_EQUAL(d, T(-1));
    }
    {
      auto [r, d] = eve::remdiv(T(4), v_t(-3));
      TTS_EQUAL(r, T( 1));
      TTS_EQUAL(d, T(-1));
    }
  }
  {
    auto [r, d] = eve::remdiv(T(12), T(4));
    TTS_EQUAL(r, T(0));
    TTS_EQUAL(d, T(3));
  }
  {
    auto [r, d] = eve::remdiv(T(1), T(2));
    TTS_EQUAL(r, T(1));
    TTS_EQUAL(d, T(0));
  }
  {
    auto [r, d] = eve::remdiv(T(4), T(3));
    TTS_EQUAL(r, T(1));
    TTS_EQUAL(d, T(1));
  }
  {
    auto [r, d] = eve::remdiv(T(3), T(4));
    TTS_EQUAL(r, T(3));
    TTS_EQUAL(d, T(0));
  }
};
