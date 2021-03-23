/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/dist.hpp>
#include <eve/function/saturated/dist.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of dist"
        , eve::test::simd::all_types
        
        )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::dist(T(), T()  ) , T);
  TTS_EXPR_IS( eve::dist(T(), v_t()) , T);
  TTS_EXPR_IS( eve::dist(v_t(), T()) , T);
  TTS_EXPR_IS( eve::dist(v_t(), v_t()) , v_t);
};

//==================================================================================================
//== dist tests
//==================================================================================================
auto valmino2 = []< typename T>(eve::as_<T> const &){return eve::valmin(eve::as(eve::element_type_t<T>()))/2;};
auto valmaxo2 = []< typename T>(eve::as_<T> const &){return eve::valmax(eve::as(eve::element_type_t<T>()))/2;};

EVE_TEST( "Check behavior of dist on signed integral wide"
        , eve::test::simd::signed_integers
        , eve::test::generate ( eve::test::randoms(valmino2, valmaxo2)
                              , eve::test::randoms(valmino2, valmaxo2)
                              )
        )
<typename T>(T const& a0, T const& a1 )
{
  using eve::dist;
  TTS_ULP_EQUAL( dist(a0, a1), T([&](auto i, auto) { return std::abs(a0.get(i)-a1.get(i)); }), 1);
  TTS_ULP_EQUAL( eve::saturated(dist)(a0, a1), T([&](auto i, auto) { return std::abs(a0.get(i)-a1.get(i)); }), 1);
};

using eve::valmin;
using eve::valmax;

EVE_TEST( "Check behavior of dist on unsigned integral wide"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(valmin, valmax)
                                  , eve::test::randoms(valmin, valmax)
                                  )
            )
<typename T>(T const& a0, T const& a1 )
{
  using eve::dist;
  TTS_ULP_EQUAL( dist(a0, a1), T([&](auto i, auto) { return std::max(a0.get(i), a1.get(i))
                                                           -std::min(a0.get(i), a1.get(i)); }), 1);
  TTS_ULP_EQUAL( eve::saturated(dist)(a0, a1), T([&](auto i, auto) { return std::max(a0.get(i), a1.get(i))
                                                           -std::min(a0.get(i), a1.get(i)); }), 1);
};
