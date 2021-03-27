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
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/binarize_not.hpp>
#include <eve/logical.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of binarize_not on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::no_data)
        )
<typename T>(T)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using wi_t = eve::as_wide_t<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::binarize_not(logical<T>())  , T);
  TTS_EXPR_IS( eve::binarize_not(logical<v_t>()), v_t);
  TTS_EXPR_IS( eve::binarize_not(logical<T>(),  eve::as<i_t>()) , wi_t);
  TTS_EXPR_IS( eve::binarize_not(logical<v_t>(), i_t())  , i_t);
  TTS_EXPR_IS( eve::binarize_not(logical<T>(), i_t())  , wi_t);

};

//==================================================================================================
//== binarize_not tests
//==================================================================================================
EVE_TEST( "Check behavior of binarize_not on wide"
            , eve::test::simd::ieee_reals
            , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
            )
<typename T>( T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  using eve::zero;
  using eve::one;
  using eve::as;
  using eve::binarize_not;
  using ui_t = eve::as_integer_t<v_t, unsigned>;
  using wui_t = eve::as_wide_t<ui_t, eve::cardinal_t<T>>;
  using i_t = eve::as_integer_t<v_t, signed>;
  using wi_t = eve::as_wide_t<i_t, eve::cardinal_t<T>>;
  auto ref_binarize_not = [&](auto i, auto) { return a0.get(i) < 10 ?  zero(as(v_t())) : one(as(v_t())); };
  auto ref_binarize_noti= [&](auto i, auto) { return a0.get(i) < i_t(64) ? 0 : 1; };
  auto ref_binarize_not2= [&](auto i, auto) { return a0.get(i) < i_t(64) ? 0 : 43; };
  TTS_IEEE_EQUAL( binarize_not(a0 < T(10)), T(ref_binarize_not));
  TTS_IEEE_EQUAL( binarize_not(a0 < T(64), as<ui_t>()), wui_t(ref_binarize_noti));
  TTS_IEEE_EQUAL( binarize_not(a0 < T(64), as<i_t >()), wi_t(ref_binarize_noti));
  TTS_IEEE_EQUAL( binarize_not(a0 < T(64), v_t(43)), T(ref_binarize_not2));
  TTS_IEEE_EQUAL( binarize_not(a0 < T(64), i_t(43)), wi_t(ref_binarize_not2));
};
