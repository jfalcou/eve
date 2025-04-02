//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

TTS_CASE_TPL("Check eve::all return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  const T val{};

  TTS_EXPR_IS((eve::all(eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::all[eve::ignore_none](eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::all[val > 0](eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::all[true](eve::logical<T>())), bool);
};

TTS_CASE_TPL("Check eve::all return type (scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::all(eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::all[eve::ignore_none](eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::all[true](eve::logical<T>())), bool);
};

TTS_CASE("Check eve::all return type (booleans)")
{
  TTS_EXPR_IS((eve::all(bool{})), bool);
  TTS_EXPR_IS((eve::all[eve::ignore_none](bool{})), bool);
  TTS_EXPR_IS((eve::all[true](bool{})), bool);
};

template<typename T>
bool mask_at(T mask, int idx)
{
  if constexpr (std::same_as<T, bool>) return mask;
  else                                 return mask.get(idx);
}

template<typename T, typename U>
std::optional<std::ptrdiff_t> manual_all(T v, U mask)
{
  if constexpr (eve::conditional_expr<U>)
  {
    return manual_all(v, expand_mask(mask, eve::as(v)));
  }
  else if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
  {
    return (v && mask);
  }
  else
  {
    for (int i = 0; i < v.size(); ++i)
        if (mask_at(mask, i) && !v.get(i))
          return false;

    return true;
  }
}

template<typename T>
void test_all(T v)
{
  TTS_EQUAL(eve::all(v), manual_all(v, true));
  TTS_EQUAL(eve::all[true](v), manual_all(v, true));
  TTS_EQUAL(eve::all[false](v), true);
  TTS_EQUAL(eve::all[eve::ignore_none](v), manual_all(v, true));

  if constexpr (eve::simd_value<T>)
  {
    T m = [](auto i, auto) { return i % 2 == 0; };
    TTS_EQUAL(eve::all[m](v), manual_all(v, m));

    TTS_EQUAL(eve::all[eve::ignore_all](v), true);
    TTS_EQUAL(eve::all[eve::keep_first(1)](v), manual_all(v, eve::keep_first(1)));
    TTS_EQUAL(eve::all[eve::ignore_first(1)](v), manual_all(v, eve::ignore_first(1)));
    TTS_EQUAL(eve::all[eve::keep_last(1)](v), manual_all(v, eve::keep_last(1)));
    TTS_EQUAL(eve::all[eve::ignore_last(1)](v), manual_all(v, eve::ignore_last(1)));
  }
}

TTS_CASE("Check eve::all on booleans")
{
  test_all(true);
  test_all(false);
};

TTS_CASE_TPL("Check eve::all behavior on scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  test_all(eve::logical<T>{true});
  test_all(eve::logical<T>{false});
};

TTS_CASE_TPL("Check eve::all behavior on wides and top_bits", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  test_all(eve::logical<T>{true});
  test_all(eve::logical<T>{false});

  constexpr auto cardinal = eve::cardinal_v<T>;

  for (std::ptrdiff_t j = 0; j < cardinal; ++j)
  {
    eve::logical<T> rhs1 = {}, rhs2 = {};

    for (std::ptrdiff_t i = 0; i < cardinal; ++i)
    {
      rhs1.set(i, i == j ? true : false);
      rhs2.set(i, i == j ? false : true);
    }

    test_all(rhs1);
    test_all(rhs2);

    test_all(eve::top_bits{rhs1});
    test_all(eve::top_bits{rhs2});
  }
};
