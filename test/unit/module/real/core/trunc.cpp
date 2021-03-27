//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/fuzzy/trunc.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/diff/trunc.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of trunc"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::trunc(T())  , T);
  TTS_EXPR_IS( eve::trunc(v_t()), v_t);
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::tolerant(eve::trunc)(T())  , T);
    TTS_EXPR_IS( eve::tolerant(eve::trunc)(v_t()), v_t);

    TTS_EXPR_IS( eve::diff(eve::trunc)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::trunc)(v_t()), v_t);
  }
};

//==================================================================================================
// tolerant tests
//==================================================================================================
EVE_TEST( "Check  with nans and infs"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::no_data)
        )<typename T>(T)
{
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-eve::eps(eve::as<T>()))), T(1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-2*eve::eps(eve::as<T>()))), T(1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-3*eve::eps(eve::as<T>()))), T(1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::inc(-4*eve::eps(eve::as<T>()))), T(0));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(eve::eps(eve::as<T>()))), T(-1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(2*eve::eps(eve::as<T>()))), T(-1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(3*eve::eps(eve::as<T>()))), T(-1));
  TTS_EQUAL(eve::tolerant(eve::trunc)(eve::dec(4*eve::eps(eve::as<T>()))), T(0));
};

//==================================================================================================
// trunc signed tests
//==================================================================================================
auto min = []< typename T>(eve::as_<T> const &){return eve::signed_value<T> ? -50 : 0; };
EVE_TEST( "Check behavior of trunc on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(min, +50))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL( eve::trunc(a0), T([&](auto i, auto) { return v_t(std::trunc(a0.get(i))); }));
    TTS_EQUAL( eve::diff(eve::trunc)(a0), eve::zero(as(a0)));
  }
  else
  {
    TTS_EQUAL( eve::trunc(a0),a0);
  }

};
