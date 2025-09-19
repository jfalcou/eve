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
TTS_CASE_TPL("Check return types of eve::is_equal(simd)", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_equal(T(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_equal(v_t(), v_t()), logical<v_t>);
  TTS_EXPR_IS(eve::is_equal(T(), v_t()), logical<T>);
  TTS_EXPR_IS(eve::is_equal(v_t(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_equal(logical<T>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(eve::is_equal(logical<v_t>(), logical<v_t>()), logical<v_t>);

  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::is_equal[eve::numeric](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::numeric](v_t(), v_t()), logical<v_t>);
    TTS_EXPR_IS(eve::is_equal[eve::numeric](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::numeric](v_t(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::almost](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::almost](v_t(), v_t()), logical<v_t>);
    TTS_EXPR_IS(eve::is_equal[eve::almost](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_equal[eve::almost](v_t(), T()), logical<T>);
  }
};

template <eve::simd_value W, typename T>
void run_check(W a, T b)
{
  auto rs0 = eve::is_equal(a, b);
  auto rs1 = eve::is_equal(b, a);
  auto rm = tts::map([](auto x, auto y) -> eve::as_logical_t<eve::element_type_t<W>> { return x == y; }, a, b);

  for (std::size_t i = 0; i < rm.size(); ++i)
  {
    TTS_EQUAL(rs0.get(i), rm.get(i));
    TTS_EQUAL(rs1.get(i), rm.get(i));
  }
}

template <eve::simd_value W, typename T, typename M>
void run_check_masked(W a, T b, M m)
{
  auto rs0 = eve::is_equal[m](a, b);
  auto rs1 = eve::is_equal[m](b, a);
  auto rm = tts::map([](auto x, auto y) -> eve::as_logical_t<eve::element_type_t<W>> { return x == y; }, a, b);

  auto em = [&]() {
    if constexpr (eve::scalar_value<M> || std::same_as<M, bool>) return W { m };
    else if constexpr (eve::conditional_expr<M>) return eve::detail::expand_mask(m, eve::as(a));
    else                                         return m;
  }();

  for (std::size_t i = 0; i < rm.size(); ++i)
  {
    if (em.get(i))
    {
      TTS_EQUAL(rs0.get(i), rm.get(i));
      TTS_EQUAL(rs1.get(i), rm.get(i));
    }
    else
    {
      TTS_EQUAL(rs0.get(i), false);
      TTS_EQUAL(rs1.get(i), false);
    }
  }
}

template <eve::simd_value W, eve::logical_simd_value L, typename M>
void equal_masked_test_cases(W a0, W a1, L l0, L l1, M m)
{
  using v_t = eve::element_type_t<W>;
  using dv_t = eve::downgrade_t<v_t>;

  run_check_masked(a0, a1, m);
  run_check_masked(a0, a0, m);
  run_check_masked(a0, v_t{ 1 }, m);
  run_check_masked(a1, v_t{ 4 }, m);
  run_check_masked(a0, dv_t{ 1 }, m);
  run_check_masked(a1, dv_t{ 4 }, m);
  run_check_masked(l0, l1, m);
}

//==================================================================================================
//== Tests for eve::is_equal
//==================================================================================================
TTS_CASE_WITH(
    "Check behavior of eve::is_equal(simd)",
    eve::test::simd::all_types_wf16,
    tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3), tts::logicals(1, 2)))
<typename T, typename M>(T const& a0, T const& a1, M const& l0, M const& l1)
{
  using v_t = eve::element_type_t<T>;
  using dv_t = eve::downgrade_t<v_t>;
  using LT  = eve::logical<T>;

  run_check(a0, a1);
  run_check(a0, a0);
  run_check(a0, v_t{ 1 });
  run_check(a1, v_t{ 4 });
  run_check(a0, dv_t{ 1 });
  run_check(a1, dv_t{ 4 });
  run_check(l0, l1);

  LT m = tts::poison(LT{ [](auto i, auto) { return ((i + 1) % 4) == 0; } });

  equal_masked_test_cases(a0, a1, l0, l1, m);
  equal_masked_test_cases(a0, a1, l0, l1, true);
  equal_masked_test_cases(a0, a1, l0, l1, false);
  equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_none);
  equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_all);
  equal_masked_test_cases(a0, a1, l0, l1, eve::keep_first(0));

  constexpr auto cardinal = eve::cardinal_v<T>;
  if constexpr (cardinal >= 2)
  {
    equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_extrema(1, 1));
    equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_extrema(cardinal / 2, cardinal / 2));
    equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_extrema(cardinal / 4, cardinal / 4));
  }
};

//==================================================================================================
//== Tests for eve::is_equal corner cases for floating
//==================================================================================================
TTS_CASE_TPL("Check behavior of eve::is_equal[almost/numeric](simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> const& tgt)
{
  using eve::as;
  using v_t  = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<v_t, unsigned>;

  auto cases = tts::limits(tgt);
  TTS_EQUAL(eve::is_equal(cases.nan, cases.nan), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_equal[eve::numeric](cases.nan, cases.nan), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost](T(1 + eve::eps(as<T>())), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(1 + eve::eps(as<T>())), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(1 + 2 * eve::eps(as<T>())), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(1 + eve::eps(as<T>())), v_t(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost =  eve::eps(as<v_t>())](T(3), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](T(1), T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](T(1), v_t(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](T(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](T(3), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](eve::next(T(0)), T(0)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](eve::next(T(0), 3), T(0)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](eve::next(T(0), 4), T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](v_t(1), v_t(1)), eve::true_(eve::as<v_t>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](v_t(3), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_equal[eve::almost = ui_t(3)](v_t(3), v_t(1)), eve::false_(eve::as<v_t>()));
};
