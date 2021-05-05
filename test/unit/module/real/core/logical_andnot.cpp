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
#include <eve/function/logical_andnot.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::logical_andnot(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::logical_andnot(logical<T>(), logical<T>()) , logical<T> );
  TTS_EXPR_IS( eve::logical_andnot(logical<v_t>(), logical<v_t>()) , logical<v_t> );
  TTS_EXPR_IS( eve::logical_andnot(logical<T>(), logical<v_t>()) , logical<T> );
  TTS_EXPR_IS( eve::logical_andnot(logical<v_t>(), logical<T>()) , logical<T> );
  TTS_EXPR_IS( eve::logical_andnot(logical<v_t>(), bool()), logical<v_t> );
  TTS_EXPR_IS( eve::logical_andnot(logical<T>(), bool())    , logical<T>);
  TTS_EXPR_IS( eve::logical_andnot(bool(), logical<v_t>()), logical<v_t> );
  TTS_EXPR_IS( eve::logical_andnot(bool(), logical<T>())    , logical<T>);
  TTS_EXPR_IS( eve::logical_andnot(bool(),bool())         , bool);
};

//==================================================================================================
//== Tests for eve::logical_andnot
//==================================================================================================
EVE_TEST( "Check behavior of eve::logical_andnot(simd)"
        , eve::test::simd::all_types
        , eve::test::generate (eve::test::logicals(0, 3)
                              , eve::test::logicals(1, 2))
        )
<typename M>(M const& l0, M const& l1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<M>;

    TTS_EQUAL(eve::logical_andnot(l0, true), eve::false_(eve::as<M>()));
    TTS_EQUAL(eve::logical_andnot(true, l1), map([](auto e) -> v_t { return  !e; }, l1));
    TTS_EQUAL(eve::logical_andnot(false, l1), eve::false_(eve::as<M>()));
    TTS_EQUAL(eve::logical_andnot(l0, false), map([](auto e) -> v_t { return  e; }, l0));
    TTS_EQUAL(eve::logical_andnot(l0, l1), map([](auto e, auto f) -> v_t { return  e && !f; }, l0, l1));
    TTS_EQUAL(eve::logical_andnot(l0, l1.get(0)), map([&](auto e) -> v_t { return  e && !l1.get(0); }, l0));
    TTS_EQUAL(eve::logical_andnot(l0.get(0), l1), map([&](auto f) -> v_t { return  l0.get(0) && !f; }, l1));
};
