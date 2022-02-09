//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_lessgreater(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_lessgreater(T(), T())     , logical<T>   );
  TTS_EXPR_IS( eve::is_lessgreater(v_t(), v_t()) , logical<v_t> );
  TTS_EXPR_IS( eve::is_lessgreater(T(), v_t())   , logical<T> );
  TTS_EXPR_IS( eve::is_lessgreater(v_t(), T())   , logical<T> );
};

//==================================================================================================
//== Tests for eve::is_lessgreater
//==================================================================================================
EVE_TEST( "Check behavior of eve::is_lessgreater(simd)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::ramp(0)
                              , eve::test::reverse_ramp(4, 2)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, T const& a1, M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_lessgreater(a0, a1), map([](auto e, auto f) -> eve::logical<v_t> { return (e < f) || (e > f); }, a0, a1));
  TTS_EQUAL(eve::is_lessgreater(a0, a0), map([](auto e, auto f) -> eve::logical<v_t> { return (e < f) || (e > f); }, a0, a0));
  TTS_EQUAL(eve::is_lessgreater(a0, v_t(1)), map([](auto e) -> eve::logical<v_t> { return (e < v_t(1)) || (e > v_t(1)); }, a0));
  TTS_EQUAL(eve::is_lessgreater[t](a0, a1), eve::if_else(t, eve::is_lessgreater(a0, a1), eve::false_(eve::as(a0))));
};
