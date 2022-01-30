//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::logical_and(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::logical_and(logical<T>(), logical<T>()) , logical<T> );
  TTS_EXPR_IS( eve::logical_and(logical<v_t>(), logical<v_t>()) , logical<v_t> );
  TTS_EXPR_IS( eve::logical_and(logical<T>(), logical<v_t>()) , logical<T> );
  TTS_EXPR_IS( eve::logical_and(logical<v_t>(), logical<T>()) , logical<T> );
  TTS_EXPR_IS( eve::logical_and(logical<v_t>(), bool()), logical<v_t> );
  TTS_EXPR_IS( eve::logical_and(logical<T>(), bool())    , logical<T>);
  TTS_EXPR_IS( eve::logical_and(bool(), logical<v_t>()), logical<v_t> );
  TTS_EXPR_IS( eve::logical_and(bool(), logical<T>())    , logical<T>);
  TTS_EXPR_IS( eve::logical_and(bool(),bool())         , bool);
};

//==================================================================================================
//== Tests for eve::logical_and
//==================================================================================================
EVE_TEST( "Check behavior of eve::logical_and(simd)"
        , eve::test::simd::all_types
        , eve::test::generate (eve::test::logicals(0, 3)
                              , eve::test::logicals(1, 2)
                              , eve::test::randoms(0, 2))
        )
<typename M, typename T>(M const& l0, M const& l1, T const & a0)
{
  using eve::detail::map;
  using l_t = eve::element_type_t<M>;

  TTS_EQUAL(eve::logical_and(l0, true), map([](auto e) -> l_t { return  e; }, l0));
  TTS_EQUAL(eve::logical_and(true, l1), map([](auto e) -> l_t { return  e; }, l1));
  TTS_EQUAL(eve::logical_and(l0, true), map([](auto e) -> l_t { return  e; }, l0));
  TTS_EQUAL(eve::logical_and(l0, false), eve::false_(eve::as<M>()));
  TTS_EQUAL(eve::logical_and(l0, l1), map([](auto e, auto f) -> l_t { return  e && f; }, l0, l1));
  TTS_EQUAL(eve::logical_and(l0, l1.get(0)), map([&](auto e) -> l_t { return  e && l1.get(0); }, l0));
  TTS_EQUAL(eve::logical_and(l0.get(0), l1), map([&](auto f) -> l_t { return  l0.get(0) && f; }, l1));
  using v_t = eve::element_type_t<T>;
  using d_t = eve::detail::downgrade_t<v_t>;
  auto da0 = eve::convert(a0, eve::as<d_t>());
  using dl_t = eve::as_logical_t<d_t>;
  TTS_EQUAL(eve::logical_and(l1, da0 > 1), map([](auto e, auto f) -> l_t { return (f > 1) && e; }, l1, da0));
  TTS_EQUAL(eve::logical_and( da0 > 1, l1), map([](auto e, auto f) -> dl_t { return bool((e > 1) && f); }, da0, l1));
};
