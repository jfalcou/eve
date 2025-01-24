//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

template<typename T, typename U, typename Expected, typename F>
void test_with_types(F f)
{
  TTS_TYPE_IS(decltype(f(T{}, U{})), Expected);
  TTS_TYPE_IS(decltype(f(U{}, T{})), Expected);
}

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_less(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::is_less(T(), T()), eve::logical<T>);
  TTS_EXPR_IS(eve::is_less(v_t(), v_t()), eve::logical<v_t>);

  test_with_types<T, v_t, eve::logical<T>>(eve::is_less);

  if constexpr (eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::is_less[eve::definitely](T(), T()), eve::logical<T>);
    TTS_EXPR_IS(eve::is_less[eve::definitely](v_t(), v_t()), eve::logical<v_t>);

    test_with_types<T, v_t, eve::logical<T>>(eve::is_less[eve::definitely]);
  }
};

TTS_CASE_TPL("Check return types of eve::is_less(simd) with mixed types", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using D = eve::downgrade_t<T>;
  using vd_t = eve::element_type_t<D>;

  test_with_types<T, vd_t, eve::logical<T>>(eve::is_less);
};

//==================================================================================================
//== Tests for eve::is_less
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::is_less(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, M const& t)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_less(a0, a1),
            tts::map([](auto e, auto f) -> eve::logical<v_t> { return e < f; }, a0, a1));
  TTS_EQUAL(eve::is_less(a0, a0),
            tts::map([](auto e, auto f) -> eve::logical<v_t> { return e < f; }, a0, a0));
  TTS_EQUAL(eve::is_less(a0, v_t(1)),
            tts::map([](auto e) -> eve::logical<v_t> { return e < v_t(1); }, a0));
  TTS_EQUAL(eve::is_less[t](a0, a1),
            eve::if_else(t, eve::is_less(a0, a1), eve::false_(eve::as(a0))));
};

//==================================================================================================
//== Tests for eve::is_less corner cases for floating
//==================================================================================================
TTS_CASE_TPL("Check behavior of eve::is_less(simd) corner cases", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> const&)
{
  using eve::as;
  using v_t  = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<v_t, unsigned>;

  TTS_EQUAL(eve::is_less[eve::definitely](T(1), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely](T(1), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely](T(1), T(3)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely](T(1), v_t(3)), eve::true_(eve::as<T>()));

  TTS_EQUAL(eve::is_less[eve::definitely =  eve::eps(as<v_t>())](T(1 - eve::eps(as<T>())), T(1)),    eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely =  eve::eps(as<v_t>())](T(1 - 2 * eve::eps(as<T>())), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely =  eve::eps(as<v_t>())](T(1 - eve::eps(as<T>())), v_t(1)),   eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely =  eve::eps(as<v_t>())](T(1), T(3)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely =  eve::eps(as<v_t>())](T(1), v_t(3)),  eve::true_(eve::as<T>()));

  TTS_EQUAL(eve::is_less[eve::definitely = ui_t(3)](T(1), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely= ui_t(3)](T(1), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely= ui_t(3)](T(1), T(3)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less[eve::definitely= ui_t(3)](T(1), v_t(3)), eve::true_(eve::as<T>()));

  if constexpr( eve::platform::supports_denormals )
  {
    auto md = eve::mindenormal(eve::as<v_t>());
    TTS_EQUAL(eve::is_less[eve::definitely = ui_t(3)](v_t(-md), T(0)), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_less[eve::definitely = ui_t(3)](v_t(-2 * md), T(0)),     eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_less[eve::definitely = ui_t(3)](v_t(-3 * md), T(0)),     eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_less[eve::definitely = ui_t(3)](v_t(-4 * md), T(0)), eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_less[eve::definitely = ui_t(3)](v_t(1), v_t(1)), eve::false_(eve::as<v_t>()));
  }
};
