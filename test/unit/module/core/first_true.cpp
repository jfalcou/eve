//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "unit/module/core/logical_reduction_test.hpp"

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


struct ManualFirstTrue
{
  template<typename T, typename C>
  std::optional<std::ptrdiff_t> operator()(T v, C mask) const
  {
    if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
    {
      return (v && mask) ? std::make_optional(0) : std::nullopt;
    }
    else
    {
      for (int i = 0; i < v.size(); ++i)
          if (v.get(i) && mask_at(mask, i))
            return i;

      return std::nullopt;
    }
  }
};

TTS_CASE("Check eve::first_true on booleans")
{
  test_case<ManualFirstTrue>(eve::first_true, true);
  test_case<ManualFirstTrue>(eve::first_true, false);
};

TTS_CASE_TPL("Check eve::first_true behavior on scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  test_case<ManualFirstTrue>(eve::first_true, eve::logical<T>{true});
  test_case<ManualFirstTrue>(eve::first_true, eve::logical<T>{false});
};

TTS_CASE_TPL("Check eve::first_true behavior on wides and top_bits", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  simd_test_cases<ManualFirstTrue>(eve::first_true, eve::as<T>{});
};
