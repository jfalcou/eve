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

template <typename A, typename B>
static constexpr auto find_priority_type()
{
  using ea_t = eve::as_arithmetic_t<eve::element_type_t<A>>;
  using eb_t = eve::as_arithmetic_t<eve::element_type_t<B>>;

  if constexpr (std::same_as<ea_t, eb_t>)      return A{};
  // smallest type
  else if constexpr (sizeof(ea_t) != sizeof(eb_t))
  {
    if constexpr (sizeof(ea_t) < sizeof(eb_t)) return A{};
    else                                       return B{};
  }
  // unsigned first
  else if constexpr (eve::signed_value<ea_t> != eve::signed_value<eb_t>)
  {
    if constexpr (eve::signed_value<ea_t>)     return B{};
    else                                       return A{};
  }
  // integral first
  else if constexpr (eve::integral_value<ea_t> != eve::integral_value<eb_t>)
  {
    if constexpr (eve::integral_value<ea_t>)   return A{};
    else                                       return B{};
  }
  else                                         return A{};
}

template<typename T, typename U>
using priority_t = eve::as_logical_t<decltype(find_priority_type<T, U>())>;

template<typename T, typename F>
void logical_test_scalar_return_type(F f)
{
  // single type
  TTS_EXPR_IS(f(logical<T>{}, logical<T>{}), logical<T>);
  TTS_EXPR_IS(f(bool{}, logical<T>{}), logical<T>);
  TTS_EXPR_IS(f(logical<T>{}, bool{}), logical<T>);
  TTS_EXPR_IS(f(bool{}, bool{}), bool);

  // test size
  using DT = eve::downgrade_t<T>;
  using UT = eve::upgrade_t<T>;

  TTS_EXPR_IS(f(logical<DT>{}, logical<T>{}), logical<DT>);
  TTS_EXPR_IS(f(logical<T>{}, logical<DT>{}), logical<DT>);

  TTS_EXPR_IS(f(logical<UT>{}, logical<T>{}), logical<T>);
  TTS_EXPR_IS(f(logical<T>{}, logical<UT>{}), logical<T>);

  // test signedness
  if constexpr (std::unsigned_integral<T>)
  {
    using U = std::make_signed_t<T>;
    TTS_EXPR_IS(f(logical<T>{}, logical<U>{}), logical<T>);
    TTS_EXPR_IS(f(logical<U>{}, logical<T>{}), logical<T>);
  }

  // test mixed integral & floating point
  else if constexpr (eve::floating_value<T>)
  {
    using U = eve::as_integer_t<T>;
    TTS_EXPR_IS(f(logical<T>{}, logical<U>{}), logical<U>);
    TTS_EXPR_IS(f(logical<U>{}, logical<T>{}), logical<U>);
  }
}

template<typename T, typename F>
void logical_test_simd_return_type(F f)
{
  using v_t = element_type_t<T>;

  TTS_EXPR_IS(f(logical<T>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(f(logical<T>(), logical<v_t>()), logical<T>);
  TTS_EXPR_IS(f(logical<v_t>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(f(logical<T>(), bool()), logical<T>);
  TTS_EXPR_IS(f(bool(), logical<T>()), logical<T>);

  // test size
  using DT = eve::downgrade_t<T>;
  using e_dt = element_type_t<DT>;
  using UT = eve::upgrade_t<T>;
  using e_ut = element_type_t<UT>;

  TTS_EXPR_IS(f(logical<DT>{}, logical<T>{}), logical<DT>);
  TTS_EXPR_IS(f(logical<T>{}, logical<DT>{}), logical<DT>);
  TTS_EXPR_IS(f(logical<T>{}, logical<e_dt>{}), logical<T>);
  TTS_EXPR_IS(f(logical<e_dt>{}, logical<T>{}), logical<T>);

  TTS_EXPR_IS(f(logical<UT>{}, logical<T>{}), logical<T>);
  TTS_EXPR_IS(f(logical<T>{}, logical<UT>{}), logical<T>);
  TTS_EXPR_IS(f(logical<T>{}, logical<e_ut>{}), logical<T>);
  TTS_EXPR_IS(f(logical<e_ut>{}, logical<T>{}), logical<T>);

  // test signedness
  if constexpr (std::unsigned_integral<T>)
  {
    using U = std::make_signed_t<T>;
    using e_u = element_type_t<U>;
    TTS_EXPR_IS(f(logical<T>{}, logical<U>{}), logical<T>);
    TTS_EXPR_IS(f(logical<U>{}, logical<T>{}), logical<T>);
    TTS_EXPR_IS(f(logical<T>{}, logical<e_u>{}), logical<T>);
    TTS_EXPR_IS(f(logical<e_u>{}, logical<T>{}), logical<T>);
  }

  // test mixed integral & floating point
  else if constexpr (eve::floating_value<T>)
  {
    using U = eve::as_integer_t<T>;
    using e_u = element_type_t<U>;
    TTS_EXPR_IS(f(logical<T>{}, logical<U>{}), logical<U>);
    TTS_EXPR_IS(f(logical<U>{}, logical<T>{}), logical<U>);
    TTS_EXPR_IS(f(logical<T>{}, logical<e_u>{}), logical<T>);
    TTS_EXPR_IS(f(logical<e_u>{}, logical<T>{}), logical<T>);
  }
}

template<typename F, typename T, typename U>
auto compile_test(F f, T a, U b) -> decltype(f(a, b)) { return f(a, b); }

template<typename T, typename U, typename F>
void logical_test_compile_reject(F f)
{
  [[maybe_unused]] const T t{};
  [[maybe_unused]] const U u{};
  [[maybe_unused]] const logical<T> lt{};
  [[maybe_unused]] const logical<U> lu{};
  [[maybe_unused]] const wide<T> wt{};
  [[maybe_unused]] const wide<U> wu{};
  [[maybe_unused]] const logical<wide<T>> lwt{};
  [[maybe_unused]] const logical<wide<U>> lwu{};
  [[maybe_unused]] const bool b{};

  TTS_EXPECT_NOT_COMPILES(t, u, { compile_test(f, t, u); });
  TTS_EXPECT_NOT_COMPILES(t, b, { compile_test(f, t, b); });
  TTS_EXPECT_NOT_COMPILES(b, t, { compile_test(f, b, t); });

  TTS_EXPECT_NOT_COMPILES(t, wu, { compile_test(f, t, wu); });
  TTS_EXPECT_NOT_COMPILES(lt, wu, { compile_test(f, lt, wu); });
  TTS_EXPECT_NOT_COMPILES(wt, wu, { compile_test(f, wt, wu); });
  TTS_EXPECT_NOT_COMPILES(lwt, wu, { compile_test(f, lwt, wu); });

  TTS_EXPECT_NOT_COMPILES(wt, u, { compile_test(f, wt, u); });
  TTS_EXPECT_NOT_COMPILES(wt, lu, { compile_test(f, wt, lu); });
  TTS_EXPECT_NOT_COMPILES(wt, lwu, { compile_test(f, wt, lwu); });
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
