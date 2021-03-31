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
#include <eve/function/ceil.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/diff/ceil.hpp>
#include <eve/function/fuzzy/ceil.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ceil"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ceil(T())  , T);
  TTS_EXPR_IS( eve::ceil(v_t()), v_t);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::tolerant(eve::ceil)(T())  , T);
    TTS_EXPR_IS( eve::tolerant(eve::ceil)(v_t()), v_t);

    TTS_EXPR_IS( eve::diff(eve::ceil)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::ceil)(v_t()), v_t);
  }
};

//==================================================================================================
// tolerant tests
//==================================================================================================
EVE_TEST_TYPES( "Check  with nans and infs"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as_<T>)
{
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-2)), T(-2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(0)), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1)), T(1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(2)), T(2));

  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.3)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.5)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(-1.6)), T(-1));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.3)) , T(2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.5)) , T(2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(1.6)) , T(2));
  TTS_EQUAL(eve::tolerant(eve::ceil)(T(0)), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(2*eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(3*eve::eps(eve::as<T>())), T(0));
  TTS_EQUAL(eve::tolerant(eve::ceil)(4*eve::eps(eve::as<T>())), T(1));
};


//==================================================================================================
// ceil  tests
//==================================================================================================
auto min = []< typename T>(eve::as_<T> const &){return eve::signed_value<T> ? -50 : 0; };
EVE_TEST( "Check behavior of ceil on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(min, +50))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL( eve::ceil(a0), T([&](auto i, auto) { return v_t(std::ceil(a0.get(i))); }));
    TTS_EQUAL( eve::diff(eve::ceil)(a0), eve::zero(as(a0)));
  }
  else
  {
    TTS_EQUAL( eve::ceil(a0),a0);
  }

};
