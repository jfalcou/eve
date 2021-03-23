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
#include <eve/constant/one.hpp>
#include <eve/function/frac.hpp>
#include <eve/function/diff/frac.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of frac"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::frac(T())  , T);
  TTS_EXPR_IS( eve::frac(v_t()), v_t);
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::frac)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::frac)(v_t()), v_t);
  }
  // corner cases
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPECT(eve::all(eve::is_negative(eve::frac(T(-0.0)))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::frac(T(0.0)))));
  }
};



//==================================================================================================
// frac signed tests
//==================================================================================================
EVE_TEST( "Check behavior of frac on signed wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  TTS_EQUAL( eve::frac(a0), T([&](auto i, auto) { auto z = a0.get(i); return z-std::trunc(z); }));
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL( eve::diff( eve::frac)(a0), eve::one(as(a0)));
  }

};
