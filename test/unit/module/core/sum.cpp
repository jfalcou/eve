//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "unit/module/core/reduction_test.hpp"

#include <bit>

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
      auto sum = eve::zero(eve::as<eve::element_type_t<T>>{});

      for (int i = 0; i < v.size(); ++i)
        if (mask_at(mask, i))
          sum += v.get(i);

      return sum;
    }
  }
};

// Same order as ManualSum, accumulated in double. For elements narrower than double this is the
// correctly rounded sum, so a test using it measures eve's own reduction and not a second
// approximate order.
struct DoubleAccSum
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
      double sum = 0;

      for (int i = 0; i < v.size(); ++i)
        if (mask_at(mask, i))
          sum += static_cast<double>(v.get(i));

      return static_cast<eve::element_type_t<T>>(sum);
    }
  }
};

TTS_CASE_WITH("Check behavior of eve::_::sum on scalars",
              eve::test::scalar::all_types_wf16,
              tts::randoms(eve::valmin, eve::valmax))
<typename T>(T v)
{
  arithmetic_reduction_test_case<ManualSum>(eve::_::sum, v);
};

TTS_CASE_WITH("Check behavior of eve::_::sum on wides (integers)",
              eve::test::simd::integers,
              tts::randoms(eve::valmin, eve::valmax))
<typename T>(T v)
{
  arithmetic_reduction_test_case<ManualSum>(eve::_::sum, v);
};

TTS_CASE_WITH("Check behavior of eve::_::sum on wides (ieee754 reals)",
              eve::test::simd::ieee_reals_wf16,
              tts::randoms(1, 9))
<typename T>(T v)
{
  // The reference is correctly rounded below double, so only eve's tree reduction is left to
  // cover, one half-ULP per level plus the final rounding. A double reference has no wider
  // accumulator and keeps the (n - 1) roundings of its own sequential order.
  constexpr auto   n      = static_cast<std::size_t>(T::size());
  constexpr auto   levels = std::bit_width(n) - 1;
  constexpr double expected_ulp =
      std::is_same_v<eve::element_type_t<T>, double> ? 0.5 * (n - 1 + levels) : 0.5 * levels + 0.5;

  arithmetic_reduction_test_case<DoubleAccSum>(eve::_::sum, v, expected_ulp);
};

TTS_CASE_TPL("Check behavior of eve::_::sum on wides (conditioned ieee754 reals)", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  T v = [](auto i, auto c) { return i < c / 2 ? 10 * (i + 1) : -(10 * (i + 1) + 1); };
  constexpr auto expected_ulp = std::is_same_v<eve::element_type_t<T>, eve::float16_t> ? 0.5 : 0.0;
  arithmetic_reduction_test_case<ManualSum>(eve::_::sum, v, expected_ulp);
};
