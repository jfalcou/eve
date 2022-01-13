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
#include <eve/constant/eps.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/diff/floor.hpp>
#include <eve/function/fuzzy/floor.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of floor"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::floor(T())  , T);
  TTS_EXPR_IS( eve::floor(v_t()), v_t);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::tolerant(eve::floor)(T())  , T);
    TTS_EXPR_IS( eve::tolerant(eve::floor)(v_t()), v_t);

    TTS_EXPR_IS( eve::diff(eve::floor)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::floor)(v_t()), v_t);
  }
};


//==================================================================================================
// tolerant tests
//==================================================================================================
EVE_TEST_TYPES( "Check  with particular values"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  TTS_EQUAL(eve::floor(static_cast<T>(-1.3)), T(-2));
  TTS_EQUAL(eve::floor(static_cast<T>(-1.5)), T(-2));
  TTS_EQUAL(eve::floor(static_cast<T>(-1.6)), T(-2));
  TTS_EQUAL(eve::floor(static_cast<T>(1.3)) , T( 1));
  TTS_EQUAL(eve::floor(static_cast<T>(1.5)) , T( 1));
  TTS_EQUAL(eve::floor(static_cast<T>(1.6)) , T( 1));

  TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(-1.3)), T(-2));
  TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(-1.5)), T(-2));
  TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(-1.6)), T(-2));
  TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(1.3)) , T( 1));
  TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(1.5)) , T( 1));
  TTS_EQUAL(eve::tolerant(eve::floor)(static_cast<T>(1.6)) , T( 1));

  auto epsi = eve::eps(eve::as<T>());
  TTS_EQUAL(eve::tolerant(eve::floor)(T(0)), T(0));
  TTS_EQUAL(eve::tolerant(eve::floor)(-epsi), T(0));
  TTS_EQUAL(eve::tolerant(eve::floor)((-2*epsi)), T(0));
  TTS_EQUAL(eve::tolerant(eve::floor)((-3*epsi)), T(0));
  TTS_EQUAL(eve::tolerant(eve::floor)((-4*epsi)), T(-1));

  TTS_EQUAL(eve::tolerant(eve::floor)(T(1)), T(1));
  TTS_EQUAL(eve::tolerant(eve::floor)((T(1)-epsi)), T(1));
  TTS_EQUAL(eve::tolerant(eve::floor)((T(1)-2*epsi)), T(1));
  TTS_EQUAL(eve::tolerant(eve::floor)((T(1)-3*epsi)), T(1));
  TTS_EQUAL(eve::tolerant(eve::floor)((T(1)-4*epsi)), T(0));

  TTS_EQUAL(eve::tolerant(eve::floor)(T(45)), T(45));
  TTS_EQUAL(eve::tolerant(eve::floor)(45*(T(1)-2*epsi)), T(45));
  TTS_EQUAL(eve::tolerant(eve::floor)(45*(T(1)-3*epsi)), T(45));
  TTS_EQUAL(eve::tolerant(eve::floor)(45*(T(1)-4*epsi)), T(44));


  TTS_EQUAL(eve::tolerant(eve::floor)(T(1)), T(1));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(1), 1), 3), T(1));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(1), 2), 3), T(1));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(1), 3), 3), T(1));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(1), 4), 3), T(0));

  TTS_EQUAL(eve::tolerant(eve::floor)(T(45)), T(45));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(45), 1), 3), T(45));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(45), 2), 3), T(45));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(45), 3), 3), T(45));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(45), 4), 3), T(44));

  TTS_EQUAL(eve::tolerant(eve::floor)(T(-45)), T(-45));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(-45), 1), 3), T(-45));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(-45), 2), 3), T(-45));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(-45), 3), 3), T(-45));
  TTS_EQUAL(eve::tolerant(eve::floor)(eve::prev(T(-45), 4), 3), T(-46));
};


//==================================================================================================
// floor(simd)  tests
//==================================================================================================
auto min = []< typename T>(eve::as<T> const &){return eve::signed_value<T> ? -50 : 0; };
EVE_TEST( "Check behavior of floor(wide) and diff(floor(wide))"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(min, +50))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL( eve::floor(a0), map([&](auto e) -> v_t{ return v_t(std::floor(e)); }, a0));
    TTS_EQUAL( eve::diff(eve::floor)(a0), eve::zero(eve::as(a0)));
  }
  else
  {
    TTS_EQUAL( eve::floor(a0),a0);
  }
};
