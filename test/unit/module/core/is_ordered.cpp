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
TTS_CASE_TPL( "Check return types of eve::is_ordered(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_ordered(T(), T())     , logical<T>   );
  TTS_EXPR_IS( eve::is_ordered(v_t(), v_t()) , logical<v_t> );
  TTS_EXPR_IS( eve::is_ordered(T(), v_t())   , logical<T> );
  TTS_EXPR_IS( eve::is_ordered(v_t(), T())   , logical<T> );
};

//==================================================================================================
//== Tests for eve::is_ordered
//==================================================================================================
TTS_CASE_WITH( "Check behavior of eve::is_ordered(simd)"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::ramp(0)
                              , tts::reverse_ramp(4, 2)
                              , tts::logicals(0, 3))
        )
<typename T, typename M>(T a0, T const& a1, M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  a0.set(0, eve::nan(eve::as<v_t>()));
  TTS_EQUAL(eve::is_ordered(a0, a1), map([](auto e, auto f) -> eve::logical<v_t> { return  (e == e) && (f == f); }, a0, a1));
  TTS_EQUAL(eve::is_ordered(a0, v_t(1)), map([](auto e) -> eve::logical<v_t> { return  (e == e); }, a0));
  TTS_EQUAL(eve::is_ordered(v_t(14), a1), map([](auto e) -> eve::logical<v_t> { return (e == e); }, a1));
  TTS_EQUAL(eve::is_ordered[t](a0, a1), eve::if_else(t, eve::is_ordered(a0, a1), eve::false_(eve::as(a0))));
};

//==================================================================================================
//== Tests for eve::is_ordered corner cases for floating
//==================================================================================================
TTS_CASE_TPL( "Check behavior of eve::is_ordered(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> tgt)
{
  using v_t = eve::element_type_t<T>;
  using eve::detail::map;
  using eve::as;

  auto cases = tts::limits(tgt);

  TTS_EQUAL(eve::is_ordered(cases.nan, cases.nan ) , eve::false_(as<T>()));
  TTS_EQUAL(eve::is_ordered(cases.nan, T(1)      ) , eve::false_(as<T>()));
  TTS_EQUAL(eve::is_ordered(T(1), cases.nan      ) , eve::false_(as<T>()));
  TTS_EQUAL(eve::is_ordered(T(1), T(1)           ) , eve::true_(as<T>()));
  TTS_EQUAL(eve::is_ordered(T(1), v_t(1)         ) , eve::true_(as<T>()));
};
