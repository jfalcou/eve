//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "unit/module/core/reduction_test.hpp"

TTS_CASE_TPL("Check eve::minimum return type (scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  arithmetic_reduction_scalar_type_test(eve::minimum, eve::as<T>{});
};

TTS_CASE_TPL("Check eve::minimum return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  arithmetic_reduction_simd_type_test(eve::minimum, eve::as<T>{});
};

struct ManualMinimum
{
  template<typename T, typename C>
  eve::element_type_t<T> operator()(T v, C mask) const
  {
    if constexpr (eve::scalar_value<T>)
    {
      return mask ? v : eve::majorant(eve::as(v));
    }
    else
    {
      auto min = eve::majorant(eve::as<eve::element_type_t<T>>{});

      for (int i = 0; i < v.size(); ++i)
        if (mask_at(mask, i))
          min = std::min(min, v.get(i));

      return min;
    }
  }
};

TTS_CASE_WITH("Check behavior of eve::minimum on scalars",
              eve::test::scalar::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T v)
{
  arithmetic_reduction_test_case<ManualMinimum>(eve::minimum, v);
};

TTS_CASE_WITH("Check behavior of eve::minimum on wides",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T v)
{
  arithmetic_reduction_test_case<ManualMinimum>(eve::minimum, v);
};
