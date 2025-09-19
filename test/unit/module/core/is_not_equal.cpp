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
TTS_CASE_TPL("Check return types of eve::is_not_equal(simd)", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_not_equal(T(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_not_equal(v_t(), v_t()), logical<v_t>);
  TTS_EXPR_IS(eve::is_not_equal(T(), v_t()), logical<T>);
  TTS_EXPR_IS(eve::is_not_equal(v_t(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_not_equal(logical<T>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(eve::is_not_equal(logical<v_t>(), logical<v_t>()), logical<v_t>);

  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::is_not_equal[eve::numeric](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_not_equal[eve::numeric](v_t(), v_t()), logical<v_t>);
    TTS_EXPR_IS(eve::is_not_equal[eve::numeric](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_not_equal[eve::numeric](v_t(), T()), logical<T>);

    TTS_EXPR_IS(eve::is_not_equal[eve::definitely](T(), T()), logical<T>);
    TTS_EXPR_IS(eve::is_not_equal[eve::definitely](v_t(), v_t()), logical<v_t>);
    TTS_EXPR_IS(eve::is_not_equal[eve::definitely](T(), v_t()), logical<T>);
    TTS_EXPR_IS(eve::is_not_equal[eve::definitely](v_t(), T()), logical<T>);
  }
};

template <eve::simd_value W, typename T>
void run_check(W a, T b)
{
  auto rs0 = eve::is_not_equal(a, b);
  auto rs1 = eve::is_not_equal(b, a);
  auto rm = tts::map([](auto x, auto y) -> eve::as_logical_t<eve::element_type_t<W>> { return x != y; }, a, b);

  TTS_EQUAL(rs0, rm);
  TTS_EQUAL(rs1, rm);
}

template <eve::simd_value W, typename T, typename M>
void run_check_masked(W a, T b, M m)
{
  auto rs0 = eve::is_not_equal[m](a, b);
  auto rs1 = eve::is_not_equal[m](b, a);
  auto rm = tts::map([](auto x, auto y) -> eve::as_logical_t<eve::element_type_t<W>> { return x != y; }, a, b);

  auto em = [&]() {
    if constexpr (eve::scalar_value<M> || std::same_as<M, bool>) return W { m };
    else if constexpr (eve::conditional_expr<M>)                 return eve::detail::expand_mask(m, eve::as(a));
    else                                                         return m;
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
void not_equal_masked_test_cases(W a0, W a1, L l0, L l1, M m)
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
//== Tests for eve::is_not_equal
//==================================================================================================
TTS_CASE_WITH(
    "Check behavior of eve::is_not_equal(simd)",
    eve::test::simd::all_types_wf16,
    tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3), tts::logicals(1, 2)))
<typename T, typename M>(T const& a0, T const& a1, [[maybe_unused]]  M const& l0, [[maybe_unused]] M const& l1)
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

  not_equal_masked_test_cases(a0, a1, l0, l1, m);
  not_equal_masked_test_cases(a0, a1, l0, l1, true);
  not_equal_masked_test_cases(a0, a1, l0, l1, false);
  not_equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_none);
  not_equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_all);
  not_equal_masked_test_cases(a0, a1, l0, l1, eve::keep_first(0));

  constexpr auto cardinal = eve::cardinal_v<T>;
  if constexpr (cardinal >= 2)
  {
    not_equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_extrema(1, 1));
    not_equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_extrema(cardinal / 2, cardinal / 2));
    not_equal_masked_test_cases(a0, a1, l0, l1, eve::ignore_extrema(cardinal / 4, cardinal / 4));
  }
};

// //==================================================================================================
// //== Tests for eve::is_not_equal corner cases for floating
// //==================================================================================================
TTS_CASE_TPL("Check behavior of eve::is_not_equal(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using v_t  = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<v_t, unsigned>;

  TTS_EQUAL(eve::is_not_equal[eve::definitely](T(1), T(1)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely](T(1), v_t(1)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely](T(3), T(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely](T(3), v_t(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  eve::eps(as<v_t>())](T(1 + eve::eps(as<T>())), T(1)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  eve::eps(as<v_t>())](T(1 + 2 * eve::eps(as<T>())), T(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  eve::eps(as<v_t>())](T(1 + eve::eps(as<T>())), v_t(1)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  eve::eps(as<v_t>())](T(3), T(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  eve::eps(as<v_t>())](T(3), v_t(1)), eve::true_(as<T>()));

  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](T(1), T(1)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](T(1), v_t(1)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](T(3), T(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](T(3), v_t(1)), eve::true_(as<T>()));
  auto md = eve::next(v_t(0));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](v_t(md), T(0)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](v_t(2 * md), T(0)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](v_t(3 * md), T(0)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](v_t(4 * md), T(0)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](v_t(1), v_t(1)), eve::false_(as<v_t>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](v_t(3), T(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_not_equal[eve::definitely =  ui_t(3)](v_t(3), v_t(1)), eve::true_(as<v_t>()));
};
