//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "unit/module/core/reduction_test.hpp"

TTS_CASE_TPL("Check eve::detail::sum return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  arithmetic_simd_type_test(eve::detail::sum, eve::as<T>{});
};

TTS_CASE_TPL("Check eve::detail::sum return type (wide)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  arithmetic_scalar_type_test(eve::detail::sum, eve::as<T>{});
};

struct ManualSum
{
  template<typename T, typename C>
  eve::element_type_t<T> operator()(T v, C mask) const
  {
    if constexpr (eve::scalar_value<T>)
    {
      return mask ? v : eve::zero(eve::as(v));
    }
    else
    {
      auto sum = eve::zero(eve::as<eve::element_type_t<T>>{});

      for (int i = 0; i < v.size(); ++i)
        if (mask_at(mask, i))
          sum += v.get(i);

      return sum;
    }
  }
};

TTS_CASE_WITH("Check behavior of eve::detail::sum on scalars",
              eve::test::scalar::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T v)
{
  arithmetic_test_case<ManualSum>(eve::detail::sum, v);
};

TTS_CASE_WITH("Check behavior of eve::detail::sum on wides",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T v)
{
  arithmetic_test_case<ManualSum>(eve::detail::sum, v, 0.5);
};
