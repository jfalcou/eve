//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/logical_notand.hpp>
#include <eve/logical.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::logical_notand(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::logical_notand(logical<T>(), logical<T>()) , logical<T> );
  TTS_EXPR_IS( eve::logical_notand(logical<v_t>(), logical<v_t>()) , logical<v_t> );
  TTS_EXPR_IS( eve::logical_notand(logical<T>(), logical<v_t>()) , logical<T> );
  TTS_EXPR_IS( eve::logical_notand(logical<v_t>(), logical<T>()) , logical<T> );
  TTS_EXPR_IS( eve::logical_notand(logical<v_t>(), bool()), logical<v_t> );
  TTS_EXPR_IS( eve::logical_notand(logical<T>(), bool())    , logical<T>);
  TTS_EXPR_IS( eve::logical_notand(bool(), logical<v_t>()), logical<v_t> );
  TTS_EXPR_IS( eve::logical_notand(bool(), logical<T>())    , logical<T>);
  TTS_EXPR_IS( eve::logical_notand(bool(),bool())         , bool);
};

//==================================================================================================
//== Tests for eve::logical_notand
//==================================================================================================
EVE_TEST( "Check behavior of eve::logical_notand(simd)"
        , eve::test::simd::all_types
        , eve::test::generate (eve::test::logicals(0, 3)
                              , eve::test::logicals(1, 2))
        )
<typename M>(M const& l0, M const& l1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<M>;

  TTS_EQUAL(eve::logical_notand(l0, true), map([](auto e) -> v_t { return  !e; }, l0));
  TTS_EQUAL(eve::logical_notand(true, l1), eve::false_(eve::as<M>()));
  TTS_EQUAL(eve::logical_notand(false, l1), map([](auto e) -> v_t { return  e; }, l1));
  TTS_EQUAL(eve::logical_notand(l0, false), eve::false_(eve::as<M>()));
  TTS_EQUAL(eve::logical_notand(l0, l1), map([](auto e, auto f) -> v_t { return  !e && f; }, l0, l1));
  TTS_EQUAL(eve::logical_notand(l0, l1.get(0)), map([&](auto e) -> v_t { return  !e && l1.get(0); }, l0));
  TTS_EQUAL(eve::logical_notand(l0.get(0), l1), map([&](auto f) -> v_t { return  !l0.get(0) && f; }, l1));
};
