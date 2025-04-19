//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "unit/module/core/scan_test.hpp"

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

struct ManualCountTrue
{
  template<typename T, typename C>
  std::ptrdiff_t operator()(T v, C mask) const
  {
    if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
    {
      return std::ptrdiff_t{v && mask};
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
};

TTS_CASE("Check eve::count_true booleans")
{
  test_case<ManualCountTrue>(eve::count_true, true);
  test_case<ManualCountTrue>(eve::count_true, false);
};

TTS_CASE_TPL("Check eve::count_true behavior on scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  test_case<ManualCountTrue>(eve::count_true, eve::logical<T>{true});
  test_case<ManualCountTrue>(eve::count_true, eve::logical<T>{false});
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

    test_case<ManualCountTrue>(eve::count_true, rhs1);
    test_case<ManualCountTrue>(eve::count_true, rhs2);
    test_case<ManualCountTrue>(eve::count_true, rhs3);
    test_case<ManualCountTrue>(eve::count_true, rhs4);
  }
};
