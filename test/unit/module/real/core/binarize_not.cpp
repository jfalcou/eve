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

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of binarize_not"
        , eve::test::simd::all_types
        )
<typename T>(eve::as_<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using wi_t = eve::as_wide_t<i_t, eve::cardinal_t<T>>;
  using wc_t = eve::as_wide_t<std::int8_t, eve::cardinal_t<T>>;
  wc_t z(0);
  std::cout << z;
  using c_t  = eve::element_type_t<wc_t>;
  c_t x(0);   std::cout << x;
  TTS_EXPR_IS( eve::binarize_not(logical<T>())  , T);
  TTS_EXPR_IS( eve::binarize_not(logical<v_t>()), v_t);
  TTS_EXPR_IS( eve::binarize_not(logical<T>(),  eve::as<i_t>()) , wi_t);
  TTS_EXPR_IS( eve::binarize_not(logical<v_t>(), i_t())  , i_t);
  TTS_EXPR_IS( eve::binarize_not(logical<T>(), i_t())  , wi_t);
   using wc_t = eve::as_wide_t<std::int8_t, eve::cardinal_t<T>>; //TODO must work
   using c_t  = eve::element_type_t<wc_t>;
   TTS_EXPR_IS( eve::binarize_not(logical<T>(), eve::as<c_t>())  , wc_t);
};

//==================================================================================================
//== binarize_not tests
//==================================================================================================
EVE_TEST( "Check behavior of binarize_not(wide)"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using eve::zero;
  using eve::one;
  using eve::as;
  using eve::binarize_not;
  using eve::detail::map;
  using ui_t = eve::as_integer_t<v_t, unsigned>;
  using i_t = eve::as_integer_t<v_t, signed>;
  auto ref_binarize_not = [](auto e) -> v_t{ return e < 10 ? zero(as(v_t())) : one(as(v_t())); };
  auto ref_binarize_notu= [](auto e) -> ui_t{ return e< v_t(64) ? 0 :1; };
  auto ref_binarize_noti= [](auto e) ->  i_t{ return e< v_t(64) ? 0 :1; };
  auto ref_binarize_noti2= [](auto e) -> i_t{ return e < i_t(64) ? 0 : 43 ; };
  auto ref_binarize_not2 = [](auto e) -> v_t{ return e < v_t(64)   ?  0 : 43; };
  TTS_IEEE_EQUAL( binarize_not(a0 < T(10)), map(ref_binarize_not, a0));
  TTS_IEEE_EQUAL( binarize_not(a0 < T(64), as<ui_t>()), map(ref_binarize_notu, a0));
  TTS_IEEE_EQUAL( binarize_not(a0 < T(64), as<i_t >()), map(ref_binarize_noti, a0));
  TTS_IEEE_EQUAL( binarize_not(a0 < T(64), v_t(43)), map(ref_binarize_not2, a0));
  TTS_IEEE_EQUAL( binarize_not(a0 < T(64), i_t(43)), map(ref_binarize_noti2, a0));
};
