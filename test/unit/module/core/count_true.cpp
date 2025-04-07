//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::count_true return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  const T val{};

  TTS_EXPR_IS((eve::count_true(eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[eve::ignore_none](eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[val > 0](eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[true](eve::logical<T>())), std::ptrdiff_t);
};

TTS_CASE_TPL("Check eve::count_true return type (scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::count_true(eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[eve::ignore_none](eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[true](eve::logical<T>())), std::ptrdiff_t);
};

TTS_CASE("Check eve::count_true return type (edge cases)")
{
  TTS_EXPR_IS((eve::count_true(bool{})), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[eve::ignore_none](bool{})), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[true](bool{})), std::ptrdiff_t);
};

template<typename T>
bool mask_at(T mask, int idx)
{
  if constexpr (std::same_as<T, bool>) return mask;
  else                                 return mask.get(idx);
}

template<typename T, typename C>
std::ptrdiff_t manual_count_true(T v, C mask)
{
  if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
  {
    if constexpr (std::same_as<C, eve::ignore_none_>) return std::ptrdiff_t{v};
    else                                              return std::ptrdiff_t{v && mask};
  }
  else if constexpr (eve::conditional_expr<C>)
  {
    return manual_count_true(v, expand_mask(mask, eve::as(v)));
  }
  else
  {
    std::ptrdiff_t expected = 0;

    for (int i = 0; i < v.size(); ++i)
        if (v.get(i) && mask_at(mask, i))
          ++expected;

    return expected;
  }
}

template<typename T, typename C>
void test_count_true(T v, C cx)
{
  const auto count = manual_count_true(v, cx);

  TTS_EQUAL(eve::count_true[cx](v), count);

  if constexpr (eve::simd_value<T>)
  {
    TTS_EQUAL(eve::count_true[cx](eve::top_bits{v}), count);
  }
}

template<typename T>
void test_count_true(T v)
{
  TTS_EQUAL(eve::count_true(v), manual_count_true(v, true));
  test_count_true(v, true);
  test_count_true(v, false);
  test_count_true(v, eve::ignore_none);

  if constexpr (eve::simd_value<T>)
  {
    constexpr auto cardinal = eve::cardinal_v<T>;
    TTS_EQUAL(eve::count_true(eve::top_bits{v}), manual_count_true(eve::top_bits{v}, true));

    T m = [](auto i, auto) { return i % 2 == 0; };
    test_count_true(v, m);

    test_count_true(v, eve::ignore_all);
    test_count_true(v, eve::keep_first(0));

    if constexpr (cardinal >= 2)
    {
      test_count_true(v, eve::ignore_extrema(1, 1));
      test_count_true(v, eve::ignore_extrema(cardinal / 2, cardinal / 2));
      test_count_true(v, eve::ignore_extrema(cardinal / 4, cardinal / 4));
    }
  }
}

TTS_CASE("Check eve::count_true booleans")
{
  test_count_true(true);
  test_count_true(false);
};

TTS_CASE_TPL("Check eve::count_true behavior on scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  test_count_true(eve::logical<T>{true});
  test_count_true(eve::logical<T>{false});
};

TTS_CASE_TPL("Check eve::count_true behavior on wides and top_bits", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  constexpr auto cardinal = eve::cardinal_v<T>;

  TTS_EQUAL(eve::count_true(eve::true_(eve::as<T>())), cardinal);
  TTS_EQUAL(eve::count_true(eve::false_(eve::as<T>())), 0);

  for (std::ptrdiff_t j = 0; j < cardinal; ++j)
  {
    eve::logical<T> rhs1 = {}, rhs2 = {}, rhs3 = {}, rhs4 = {};

    for (std::ptrdiff_t i = 0; i < cardinal; ++i)
    {
      rhs1.set(i, i >= j ? true : false);
      rhs2.set(i, i <= j ? false : true);
      rhs3.set(i, i == j ? true : false);
      rhs4.set(i, i == j ? false : true);
    }

    test_count_true(rhs1);
    test_count_true(rhs2);
    test_count_true(rhs3);
    test_count_true(rhs4);
  }
};
