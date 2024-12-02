//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

using namespace eve;

template<typename L1> struct rewrap;
template<typename... Ts>
struct rewrap<kumi::tuple<Ts...>> { using type = tts::types<Ts...>; };

template<typename L1, typename L2> struct cartesian;

template<typename... T1s, typename... T2s>
struct cartesian<tts::types<T1s...>, tts::types<T2s...>>
{
  using base       = kumi::result::cartesian_product_t<kumi::tuple<T1s...>,kumi::tuple<T2s...>>;
  using types_list = typename rewrap<base>::type;
};

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::logical_and(scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS(logical_and(logical<T>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(logical_and(bool(), logical<T>()), logical<T>);
  TTS_EXPR_IS(logical_and(logical<T>(), bool()), logical<T>);
  TTS_EXPR_IS(logical_and(T(), bool()), logical<T>);
  TTS_EXPR_IS(logical_and(bool(), T()), logical<T>);
  TTS_EXPR_IS(logical_and(bool(), bool()), bool);
};

TTS_CASE_TPL("Check return types of eve::logical_and(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = element_type_t<T>;

  TTS_EXPR_IS(logical_and(logical<T>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(logical_and(logical<T>(), logical<v_t>()), logical<T>);
  TTS_EXPR_IS(logical_and(logical<v_t>(), logical<T>()), logical<T>);
  TTS_EXPR_IS(logical_and(logical<v_t>(), bool()), logical<v_t>);
  TTS_EXPR_IS(logical_and(bool(), logical<v_t>()), logical<v_t>);
  TTS_EXPR_IS(logical_and(logical<T>(), bool()), logical<T>);
  TTS_EXPR_IS(logical_and(bool(), logical<T>()), logical<T>);
};

//==================================================================================================
//== Tests for eve::logical_and
//==================================================================================================
TTS_CASE("Check return types of eve::logical_and(bool)")
{
  TTS_EQUAL(logical_and(true, true), true);
  TTS_EQUAL(logical_and(true, false), false);
  TTS_EQUAL(logical_and(false, true), false);
  TTS_EQUAL(logical_and(false, false), false);
};

template<typename T, typename U>
auto test_type(T a, U b) -> decltype(logical_and(a, b)) { return logical_and(a, b); }

TTS_CASE_TPL("Check behavior of eve::logical_and(wide)"
            , cartesian<eve::test::scalar::all_types, eve::test::scalar::all_types>
            )
<typename T, typename U>( tts::type<kumi::tuple<T, U>> )
{
  [[maybe_unused]] const T t{};
  [[maybe_unused]] const U u{};
  [[maybe_unused]] const logical<T> lt{};
  [[maybe_unused]] const logical<U> lu{};
  [[maybe_unused]] const wide<T> wt{};
  [[maybe_unused]] const wide<U> wu{};
  [[maybe_unused]] const logical<wide<T>> lwt{};
  [[maybe_unused]] const logical<wide<U>> lwu{};

  TTS_EXPECT_NOT_COMPILES(t, wu, { test_type(t, wu); });
  TTS_EXPECT_NOT_COMPILES(lt, wu, { test_type(lt, wu); });
  TTS_EXPECT_NOT_COMPILES(wt, wu, { test_type(wt, wu); });
  TTS_EXPECT_NOT_COMPILES(lwt, wu, { test_type(lwt, wu); });

  TTS_EXPECT_NOT_COMPILES(wt, u, { test_type(wt, u); });
  TTS_EXPECT_NOT_COMPILES(wt, lu, { test_type(wt, lu); });
  TTS_EXPECT_NOT_COMPILES(wt, lwu, { test_type(wt, lwu); });
};

TTS_CASE_WITH("Check behavior of eve::logical_and(logical<wide>)",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(0, 3), tts::logicals(1, 2), tts::randoms(0, 2)))
<typename M, typename T>(M const& l0, [[maybe_unused]] M const& l1, [[maybe_unused]] T const& a0)
{
  using l_t = eve::element_type_t<M>;

  TTS_EQUAL(eve::logical_and(l0, true), tts::map([](auto e) -> l_t { return e; }, l0));
  TTS_EQUAL(eve::logical_and(true, l1), tts::map([](auto e) -> l_t { return e; }, l1));
  TTS_EQUAL(eve::logical_and(l0, true), tts::map([](auto e) -> l_t { return e; }, l0));
  TTS_EQUAL(eve::logical_and(l0, false), eve::false_(eve::as<M>()));
  TTS_EQUAL(eve::logical_and(l0, l1), tts::map([](auto e, auto f) -> l_t { return e && f; }, l0, l1));
  TTS_EQUAL(eve::logical_and(l0, l1.get(0)),
            tts::map([&](auto e) -> l_t { return e && l1.get(0); }, l0));
  TTS_EQUAL(eve::logical_and(l0.get(0), l1),
            tts::map([&](auto f) -> l_t { return l0.get(0) && f; }, l1));
  using v_t  = eve::element_type_t<T>;
  using d_t  = eve::downgrade_t<v_t>;
  auto da0   = eve::convert(a0, eve::as<d_t>());
  using dl_t = eve::as_logical_t<d_t>;
  TTS_EQUAL(eve::logical_and(l1, da0 > 1),
            tts::map([](auto e, auto f) -> l_t { return (f > 1) && e; }, l1, da0));
  TTS_EQUAL(eve::logical_and(da0 > 1, l1),
            tts::map([](auto e, auto f) -> dl_t { return bool((e > 1) && f); }, da0, l1));

  // Mixed type regression test, see #1959
  TTS_EQUAL(eve::logical_and((da0 > 1).get(0), l0), tts::map([&](auto e) -> l_t { return e && (da0 > 1).get(0); }, l0));
  TTS_EQUAL(eve::logical_and(l0, (da0 > 1).get(0)), tts::map([&](auto e) -> l_t { return e && (da0 > 1).get(0); }, l0));
};
