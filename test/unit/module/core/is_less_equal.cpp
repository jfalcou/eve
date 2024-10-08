//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_less_equal(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_less_equal(T(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_less_equal(v_t(), v_t()), logical<v_t>);
  TTS_EXPR_IS(eve::is_less_equal(T(), v_t()), logical<T>);
  TTS_EXPR_IS(eve::is_less_equal(v_t(), T()), logical<T>);

  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::is_less_equal[eve::almost](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost](v_t(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost = unsigned()](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost = unsigned()](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost = unsigned()](v_t(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost = v_t()](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost = v_t()](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost = v_t()](v_t(), T()), logical<T>);
    using ui_t = eve::as_integer_t<v_t, unsigned>;
    TTS_EXPR_IS(eve::is_less_equal[eve::almost = ui_t()](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost = ui_t()](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_less_equal[eve::almost = ui_t()](v_t(), T()), logical<T>);
  }
};

//==================================================================================================
//== Tests for eve::is_less_equal
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::is_less_equal(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, M const& t)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_less_equal(a0, a1),
            tts::map([](auto e, auto f) -> eve::logical<v_t> { return e <= f; }, a0, a1));
  TTS_EQUAL(eve::is_less_equal(a0, a0),
            tts::map([](auto e, auto f) -> eve::logical<v_t> { return e <= f; }, a0, a0));
  TTS_EQUAL(eve::is_less_equal(a0, v_t(1)),
            tts::map([](auto e) -> eve::logical<v_t> { return e <= v_t(1); }, a0));
  TTS_EQUAL(eve::is_less_equal[t](a0, a1),
            eve::if_else(t, eve::is_less_equal(a0, a1), eve::false_(eve::as(a0))));
};

//==================================================================================================
//== Tests for eve::is_less_equal corner cases for floating
//==================================================================================================
TTS_CASE_TPL("Check behavior of eve::is_less_equal(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> const&)
{
  using eve::as;
  using eve::logical;
  using v_t  = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_less_equal[eve::almost](T(1), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost](T(1), v_t(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost](T(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost](T(3), v_t(1)), eve::false_(eve::as<T>()));

  TTS_EQUAL(eve::is_less_equal[eve::almost =  eve::eps(as<v_t>())](T(1 + eve::eps(as<T>())), T(1)),  eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost =  eve::eps(as<v_t>())](T(1 + 2 * eve::eps(as<T>())), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost =  eve::eps(as<v_t>())](T(1 + eve::eps(as<T>())), v_t(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost =  eve::eps(as<v_t>())](T(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost =  eve::eps(as<v_t>())](T(3), v_t(1)), eve::false_(eve::as<T>()));

  using ui_t = eve::as_integer_t<v_t, unsigned>;

  TTS_EQUAL(eve::is_less_equal[eve::almost = ui_t(3)](T(1), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost = ui_t(3)](T(1), v_t(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost = ui_t(3)](T(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_less_equal[eve::almost = ui_t(3)](T(3), v_t(1)), eve::false_(eve::as<T>()));

  if constexpr( eve::platform::supports_denormals )
  {
    auto md = eve::mindenormal(eve::as<v_t>());

    TTS_EQUAL(eve::is_less_equal[eve::almost = ui_t(3)](v_t(md), T(0)), eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_less_equal[eve::almost = ui_t(3)](v_t(2 * md), T(0)),
              eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_less_equal[eve::almost = ui_t(3)](v_t(3 * md), T(0)),
              eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_less_equal[eve::almost = ui_t(3)](v_t(4 * md), T(0)),
              eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_less_equal[eve::almost = ui_t(3)](v_t(1), v_t(1)), eve::true_(eve::as<v_t>()));
  }
};
