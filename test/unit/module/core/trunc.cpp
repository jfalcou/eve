//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of trunc"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::trunc(T())  , T);
  TTS_EXPR_IS( eve::trunc(v_t()), v_t);
  TTS_EXPR_IS( eve::int_(eve::trunc)(T())  , eve::as_integer_t<T>);
  TTS_EXPR_IS( eve::int_(eve::trunc)(v_t()), eve::as_integer_t<v_t>);
  TTS_EXPR_IS( eve::uint_(eve::trunc)(T())  , (eve::as_integer_t<T, unsigned>));
  TTS_EXPR_IS( eve::uint_(eve::trunc)(v_t()), (eve::as_integer_t<v_t, unsigned>));

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::tolerant(eve::trunc)(T())  , T);
    TTS_EXPR_IS( eve::tolerant(eve::trunc)(v_t()), v_t);

    
    
  }
};

//==================================================================================================
// tolerant tests
//==================================================================================================
EVE_TEST_TYPES( "Check  with nans and infs"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
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
auto min = []< typename T>(eve::as<T> const &){return eve::signed_value<T> ? -50 : 0; };
EVE_TEST( "Check behavior of trunc on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(min, +50))
        )
<typename T>(T const& a0 )
{
  using wi_t = eve::as_integer_t<T>;
  using uwi_t = eve::as_integer_t<T, unsigned>;
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using ui_t = eve::as_integer_t<v_t, unsigned>;
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL( eve::trunc(a0), T([&](auto i, auto) { return v_t(std::trunc(a0.get(i))); }));
    
    TTS_EQUAL( eve::int_(eve::trunc)(a0), wi_t([&](auto i, auto) { return i_t(a0.get(i)); }));
    TTS_EQUAL( eve::uint_(eve::trunc)(eve::abs(a0)), uwi_t([&](auto i, auto) { return ui_t(std::abs(a0.get(i))); }));
  }
  else
  {
    TTS_EQUAL( eve::trunc(a0),a0);
  }

};
