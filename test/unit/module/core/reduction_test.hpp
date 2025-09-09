//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include <eve/module/core.hpp>

template<typename F, typename T, typename U>
auto compile_reject_test(F f, T v) -> decltype(f(v)) { }

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

template<typename TruthFn>
struct TestRunner
{
  template<typename Callable, typename T>
  static void call_nocx(Callable callable, T v);

  template<typename Callable, typename T, typename C>
  static void call_cx(Callable callable, T v, C cx);
};

template<typename TruthFn>
struct LogicalTestRunner : TestRunner<TruthFn>
{
  template<typename Callable, typename T>
  static void call_nocx(Callable callable, T v) {
    const auto manual_res = invoke_truth_fn<TruthFn>(v, true);

    if constexpr (eve::simd_value<T>) v = tts::poison(v);

    TTS_EQUAL(callable(v), manual_res);

    if constexpr (eve::simd_value<T>)
    {
      TTS_EQUAL(callable(eve::top_bits{v}), manual_res);
    }
  }

  template<typename Callable, typename T, typename C>
  static void call_cx(Callable callable, T v, C cx) {
    const auto manual_res = invoke_truth_fn<TruthFn>(v, cx);

    if constexpr (eve::simd_value<T>) v = tts::poison(v);

    TTS_EQUAL(callable[cx](v), manual_res);

    if constexpr (eve::simd_value<T>)
    {
      TTS_EQUAL(callable[cx](eve::top_bits{v}), manual_res);
    }
  }
};

template<typename TruthFn>
struct ArithmeticTestRunner : TestRunner<TruthFn>
{
  double expected_ulp;

  constexpr ArithmeticTestRunner(double ulp = 0.0) : expected_ulp(ulp) {}

  template<typename Callable, typename T>
  void call_nocx(Callable callable, T v) const {
    const auto manual_res = invoke_truth_fn<TruthFn>(v, true);
    const auto res = callable(v);

    TTS_ULP_EQUAL(res, manual_res, expected_ulp);

    if constexpr (eve::simd_value<T>)
    {
      auto res_splat = callable[eve::splat](v);
      TTS_ULP_EQUAL(res_splat.get(0), manual_res, expected_ulp);

      for (std::ptrdiff_t i = 0; i < T::size(); ++i)
      {
        TTS_EQUAL(res_splat.get(0), res_splat.get(i));
      }
    }
  }

  template<typename Callable, typename T, typename C>
  void call_cx(Callable callable, T v, C cx) const {
    const auto manual_res = invoke_truth_fn<TruthFn>(v, cx);
    const auto res = callable[cx](v);

    TTS_ULP_EQUAL(res, manual_res, expected_ulp);

    if constexpr (eve::simd_value<T>)
    {
      auto res_splat = callable[eve::splat][cx](v);
      TTS_ULP_EQUAL(res_splat.get(0), manual_res, expected_ulp);

      for (std::ptrdiff_t i = 0; i < T::size(); ++i)
      {
        TTS_EQUAL(res_splat.get(0), res_splat.get(i));
      }
    }
  }
};

template<typename TruthFn>
constexpr LogicalTestRunner<TruthFn> logical_runner{};

template<typename TruthFn>
constexpr ArithmeticTestRunner<TruthFn> arithmetic_runner{};

template<typename TruthFn, typename Callable, typename T, typename Runner>
void reduction_test_case(Callable callable, T v, Runner runner)
{
  runner.call_nocx(callable, v);
  runner.call_cx(callable, v, true);
  runner.call_cx(callable, v, false);
  runner.call_cx(callable, v, eve::ignore_none);

  if constexpr (eve::simd_value<T>)
  {
    constexpr auto cardinal = eve::cardinal_v<T>;

    using LT = eve::as_logical_t<T>;
    LT m = tts::poison(LT{ [](auto i, auto) { return i % 2 == 0; } });
    runner.call_cx(callable, v, m);

    runner.call_cx(callable, v, eve::ignore_all);
    runner.call_cx(callable, v, eve::keep_first(0));

    if constexpr (cardinal >= 2)
    {
      runner.call_cx(callable, v, eve::ignore_extrema(1, 1));
      runner.call_cx(callable, v, eve::ignore_extrema(cardinal / 2, cardinal / 2));
      runner.call_cx(callable, v, eve::ignore_extrema(cardinal / 4, cardinal / 4));
    }
  }
}

template<typename TruthFn, typename Callable, typename T>
void logical_reduction_test_case(Callable callable, T v)
{
  constexpr auto runner = logical_runner<TruthFn>;
  reduction_test_case<TruthFn>(callable, v, runner);
}

template<typename TruthFn, typename Callable, typename T>
void logical_reduction_simd_test_cases(Callable callable, eve::as<T> typ)
{
  constexpr auto cardinal = eve::cardinal_v<T>;
  constexpr auto runner = logical_runner<TruthFn>;

  reduction_test_case<TruthFn>(callable, eve::true_(typ), runner);
  reduction_test_case<TruthFn>(callable, eve::false_(typ), runner);

  for (std::ptrdiff_t j = 0; j < cardinal; ++j)
  {
    eve::logical<T> rhs1 = {}, rhs2 = {}, rhs3 = {}, rhs4 = {};

    for (std::ptrdiff_t i = 0; i < cardinal; ++i)
    {
      rhs1.set(i, i >= j ? true : false);
      rhs2.set(i, i <= j ? false : true);
      rhs3.set(i, i == j ? true : false);
      rhs4.set(i, i == j ? false : true);
    }

    reduction_test_case<TruthFn>(callable, rhs1, runner);
    reduction_test_case<TruthFn>(callable, rhs2, runner);
    reduction_test_case<TruthFn>(callable, rhs3, runner);
    reduction_test_case<TruthFn>(callable, rhs4, runner);
  }
}

template<typename TruthFn, typename Callable, typename T>
void arithmetic_reduction_test_case(Callable callable, T v, double expected_ulp = 0.0)
{
  const auto runner = ArithmeticTestRunner<TruthFn>{expected_ulp};
  reduction_test_case<TruthFn>(callable, v, runner);
}

template<typename Callable, eve::arithmetic_simd_value T>
void arithmetic_reduction_simd_type_test(Callable callable, eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  T val{};

  TTS_EXPR_IS((callable(val)), e_t);
  TTS_EXPR_IS((callable[eve::ignore_none](val)), e_t);
  TTS_EXPR_IS((callable[val > 0](val)), e_t);
  TTS_EXPR_IS((callable[true](val)), e_t);

  TTS_EXPR_IS((callable[eve::splat](val)), T);
  TTS_EXPR_IS((callable[eve::splat][eve::ignore_none](val)), T);
  TTS_EXPR_IS((callable[eve::splat][val > 0](val)), T);
  TTS_EXPR_IS((callable[eve::splat][true](val)), T);
}

template<typename Callable, eve::arithmetic_scalar_value T>
void arithmetic_reduction_scalar_type_test(Callable callable, eve::as<T>)
{
  T val{};

  TTS_EXPR_IS((callable(val)), T);
  TTS_EXPR_IS((callable[eve::ignore_none](val)), T);
  TTS_EXPR_IS((callable[true](val)), T);

  TTS_EXPECT_NOT_COMPILES(val, { compile_reject_test(callable[eve::splat], val); });
  TTS_EXPECT_NOT_COMPILES(val, { compile_reject_test(callable[eve::splat][eve::ignore_none], val); });
  TTS_EXPECT_NOT_COMPILES(val, { compile_reject_test(callable[eve::splat][val > 0], val); });
  TTS_EXPECT_NOT_COMPILES(val, { compile_reject_test(callable[eve::splat][true], val); });
}

template<typename Callable, eve::logical_simd_value T>
void logical_reduction_simd_type_test(Callable callable, eve::as<T>)
{
  T val{};

  TTS_EXPR_IS((callable(val)), bool);
  TTS_EXPR_IS((callable[eve::ignore_none](val)), bool);
  TTS_EXPR_IS((callable[val](val)), bool);
  TTS_EXPR_IS((callable[true](val)), bool);

  TTS_EXPR_IS((callable[eve::splat](val)), T);
  TTS_EXPR_IS((callable[eve::splat][eve::ignore_none](val)), T);
  TTS_EXPR_IS((callable[eve::splat][val](val)), T);
  TTS_EXPR_IS((callable[eve::splat][true](val)), T);
}

template<typename Callable, eve::logical_scalar_value T>
void logical_reduction_scalar_type_test(Callable callable, eve::as<T>)
{
  T val{};

  TTS_EXPR_IS((callable(val)), bool);
  TTS_EXPR_IS((callable[eve::ignore_none](val)), bool);
  TTS_EXPR_IS((callable[true](val)), bool);

  TTS_EXPECT_NOT_COMPILES(val, { compile_reject_test(callable[eve::splat], val); });
  TTS_EXPECT_NOT_COMPILES(val, { compile_reject_test(callable[eve::splat][eve::ignore_none], val); });
  TTS_EXPECT_NOT_COMPILES(val, { compile_reject_test(callable[eve::splat][val > 0], val); });
  TTS_EXPECT_NOT_COMPILES(val, { compile_reject_test(callable[eve::splat][true], val); });
}

