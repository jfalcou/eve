//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include "unit/module/core/reduction_test.hpp"

TTS_CASE_TPL("Check eve::none return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  const T val{};

  TTS_EXPR_IS((eve::none(eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::none[eve::ignore_none](eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::none[val > 0](eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::none[true](eve::logical<T>())), bool);
};

TTS_CASE_TPL("Check eve::none return type (scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::none(eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::none[eve::ignore_none](eve::logical<T>())), bool);
  TTS_EXPR_IS((eve::none[true](eve::logical<T>())), bool);
};

TTS_CASE("Check eve::none return type (booleans)")
{
  TTS_EXPR_IS((eve::none(bool{})), bool);
  TTS_EXPR_IS((eve::none[eve::ignore_none](bool{})), bool);
  TTS_EXPR_IS((eve::none[true](bool{})), bool);
};

struct ManualNone {
  template<typename T, typename C>
  bool operator()(T v, C mask)
  {
    if constexpr (eve::scalar_value<T> || std::same_as<T, bool>)
    {
      return !(mask && v);
    }
    else
    {
      for (int i = 0; i < v.size(); ++i)
        if (v.get(i) && mask_at(mask, i))
          return false;

      return true;
    }
  }
};

TTS_CASE("Check eve::none booleans")
{
  logical_reduction_test_case<ManualNone>(eve::none, true);
  logical_reduction_test_case<ManualNone>(eve::none, false);
};

TTS_CASE_TPL("Check eve::none behavior on scalars", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  logical_reduction_test_case<ManualNone>(eve::none, eve::logical<T>{true});
  logical_reduction_test_case<ManualNone>(eve::none, eve::logical<T>{false});
};

TTS_CASE_TPL("Check eve::none behavior on wides and top_bits", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  logical_reduction_simd_test_cases<ManualNone>(eve::none, eve::as<T>{});
};
