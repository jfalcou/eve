//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/detail/function/inner_bit_cast.hpp>

using namespace eve;

template<typename F, typename T, typename U>
void test_with_types(F f)
{
  TTS_TYPE_IS(decltype(f(T{}, U{})), (eve::as_wide_as_t<T, U>));
  TTS_TYPE_IS(decltype(f(kumi::make_tuple(T{}, U{}))), (eve::as_wide_as_t<T, U>));
  TTS_TYPE_IS(decltype(f(U{}, T{})), (eve::as_wide_as_t<U, T>));
  TTS_TYPE_IS(decltype(f(kumi::make_tuple(U{}, T{}))), (eve::as_wide_as_t<U, T>));

  TTS_TYPE_IS(decltype(f(T{}, U{}, T{})), (eve::as_wide_as_t<T, U>));
  TTS_TYPE_IS(decltype(f(kumi::make_tuple(T{}, U{}, T{}))), (eve::as_wide_as_t<T, U>));
}

template<typename T, typename F>
void bit_test_scalar_return_type(F f)
{
  TTS_EXPR_IS(f(T{}, T{}), T);

  // test signedness
  if constexpr (std::signed_integral<T>)
  {
    test_with_types<F, T, std::make_unsigned_t<T>>(f);
  }

  // test mixed integral & floating point
  else if constexpr (eve::floating_value<T>)
  {
    test_with_types<F, T, eve::as_integer_t<T>>(f);
  }
}

template<typename T, typename F>
void bit_test_simd_return_type(F f)
{
  using v_t = element_type_t<T>;

  TTS_EXPR_IS(f(T{}, T{}), T);

  test_with_types<F, T, v_t>(f);

  // test signedness
  if constexpr (std::signed_integral<T>)
  {
    using U = std::make_unsigned_t<T>;
    using e_u = element_type_t<U>;
    test_with_types<F, T, U>(f);
    test_with_types<F, T, e_u>(f);

    // signedness + size diff
    if constexpr (sizeof(e_u) >= 2)
    {
      using DT = eve::as_wide_as_t<eve::downgrade_t<e_u>, typename T::combined_type>;
      test_with_types<F, T, DT>(f);
    }
  }

  //test mixed integral & floating point
  else if constexpr (eve::floating_value<T>)
  {
    using U = eve::as_integer_t<T>;
    using e_u = element_type_t<U>;

    test_with_types<F, T, U>(f);
    test_with_types<F, T, e_u>(f);

    // mixed + size diff
    if constexpr (sizeof(e_u) >= 2)
    {
      using DT = eve::as_wide_as_t<eve::downgrade_t<e_u>, typename T::combined_type>;
      test_with_types<F, T, DT>(f);
    }
  }

  // test size
  using e_dt = eve::downgrade_t<v_t>;
  if constexpr (!std::same_as<e_dt, v_t>)
  {
    using DT = eve::as_wide_as_t<e_dt, typename T::combined_type>;
    test_with_types<F, T, DT>(f);
  }
}

//TODO: move to TTS
template<typename T>
auto check_bit_equal(T a, T b)
{
  using u_t = eve::as_uinteger_t<T>;
  return TTS_EQUAL(inner_bit_cast(a, as<u_t>{}), inner_bit_cast(b, as<u_t>{}));
}

template<typename T, typename F, typename TruthFn>
void bit_test_simd_inner(F fn, TruthFn truthFn, T a, T b, [[maybe_unused]] T c)
{
  const auto invoke_truth_fn = [&](auto va, auto vb, simd_value auto... vc)
  {
    using a_t = decltype(va);
    using b_t = decltype(vb);

    using ra_t = std::conditional_t<eve::simd_value<a_t>, a_t, eve::as_wide_as_t<a_t, b_t>>;
    using rb_t = std::conditional_t<eve::simd_value<b_t>, b_t, eve::as_wide_as_t<b_t, a_t>>;

    using u_t = eve::as_uinteger_t<ra_t>;

    const auto inA = inner_bit_cast(ra_t { va }, as<u_t>{});
    const auto inB = inner_bit_cast(rb_t { vb }, as<u_t>{});

    return inner_bit_cast(eve::detail::map(truthFn, inA, inB, inner_bit_cast(vc, as<u_t>{})...), as<ra_t>{});
  };

  const auto run_case = [&](auto va, auto vb, auto vc)
  {
    // 2-arg version
    const auto res = invoke_truth_fn(va, vb);
    const auto resi = invoke_truth_fn(vb, va);

    check_bit_equal(fn(va, vb), res);
    check_bit_equal(fn(vb, va), resi);
    check_bit_equal(fn(kumi::make_tuple(va, vb)), res);

    // 3-arg version
    const auto res3 = invoke_truth_fn(va, vb, vc);
    const auto res3i = invoke_truth_fn(vb, va, vc);

    check_bit_equal(fn(va, vb, vc), res3);
    check_bit_equal(fn(vb, va, vc), res3i);
    check_bit_equal(fn(kumi::make_tuple(va, vb, vc)), res3);
  };

  run_case(a, b, c);
  run_case(a, b.get(0), c);

  // downgraded
  using v_t  = eve::element_type_t<T>;
  using d_t  = eve::downgrade_t<v_t>;
  if constexpr (!std::same_as<d_t, v_t>)
  {
    using DT = eve::as_wide_as_t<d_t, typename T::combined_type>;
    auto db  = tts::poison(inner_bit_cast(b, eve::as<DT>{}));
    run_case(a, db, c);
  }

  // mixed types
  if constexpr (eve::floating_value<T>)
  {
    using u_t = eve::as_uinteger_t<T>;
    auto ub  = tts::poison(inner_bit_cast(b, eve::as<u_t>{}));
    run_case(a, ub, c);
    run_case(a, ub.get(0), c);

    // mixed + downgraded
    if constexpr (sizeof(T) >= 2)
    {
      using du_t = eve::downgrade_t<u_t>;
      using cdu_t = eve::as_wide_as_t<eve::element_type_t<du_t>, typename T::combined_type>;
      auto dub  = tts::poison(inner_bit_cast(b, eve::as<cdu_t>{}));
      run_case(a, dub, c);
    }
  }
}

template<typename T, typename Mask, typename F>
void bit_test_simd_inner_cx(F fn, T a, T b, [[maybe_unused]] T c, Mask mask)
{
  const auto run_case = [&](auto va, auto vb)
  {
    const auto res = fn(va, vb);
    const auto resi = fn(vb, va);

    if constexpr (eve::conditional_expr<Mask>)
    {
      const auto alt = eve::detail::alternative(mask, va, as(res));
      const auto alti = eve::detail::alternative(mask, vb, as(resi));

      check_bit_equal(fn[mask](va, vb), eve::if_else(mask, res, alt));
      check_bit_equal(fn[mask](vb, va), eve::if_else(mask, resi, alti));
      check_bit_equal(fn[mask](kumi::make_tuple(va, vb)), eve::if_else(mask, res, alt));
    }
    else
    {
      check_bit_equal(fn[mask](va, vb), eve::if_else(mask, res, va));
      check_bit_equal(fn[mask](vb, va), eve::if_else(mask, resi, vb));
      check_bit_equal(fn[mask](kumi::make_tuple(va, vb)), eve::if_else(mask, res, va));
    }
  };

  run_case(a, b);
  run_case(a, b.get(0));

  // mixed types
  if constexpr (eve::floating_value<T>)
  {
    using u_t = eve::as_uinteger_t<T>;
    auto ub  = tts::poison(inner_bit_cast(b, eve::as<u_t>{}));
    run_case(a, ub);
    run_case(a, ub.get(0));
  }
}

template<typename T, typename F, typename TruthFn>
void bit_test_simd(F fn, TruthFn truthFn, T a, T b, T c)
{
  bit_test_simd_inner(fn, truthFn, a, b, c);

  bit_test_simd_inner_cx(fn, a, b, c, eve::ignore_none);
  bit_test_simd_inner_cx(fn, a, b, c, eve::ignore_all);
  bit_test_simd_inner_cx(fn, a, b, c, true);
  bit_test_simd_inner_cx(fn, a, b, c, false);

  eve::logical<T> m = tts::poison(eve::logical<T>{ [](auto i, auto) { return i % 2 == 0; } });
  bit_test_simd_inner_cx(fn, a, b, c, m);
  bit_test_simd_inner_cx(fn, a, b, c, if_(m).else_(24));

  constexpr auto cardinal = eve::cardinal_v<T>;

  if constexpr (cardinal >= 2)
  {
    bit_test_simd_inner_cx(fn, a, b, c, eve::ignore_extrema(1, 1));
    bit_test_simd_inner_cx(fn, a, b, c, eve::ignore_extrema(cardinal / 2, cardinal / 2));
    bit_test_simd_inner_cx(fn, a, b, c, eve::ignore_extrema(cardinal / 4, cardinal / 4));
  }
}
