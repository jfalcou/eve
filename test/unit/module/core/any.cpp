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

TTS_CASE_TPL("Check eve::any return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  const T val{};

  TTS_EXPR_IS((eve::any(eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::any[eve::ignore_none](eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::any[val > 0](eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::any[true](eve::logical<T>())), bool);
};

TTS_CASE_TPL("Check eve::any return type (scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::any(eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::any[eve::ignore_none](eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::any[true](eve::logical<T>())), bool);
};

TTS_CASE("Check eve::any return type (booleans)")
{
  TTS_EXPR_IS((eve::any(bool{})), bool);
  TTS_EXPR_IS((eve::any[eve::ignore_none](bool{})), bool);
  TTS_EXPR_IS((eve::any[true](bool{})), bool);
};

struct ManualTestAny {
  template<typename T, typename C>
  bool operator()(T v, C mask)
  {
    if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
    {
      return v && mask;
    }
    else
    {
      for (int i = 0; i < v.size(); ++i)
        if (v.get(i) && mask_at(mask, i))
          return true;

      return false;
    }
  }
};

TTS_CASE("Check eve::any booleans")
{
  logical_reduction_test_case<ManualTestAny>(eve::any, true);
  logical_reduction_test_case<ManualTestAny>(eve::any, false);
};

TTS_CASE_TPL("Check eve::any behavior on scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_reduction_test_case<ManualTestAny>(eve::any, eve::logical<T>{true});
  logical_reduction_test_case<ManualTestAny>(eve::any, eve::logical<T>{false});
};

TTS_CASE_TPL("Check eve::any behavior on wides and top_bits", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  logical_reduction_simd_test_cases<ManualTestAny>(eve::any, eve::as<T>{});
};
