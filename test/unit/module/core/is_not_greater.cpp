//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_not_greater(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_not_greater(T(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_not_greater(v_t(), v_t()), logical<v_t>);
  TTS_EXPR_IS(eve::is_not_greater(T(), v_t()), logical<T>);
  TTS_EXPR_IS(eve::is_not_greater(v_t(), T()), logical<T>);

  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(T(), T()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(v_t(), T()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(T(), T(), unsigned()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(T(), v_t(), unsigned()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(v_t(), T(), unsigned()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(T(), T(), T()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(T(), v_t(), T()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(v_t(), T(), T()), logical<T>);
    using ui_t = eve::as_integer_t<T, unsigned>;
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(T(), T(), ui_t()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(T(), v_t(), ui_t()), logical<T>);
    TTS_EXPR_IS(eve::almost(eve::is_not_greater)(v_t(), T(), ui_t()), logical<T>);
  }
};

//==================================================================================================
//== Tests for eve::is_not_greater
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::is_not_greater(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, M const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_not_greater(a0, a1),
            map([](auto e, auto f) -> eve::logical<v_t> { return e <= f; }, a0, a1));
  TTS_EQUAL(eve::is_not_greater(a0, a0),
            map([](auto e, auto f) -> eve::logical<v_t> { return e <= f; }, a0, a0));
  TTS_EQUAL(eve::is_not_greater(a0, v_t(1)),
            map([](auto e) -> eve::logical<v_t> { return e <= v_t(1); }, a0));
  TTS_EQUAL(eve::is_not_greater[t](a0, a1),
            eve::if_else(t, eve::is_not_greater(a0, a1), eve::false_(eve::as(a0))));
};

//==================================================================================================
//== Tests for eve::is_not_greater corner cases for floating
//==================================================================================================
TTS_CASE_TPL("Check behavior of eve::is_not_greater(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::logical;
  using v_t  = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<T, unsigned>;

  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(1), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(1), v_t(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(3), v_t(1)), eve::false_(eve::as<T>()));

  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(1 + eve::eps(as<T>())), T(1), eve::eps(as<T>())),
            eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(1 + 2 * eve::eps(as<T>())), T(1), eve::eps(as<T>())),
            eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(1 + eve::eps(as<T>())), v_t(1), eve::eps(as<T>())),
            eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(3), T(1), eve::eps(as<T>())),
            eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(3), v_t(1), eve::eps(as<T>())),
            eve::false_(eve::as<T>()));

  using ui_t = eve::as_integer_t<T, unsigned>;

  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(1), T(1), ui_t(3)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(1), v_t(1), ui_t(3)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(3), T(1), ui_t(3)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_not_greater)(T(3), v_t(1), ui_t(3)), eve::false_(eve::as<T>()));

  if constexpr( eve::platform::supports_denormals )
  {
    auto md = eve::mindenormal(eve::as<v_t>());

    TTS_EQUAL(eve::almost(eve::is_not_greater)(v_t(md), T(0), ui_t(3)), eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::almost(eve::is_not_greater)(v_t(2 * md), T(0), ui_t(3)),
              eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::almost(eve::is_not_greater)(v_t(3 * md), T(0), ui_t(3)),
              eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::almost(eve::is_not_greater)(v_t(4 * md), T(0), ui_t(3)),
              eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::almost(eve::is_not_greater)(v_t(1), v_t(1), ui_t(3)), eve::true_(eve::as<T>()));
  }
};
