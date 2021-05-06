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
#include <eve/function/binarize.hpp>
#include <eve/logical.hpp>
#include <eve/function/is_less.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of binarize"
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
  TTS_EXPR_IS( eve::binarize(logical<T>())  , T);
  TTS_EXPR_IS( eve::binarize(logical<v_t>()), v_t);
  TTS_EXPR_IS( eve::binarize(logical<T>(),  eve::as<i_t>()) , wi_t);
  TTS_EXPR_IS( eve::binarize(logical<v_t>(), i_t())  , i_t);
  TTS_EXPR_IS( eve::binarize(logical<T>(), i_t())  , wi_t);
   using wc_t = eve::as_wide_t<std::int8_t, eve::cardinal_t<T>>; //TODO must work
   using c_t  = eve::element_type_t<wc_t>;
   TTS_EXPR_IS( eve::binarize(logical<T>(), eve::as<c_t>())  , wc_t);
};

//==================================================================================================
//== binarize tests
//==================================================================================================
EVE_TEST( "Check behavior of binarize(wide)"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using eve::zero;
  using eve::one;
  using eve::as;
  using eve::binarize;
  using eve::detail::map;
  using ui_t = eve::as_integer_t<v_t, unsigned>;
  using i_t = eve::as_integer_t<v_t, signed>;
  auto ref_binarize = [](auto e) -> v_t{ return e < 10 ? one(as(v_t())) : zero(as(v_t())); };
  auto ref_binarizeu= [](auto e) -> ui_t{ return e< v_t(64) ? 1 : 0; };
  auto ref_binarizei= [](auto e) ->  i_t{ return e< v_t(64) ? 1 : 0; };
  auto ref_binarizei2= [](auto e) -> i_t{ return e < i_t(64) ? 43: 0; };
  auto ref_binarize2 = [](auto e) -> v_t{ return e < v_t(64)   ? 43: 0; };
  TTS_IEEE_EQUAL( binarize(a0 < T(10)), map(ref_binarize, a0));
  TTS_IEEE_EQUAL( binarize(a0 < T(64), as<ui_t>()), map(ref_binarizeu, a0));
  TTS_IEEE_EQUAL( binarize(a0 < T(64), as<i_t >()), map(ref_binarizei, a0));
  TTS_IEEE_EQUAL( binarize(a0 < T(64), v_t(43)), map(ref_binarize2, a0));
  TTS_IEEE_EQUAL( binarize(a0 < T(64), i_t(43)), map(ref_binarizei2, a0));
};


