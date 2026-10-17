//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "unit/module/core/reduction_test.hpp"

TTS_CASE_TPL("Check eve::_::sum return type (scalar)", eve::test::scalar::all_types_wf16)
<typename T>(tts::type<T>)
{
  arithmetic_reduction_scalar_type_test(eve::_::sum, eve::as<T>{});
};

TTS_CASE_TPL("Check eve::_::sum return type (wide)", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  arithmetic_reduction_simd_type_test(eve::_::sum, eve::as<T>{});
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
      // A float16 sum is exact in float, so the reference carries no rounding of its own.
      using e_t = eve::element_type_t<T>;
      using s_t = std::conditional_t<sizeof(e_t) == 2 && std::floating_point<e_t>, float, e_t>;
      auto sum = eve::zero(eve::as<s_t>{});

      for (int i = 0; i < v.size(); ++i)
        if (mask_at(mask, i))
          sum += static_cast<s_t>(v.get(i));

      return static_cast<e_t>(sum);
    }
  }
};

TTS_CASE_WITH("Check behavior of eve::_::sum on scalars",
              eve::test::scalar::all_types_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T v)
{
  arithmetic_reduction_test_case<ManualSum>(eve::_::sum, v);
};

TTS_CASE_WITH("Check behavior of eve::_::sum on wides (integers)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T v)
{
  arithmetic_reduction_test_case<ManualSum>(eve::_::sum, v);
};

TTS_CASE_WITH("Check behavior of eve::_::sum on wides (ieee754 reals)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(1, 9)))
<typename T>(T v)
{
  // A float16 sum done in float16 rounds at every level of its tree.
  constexpr double ulp = sizeof(eve::element_type_t<T>) == 2 ? 1.0 + std::bit_width(std::size_t{T::size()}) / 2.0 : 1.0;
  arithmetic_reduction_test_case<ManualSum>(eve::_::sum, v, ulp);
};

TTS_CASE_TPL("Check behavior of eve::_::sum on wides (conditioned ieee754 reals)", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  T v = [](auto i, auto c) { return i < c / 2 ? 10 * (i + 1) : -(10 * (i + 1) + 1); };
  constexpr auto expected_ulp = std::is_same_v<eve::element_type_t<T>, eve::float16_t> ? 0.5 : 0.0;
  arithmetic_reduction_test_case<ManualSum>(eve::_::sum, v, expected_ulp);
};
