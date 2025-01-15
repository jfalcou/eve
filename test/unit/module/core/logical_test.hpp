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

using namespace eve;

template<typename F, typename T, typename U, typename Expected>
void test_with_types(F f)
{
  TTS_TYPE_IS(decltype(f(T{}, U{})), Expected);
  TTS_TYPE_IS(decltype(f(U{}, T{})), Expected);
}

template<typename F>
void logical_test_special_cases(F f)
{
  TTS_EXPR_IS(f(bool{}, bool{}), bool);

  if constexpr (sizeof(long) == sizeof(long long))
  {
    test_with_types<F, long, long long, long long>(f);
  }
}

template<typename T, typename F>
void logical_test_scalar_return_type(F f)
{
  // single type
  TTS_EXPR_IS(f(logical<T>{}, logical<T>{}), logical<T>);
  TTS_EXPR_IS(f(bool{}, bool{}), bool);

  test_with_types<F, bool, logical<T>, logical<T>>(f);

  // test signedness
  if constexpr (std::signed_integral<T>)
  {
    using U = std::make_unsigned_t<T>;
    test_with_types<F, logical<T>, logical<U>, logical<U>>(f);
  }

  // test mixed integral & floating point
  else if constexpr (eve::floating_value<T>)
  {
    using U = eve::as_integer_t<T>;
    test_with_types<F, logical<T>, logical<U>, logical<U>>(f);
  }

  // test size
  using DT = eve::downgrade_t<T>;
  using UT = eve::upgrade_t<T>;

  test_with_types<F, logical<T>, logical<DT>, logical<DT>>(f);
  test_with_types<F, logical<T>, logical<UT>, logical<T>>(f);
}

template<typename T, typename F>
void logical_test_simd_return_type(F f)
{
  using v_t = element_type_t<T>;

  TTS_EXPR_IS(f(logical<T>{}, logical<T>{}), logical<T>);

  test_with_types<F, logical<T>, logical<v_t>, logical<T>>(f);
  test_with_types<F, logical<T>, bool, logical<T>>(f);

  // test signedness
  if constexpr (std::signed_integral<T>)
  {
    using U = std::make_unsigned_t<T>;
    using e_u = element_type_t<U>;
    test_with_types<F, logical<T>, logical<U>, logical<U>>(f);
    test_with_types<F, logical<T>, logical<e_u>, logical<T>>(f);
  }

  // test mixed integral & floating point
  else if constexpr (eve::floating_value<T>)
  {
    using U = eve::as_integer_t<T>;
    using e_u = element_type_t<U>;

    test_with_types<F, logical<T>, logical<U>, logical<U>>(f);
    test_with_types<F, logical<T>, logical<e_u>, logical<T>>(f);
  }

  // test size
  using DT = eve::downgrade_t<T>;
  using e_dt = element_type_t<DT>;
  using UT = eve::upgrade_t<T>;
  using e_ut = element_type_t<UT>;

  test_with_types<F, logical<T>, logical<DT>, logical<DT>>(f);
  test_with_types<F, logical<T>, logical<e_dt>, logical<T>>(f);
  test_with_types<F, logical<T>, logical<UT>, logical<T>>(f);
  test_with_types<F, logical<T>, logical<e_ut>, logical<T>>(f);
}

template<typename F, typename T, typename U>
auto compile_reject_test(F f, T a, U b) -> decltype(f(a, b), f(b, a)) { }

template<typename T, typename F>
void logical_test_compile_reject(F f)
{
  [[maybe_unused]] const T t{};
  [[maybe_unused]] const logical<T> lt{};
  [[maybe_unused]] const wide<T> wt{};
  [[maybe_unused]] const logical<wide<T>> lwt{};
  [[maybe_unused]] const bool b{};

  TTS_EXPECT_NOT_COMPILES(t, b, { compile_reject_test(f, t, b); });
  TTS_EXPECT_NOT_COMPILES(t, { compile_reject_test(f, t, t); });
  TTS_EXPECT_NOT_COMPILES(t, lt, { compile_reject_test(f, t, lt); });
  TTS_EXPECT_NOT_COMPILES(t, wt, { compile_reject_test(f, t, wt); });
  TTS_EXPECT_NOT_COMPILES(t, lwt, { compile_reject_test(f, t, lwt); });

  TTS_EXPECT_NOT_COMPILES(wt, b, { compile_reject_test(f, wt, b); });
  TTS_EXPECT_NOT_COMPILES(wt, lt, { compile_reject_test(f, wt, lt); });
  TTS_EXPECT_NOT_COMPILES(wt, { compile_reject_test(f, wt, wt); });
  TTS_EXPECT_NOT_COMPILES(wt, lwt, { compile_reject_test(f, wt, lwt); });
}

template<typename M, typename T, typename F, typename FS>
void logical_test_simd(F ff, FS fs, M l0, M l1, T a0)
{
  using l_t = eve::element_type_t<M>;

  TTS_EQUAL(ff(l0, l1), tts::map([&](auto e, auto f) -> l_t { return fs(e, f); }, l0, l1));
  TTS_EQUAL(ff(l0, l1.get(0)), tts::map([&](auto e) -> l_t { return fs(e, l1.get(0)); }, l0));
  TTS_EQUAL(ff(l0.get(0), l1), tts::map([&](auto e) -> l_t { return fs(l0.get(0), e); }, l1));

  // downgraded
  using v_t  = eve::element_type_t<T>;
  using d_t  = eve::downgrade_t<v_t>;
  using ld_t  = eve::as_logical_t<d_t>;
  auto da0   = eve::convert(a0, eve::as<d_t>());
  TTS_EQUAL(ff(l1, da0 > 1), tts::map([&](auto e, auto f) -> ld_t { return bool{fs(e, f > 1)}; }, l1, da0));
  TTS_EQUAL(ff(da0 > 1, l1), tts::map([&](auto e, auto f) -> ld_t { return bool{fs(e > 1, f)}; }, da0, l1));

  TTS_EQUAL(ff((da0 > 1).get(0), l0), tts::map([&](auto e) -> l_t { return bool{fs((da0 > 1).get(0), e)}; }, l0));
  TTS_EQUAL(ff(l0, (da0 > 1).get(0)), tts::map([&](auto e) -> l_t { return bool{fs(e, (da0 > 1).get(0))}; }, l0));

  // upgraded
  using u_t  = eve::upgrade_t<v_t>;
  auto ua0   = eve::convert(a0, eve::as<u_t>());
  TTS_EQUAL(ff(l1, ua0 > 1), tts::map([&](auto e, auto f) -> l_t { return bool{fs(e, f > 1)}; }, l1, ua0));
  TTS_EQUAL(ff(ua0 > 1, l1), tts::map([&](auto e, auto f) -> l_t { return bool{fs(e > 1, f)}; }, ua0, l1));

  TTS_EQUAL(ff((ua0 > 1).get(0), l0), tts::map([&](auto e) -> l_t { return bool{fs((ua0 > 1).get(0), e)}; }, l0));
  TTS_EQUAL(ff(l0, (ua0 > 1).get(0)), tts::map([&](auto e) -> l_t { return bool{fs(e, (ua0 > 1).get(0))}; }, l0));
}
