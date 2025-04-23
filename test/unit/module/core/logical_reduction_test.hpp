//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include <eve/module/core.hpp>

template<typename Impl, typename T, typename C>
auto invoke_truth_fn(T v, C mask)
{
  if constexpr (std::same_as<C, eve::ignore_none_> && (eve::scalar_value<T> || std::same_as<T, bool>))
  {
    return Impl{}(v, true);
  }
  else if constexpr (eve::conditional_expr<C>)
  {
    return Impl{}(v, eve::detail::expand_mask(mask, eve::as(v)));
  }
  else
  {
    return Impl{}(v, mask);
  }
}

template<typename T>
bool mask_at(T mask, int idx)
{
  if constexpr (std::same_as<T, bool>) return mask;
  else                                 return mask.get(idx);
}

template<typename TruthFn, typename Callable, typename T>
void test_case_nocx(Callable callable, T v)
{
  const auto manual_res = invoke_truth_fn<TruthFn>(v, true);

  TTS_EQUAL(callable(v), manual_res);

  if constexpr (eve::simd_value<T>)
  {
    TTS_EQUAL(callable(eve::top_bits{v}), manual_res);
  }
}

template<typename TruthFn, typename Callable, typename T, typename C>
void test_case_cx(Callable callable, T v, C cx)
{
  const auto manual_res = invoke_truth_fn<TruthFn>(v, cx);

  TTS_EQUAL(callable[cx](v), manual_res);

  if constexpr (eve::simd_value<T>)
  {
    TTS_EQUAL(callable[cx](eve::top_bits{v}), manual_res);
  }
}

template<typename TruthFn, typename Callable, typename T>
void test_case(Callable callable, T v)
{
  test_case_nocx<TruthFn>(callable, v);
  test_case_cx<TruthFn>(callable, v, true);
  test_case_cx<TruthFn>(callable, v, false);
  test_case_cx<TruthFn>(callable, v, eve::ignore_none);

  if constexpr (eve::simd_value<T>)
  {
    constexpr auto cardinal = eve::cardinal_v<T>;

    T m = [](auto i, auto) { return i % 2 == 0; };
    test_case_cx<TruthFn>(callable, v, m);

    test_case_cx<TruthFn>(callable, v, eve::ignore_all);
    test_case_cx<TruthFn>(callable, v, eve::keep_first(0));

    if constexpr (cardinal >= 2)
    {
      test_case_cx<TruthFn>(callable, v, eve::ignore_extrema(1, 1));
      test_case_cx<TruthFn>(callable, v, eve::ignore_extrema(cardinal / 2, cardinal / 2));
      test_case_cx<TruthFn>(callable, v, eve::ignore_extrema(cardinal / 4, cardinal / 4));
    }
  }
}
