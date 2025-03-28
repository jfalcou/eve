//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::first_true return type", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::first_true(eve::logical<T>())), std::optional<std::ptrdiff_t>);
};

template<typename T>
bool mask_at(T mask, int idx)
{
  if constexpr (std::same_as<T, bool>) return mask;
  else                                 return mask.get(idx);
}

template<typename T, typename U>
std::optional<std::ptrdiff_t> manual_first_true(T v, U mask)
{
  if constexpr (eve::conditional_expr<U>)
  {
    return manual_first_true(v, expand_mask(mask, eve::as(v)));
  }
  else if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
  {
    return (v && mask) ? std::make_optional(0) : std::nullopt;
  }
  else
  {
    for (int i = 0; i < v.size(); ++i)
        if (v.get(i) && mask_at(mask, i))
          return std::make_optional(i);

    return std::nullopt;
  }
}

template<typename T>
void test_first_true(T v)
{
  TTS_EQUAL(eve::first_true(v), manual_first_true(v, true));
  TTS_EQUAL(eve::first_true[true](v), manual_first_true(v, true));
  TTS_EQUAL(eve::first_true[false](v), std::nullopt);
  TTS_EQUAL(eve::first_true[eve::ignore_none](v), manual_first_true(v, true));

  if constexpr (eve::simd_value<T>)
  {
    T m = [](auto i, auto) { return i % 2 == 0; };
    TTS_EQUAL(eve::first_true[m](v), manual_first_true(v, m));

    TTS_EQUAL(eve::first_true[eve::ignore_all](v), std::nullopt);
    TTS_EQUAL(eve::first_true[eve::keep_first(1)](v), manual_first_true(v, eve::keep_first(1)));
    TTS_EQUAL(eve::first_true[eve::ignore_first(1)](v), manual_first_true(v, eve::ignore_first(1)));
    TTS_EQUAL(eve::first_true[eve::keep_last(1)](v), manual_first_true(v, eve::keep_last(1)));
    TTS_EQUAL(eve::first_true[eve::ignore_last(1)](v), manual_first_true(v, eve::ignore_last(1)));
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
    eve::logical<T> rhs1 = {}, rhs2 = {}, rhs3 = {}, rhs4 = {};

    for( std::ptrdiff_t i = 0; i < cardinal; ++i )
    {
      rhs1.set(i, i >= j ? true : false);
      rhs2.set(i, i <= j ? false : true);
      rhs3.set(i, i == j ? true : false);
      rhs4.set(i, i == j ? false : true);
    }

    test_first_true(rhs1);
    test_first_true(rhs2);
    test_first_true(rhs3);
    test_first_true(rhs4);

    test_first_true(eve::top_bits{rhs1});
    test_first_true(eve::top_bits{rhs2});
    test_first_true(eve::top_bits{rhs3});
    test_first_true(eve::top_bits{rhs4});
  }
};
