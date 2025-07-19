//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "unit/module/core/reduction_test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::last_true return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  const T val{};

  TTS_EXPR_IS((eve::last_true(eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::last_true[eve::ignore_none](eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::last_true[val > 0](eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::last_true[true](eve::logical<T>())), std::optional<std::ptrdiff_t>);
};

TTS_CASE_TPL("Check eve::last_true return type (scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::last_true(eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::last_true[eve::ignore_none](eve::logical<T>())), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::last_true[true](eve::logical<T>())), std::optional<std::ptrdiff_t>);
};

TTS_CASE("Check eve::last_true return type (edge cases)")
{
  TTS_EXPR_IS((eve::last_true(bool{})), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::last_true[eve::ignore_none](bool{})), std::optional<std::ptrdiff_t>);
  TTS_EXPR_IS((eve::last_true[true](bool{})), std::optional<std::ptrdiff_t>);
};


struct ManualLastTrue
{
  template<typename T, typename C>
  std::optional<std::ptrdiff_t> operator()(T v, C mask) const
  {
    if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
    {
      return (v && mask) ? std::optional{0} : std::nullopt;
    }
    else
    {
      for (int i = v.size() - 1; i >= 0; --i)
          if (v.get(i) && mask_at(mask, i))
            return i;

      return std::nullopt;
    }
  }
};

TTS_CASE("Check eve::last_true on booleans")
{
  logical_test_case<ManualLastTrue>(eve::last_true, true);
  logical_test_case<ManualLastTrue>(eve::last_true, false);
};

TTS_CASE_TPL("Check eve::last_true behavior on scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_test_case<ManualLastTrue>(eve::last_true, eve::logical<T>{true});
  logical_test_case<ManualLastTrue>(eve::last_true, eve::logical<T>{false});
};

TTS_CASE_TPL("Check eve::last_true behavior on wides and top_bits", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  logical_simd_test_cases<ManualLastTrue>(eve::last_true, eve::as<T>{});
};
