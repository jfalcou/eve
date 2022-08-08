//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::logical_andnot(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::logical_andnot(logical<T>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(eve::logical_andnot(logical<v_t>(), logical<v_t>()), logical<v_t>);
  TTS_EXPR_IS(eve::logical_andnot(logical<T>(), logical<v_t>()), logical<T>);
  TTS_EXPR_IS(eve::logical_andnot(logical<v_t>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(eve::logical_andnot(logical<v_t>(), bool()), logical<v_t>);
  TTS_EXPR_IS(eve::logical_andnot(logical<T>(), bool()), logical<T>);
  TTS_EXPR_IS(eve::logical_andnot(bool(), logical<v_t>()), logical<v_t>);
  TTS_EXPR_IS(eve::logical_andnot(bool(), logical<T>()), logical<T>);
  TTS_EXPR_IS(eve::logical_andnot(bool(), bool()), bool);
};

//==================================================================================================
//== Tests for eve::logical_andnot
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::logical_andnot(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(0, 3), tts::logicals(1, 2), tts::randoms(0, 2)))
<typename M, typename T>(M const& l0, M const& l1, T const& a0)
{
  using eve::detail::map;
  using l_t = eve::element_type_t<M>;

  TTS_EQUAL(eve::logical_andnot(l0, true), eve::false_(eve::as<M>()));
  TTS_EQUAL(eve::logical_andnot(true, l1), map([](auto e) -> l_t { return !e; }, l1));
  TTS_EQUAL(eve::logical_andnot(false, l1), eve::false_(eve::as<M>()));
  TTS_EQUAL(eve::logical_andnot(l0, false), map([](auto e) -> l_t { return e; }, l0));
  TTS_EQUAL(eve::logical_andnot(l0, l1),
            map([](auto e, auto f) -> l_t { return e && !f; }, l0, l1));
  TTS_EQUAL(eve::logical_andnot(l0, l1.get(0)),
            map([&](auto e) -> l_t { return e && !l1.get(0); }, l0));
  TTS_EQUAL(eve::logical_andnot(l0.get(0), l1),
            map([&](auto f) -> l_t { return l0.get(0) && !f; }, l1));
  using v_t  = eve::element_type_t<T>;
  using d_t  = eve::detail::downgrade_t<v_t>;
  auto da0   = eve::convert(a0, eve::as<d_t>());
  using dl_t = eve::as_logical_t<d_t>;
  TTS_EQUAL(eve::logical_andnot(l1, da0 > 1),
            map([](auto e, auto f) -> l_t { return !(f > 1) && e; }, l1, da0));
  TTS_EQUAL(eve::logical_andnot(da0 > 1, l1),
            map([](auto e, auto f) -> dl_t { return dl_t((e > 1) && !f); }, da0, l1));
};
