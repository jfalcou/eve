//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::first_true return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  const T val{};

  TTS_EXPR_IS((eve::first_true(eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::first_true[eve::ignore_none](eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::first_true[val > 0](eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::first_true[true](eve::logical<T>())), std::optional<std::ptrdiff_t>);
};

TTS_CASE_TPL("Check eve::first_true return type (scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::first_true(eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::first_true[eve::ignore_none](eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::first_true[true](eve::logical<T>())), std::optional<std::ptrdiff_t>);
};

TTS_CASE("Check eve::first_true return type (edge cases)")
{
  TTS_EXPR_IS((eve::first_true(bool{})), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::first_true[eve::ignore_none](bool{})), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::first_true[true](bool{})), std::optional<std::ptrdiff_t>);
};

template<typename T>
bool mask_at(T mask, int idx)
{
  if constexpr (std::same_as<T, bool>) return mask;
  else                                 return mask.get(idx);
}

template<typename T, typename C>
std::optional<std::ptrdiff_t> manual_first_true(T v, C mask)
{
  if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
  {
    if constexpr (std::same_as<C, eve::ignore_none_>) return v ? std::make_optional(0): std::nullopt;
    else                                              return (v && mask) ? std::make_optional(0) : std::nullopt;
  }
  else if constexpr (eve::conditional_expr<C>)
  {
    return manual_first_true(v, expand_mask(mask, eve::as(v)));
  }
  else
  {
    for (int i = 0; i < v.size(); ++i)
        if (v.get(i) && mask_at(mask, i))
          return i;

    return std::nullopt;
  }
}

template<typename T, typename C>
void test_first_true(T v, C cx)
{
  const auto first = manual_first_true(v, cx);

  TTS_EQUAL(eve::first_true[cx](v), first);

  if constexpr (eve::simd_value<T>)
  {
    TTS_EQUAL(eve::first_true[cx](eve::top_bits{v}), first);
  }
}

template<typename T>
void test_first_true(T v)
{
  TTS_EQUAL(eve::first_true(v), manual_first_true(v, true));
  test_first_true(v, true);
  test_first_true(v, false);
  test_first_true(v, eve::ignore_none);

  if constexpr (eve::simd_value<T>)
  {
    constexpr auto cardinal = eve::cardinal_v<T>;
    TTS_EQUAL(eve::first_true(eve::top_bits{v}), manual_first_true(eve::top_bits{v}, true));

    T m = [](auto i, auto) { return i % 2 == 0; };
    test_first_true(v, m);

    test_first_true(v, eve::ignore_all);
    test_first_true(v, eve::keep_first(0));

    if constexpr (cardinal >= 2)
    {
      test_first_true(v, eve::ignore_extrema(1, 1));
      test_first_true(v, eve::ignore_extrema(cardinal / 2, cardinal / 2));
      test_first_true(v, eve::ignore_extrema(cardinal / 4, cardinal / 4));
    }
  }
}

TTS_CASE("Check eve::first_true on booleans")
{
  test_first_true(true);
  test_first_true(false);
};

TTS_CASE_TPL("Check eve::first_true behavior on scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  test_first_true(eve::logical<T>{true});
  test_first_true(eve::logical<T>{false});
};

TTS_CASE_TPL("Check eve::first_true behavior on wides and top_bits", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  constexpr auto cardinal = eve::cardinal_v<T>;

  for( std::ptrdiff_t j = 0; j < cardinal; ++j )
  {
    eve::logical<T> rhs1 = {}, rhs2 = {}, rhs3 = {};

    for( std::ptrdiff_t i = 0; i < cardinal; ++i )
    {
      rhs1.set(i, i >= j ? true : false);
      rhs2.set(i, i <= j ? false : true);
      rhs3.set(i, i == j ? true : false);
    }

    test_first_true(rhs1);
    test_first_true(rhs2);
    test_first_true(rhs3);
  }
};
