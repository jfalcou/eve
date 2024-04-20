//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of floor", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::floor(T()), T);
  TTS_EXPR_IS(eve::floor(v_t()), v_t);
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::floor(T(), eve::as<signed>()), (eve::as_integer_t<T, signed>));
    TTS_EXPR_IS(eve::floor(v_t(), eve::as<signed>()), (eve::as_integer_t<v_t, signed>));
    TTS_EXPR_IS(eve::floor(T(), eve::as<unsigned>()), (eve::as_integer_t<T, unsigned>));
    TTS_EXPR_IS(eve::floor(v_t(), eve::as<unsigned>()), (eve::as_integer_t<v_t, unsigned>));
    TTS_EXPR_IS(eve::floor[eve::almost2](T()), T);
    TTS_EXPR_IS(eve::floor[eve::almost2](v_t()), v_t);
  }
};

//==================================================================================================
// almost2 tests
//==================================================================================================
TTS_CASE_TPL("Check  with particular values", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::floor(static_cast<T>(-1.3)), T(-2));
  TTS_EQUAL(eve::floor(static_cast<T>(-1.5)), T(-2));
  TTS_EQUAL(eve::floor(static_cast<T>(-1.6)), T(-2));
  TTS_EQUAL(eve::floor(static_cast<T>(1.3)), T(1));
  TTS_EQUAL(eve::floor(static_cast<T>(1.5)), T(1));
  TTS_EQUAL(eve::floor(static_cast<T>(1.6)), T(1));

  TTS_EQUAL(eve::floor[eve::almost2](static_cast<T>(-1.3)), T(-2));
  TTS_EQUAL(eve::floor[eve::almost2](static_cast<T>(-1.5)), T(-2));
  TTS_EQUAL(eve::floor[eve::almost2](static_cast<T>(-1.6)), T(-2));
  TTS_EQUAL(eve::floor[eve::almost2](static_cast<T>(1.3)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2](static_cast<T>(1.5)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2](static_cast<T>(1.6)), T(1));

  auto epsi = eve::eps(eve::as<T>());
  TTS_EQUAL(eve::floor[eve::almost2](T(0)), T(0));
  TTS_EQUAL(eve::floor[eve::almost2](-epsi), T(0));
  TTS_EQUAL(eve::floor[eve::almost2]((-2 * epsi)), T(0));
  TTS_EQUAL(eve::floor[eve::almost2]((-3 * epsi)), T(0));
  TTS_EQUAL(eve::floor[eve::almost2]((-4 * epsi)), T(-1));

  TTS_EQUAL(eve::floor[eve::almost2](T(1)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2]((T(1) - epsi)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2]((T(1) - 2 * epsi)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2]((T(1) - 3 * epsi)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2]((T(1) - 4 * epsi)), T(0));

  TTS_EQUAL(eve::floor[eve::almost2](T(45)), T(45));
  TTS_EQUAL(eve::floor[eve::almost2](45 * (T(1) - 2 * epsi)), T(45));
  TTS_EQUAL(eve::floor[eve::almost2](45 * (T(1) - 3 * epsi)), T(45));
  TTS_EQUAL(eve::floor[eve::almost2](45 * (T(1) - 4 * epsi)), T(44));

  TTS_EQUAL(eve::floor[eve::almost2](T(1)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2](eve::prev(T(1), 1)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2](eve::prev(T(1), 2)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2](eve::prev(T(1), 3)), T(1));
  TTS_EQUAL(eve::floor[eve::almost2](eve::prev(T(1), 10)), T(0));

  TTS_EQUAL(eve::floor[eve::almost2 = 3](T(45)), T(45));
  TTS_EQUAL(eve::floor[eve::almost2 = 3](eve::prev(T(45), 1)), T(45));
  TTS_EQUAL(eve::floor[eve::almost2 = 3](eve::prev(T(45), 2)), T(45));
  TTS_EQUAL(eve::floor[eve::almost2 = 3](eve::prev(T(45), 3)), T(45));
  TTS_EQUAL(eve::floor[eve::almost2 = 3](eve::prev(T(45), 4)), T(44));

  TTS_EQUAL(eve::floor[eve::almost2 = 3](T(-45)), T(-45));
  TTS_EQUAL(eve::floor[eve::almost2 = 3](eve::prev(T(-45), 1)), T(-45));
  TTS_EQUAL(eve::floor[eve::almost2 = 3](eve::prev(T(-45), 2)), T(-45));
  TTS_EQUAL(eve::floor[eve::almost2 = 3](eve::prev(T(-45), 3)), T(-45));
  TTS_EQUAL(eve::floor[eve::almost2 = 3](eve::prev(T(-45), 4)), T(-46));
};

//==================================================================================================
// floor(simd)  tests
//==================================================================================================
auto mini = tts::constant([]<typename T>(eve::as<T>) { return eve::signed_value<T> ? -50 : 0; });

TTS_CASE_WITH("Check behavior of floor(wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(mini, +50)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using wi_t  = eve::as_integer_t<T>;
  using uwi_t = eve::as_integer_t<T, unsigned>;
  using v_t   = eve::element_type_t<T>;
  using i_t   = eve::as_integer_t<v_t>;
  using ui_t  = eve::as_integer_t<v_t, unsigned>;
  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::floor(a0), map([&](auto e) -> v_t { return v_t(std::floor(e)); }, a0));

    TTS_EQUAL(eve::floor(a0, eve::as<int>()),
              wi_t([&](auto i, auto) { return i_t(std::floor(a0.get(i))); }));
    TTS_EQUAL(eve::floor(eve::abs(a0), eve::as<uint>()),
              uwi_t([&](auto i, auto) { return ui_t(std::floor(std::abs(a0.get(i)))); }));
  }
  else { TTS_EQUAL(eve::floor(a0), a0); }
};


//==================================================================================================
// Tests for masked floor
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::floor)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::floor[mask](a0),
            eve::if_else(mask, eve::floor(a0), a0));
};
