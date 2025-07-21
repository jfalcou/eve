//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "unit/module/core/reduction_test.hpp"

TTS_CASE_TPL("Check eve::maximum return type (scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  arithmetic_scalar_type_test(eve::maximum, eve::as<T>{});
};

TTS_CASE_TPL("Check eve::maximum return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  arithmetic_simd_type_test(eve::maximum, eve::as<T>{});
};

struct ManualMaximum
{
  template<typename T, typename C>
  eve::element_type_t<T> operator()(T v, C mask) const
  {
    if constexpr (eve::scalar_value<T>)
    {
      return mask ? v : eve::valmin(eve::as(v));
    }
    else
    {
      auto max = eve::valmin(eve::as<eve::element_type_t<T>>{});

      for (std::ptrdiff_t i = 0; i < v.size(); ++i)
        if (mask_at(mask, i))
          max = std::max(max, v.get(i));

      return max;
    }
  }
};

TTS_CASE_WITH("Check behavior of eve::maximum on scalars",
              eve::test::scalar::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T v)
{
  arithmetic_test_case<ManualMaximum>(eve::maximum, v);
};

TTS_CASE_WITH("Check behavior of eve::maximum on wides",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T v)
{
  arithmetic_test_case<ManualMaximum>(eve::maximum, v);
};
