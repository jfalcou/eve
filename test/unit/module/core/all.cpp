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

struct ManualTestAll {
  template<typename T, typename C>
  bool operator()(T v, C mask)
  {
    if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
    {
      return v || !mask;
    }
    else
    {
      for (int i = 0; i < v.size(); ++i)
        if (mask_at(mask, i) && !v.get(i))
          return false;

      return true;
    }
  }
};

TTS_CASE("Check eve::all booleans")
{
  test_case<ManualTestAll>(eve::all, true);
  test_case<ManualTestAll>(eve::all, false);
};

TTS_CASE_TPL("Check eve::all behavior on scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  test_case<ManualTestAll>(eve::all, eve::logical<T>{true});
  test_case<ManualTestAll>(eve::all, eve::logical<T>{false});
};

TTS_CASE_TPL("Check eve::all behavior on wides and top_bits", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  simd_test_cases<ManualTestAll>(eve::all, eve::as<T>{});
};
