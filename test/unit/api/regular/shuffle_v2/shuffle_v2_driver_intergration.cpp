//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

namespace
{

constexpr auto perfect_native_shuffler =
    []<std::ptrdiff_t... I>(eve::pattern_t<I...> p, auto g, auto... xs)
{
  if constexpr( !eve::supports_simd ) { TTS_FAIL("should not be called: " + tts::as_string(p)); }
  else
  {
    auto shuffled = get<0>(eve::detail::shuffle_emulated(p, g, kumi::tuple {xs...}));
    // mock level matches to size of the pattern
    constexpr std::array idxs {I...};
    constexpr int complexity = decltype(p)::size() - std::count(idxs.begin(), idxs.end(), eve::we_);
    return kumi::tuple {shuffled, eve::index<complexity>};
  }
};

constexpr auto perfect_shuffler = eve::detail::make_shuffle_v2(perfect_native_shuffler);

constexpr auto never_native_shuffler = eve::detail::make_shuffle_v2(
    []<std::ptrdiff_t... I>(eve::pattern_t<I...> p, auto g, auto... xs)
    {
      TTS_FAIL("should not be called: " + tts::as_string(p));
      return perfect_native_shuffler(p, g, xs...);
    });

auto
tst_for_shuffler(auto shuffler)
{
  return [shuffler](auto expected, auto expected_l, auto... args)
  {
    auto [shuffled, l] = shuffler(args...);
    if constexpr( !eve::supports_simd ) { TTS_EQUAL(0, l()) << expected; }
    else { TTS_EQUAL(expected_l, l) << expected; }
    TTS_EQUAL(expected, shuffled);
  };
}

TTS_CASE("integrating with fake native shuffle")
{
  auto tst = tst_for_shuffler(perfect_shuffler);

  using T = eve::wide<int, eve::fixed<4>>;

  tst(T {3, 4, 1, 2}, eve::index<2>, T {1, 2, 3, 4}, eve::lane<2>, eve::pattern<1, 0>);
  tst(T {4, 3, 2, 1}, eve::index<4>, T {1, 2, 3, 4}, eve::pattern<3, 2, 1, 0>);
  tst(T {3, 4, 1, 2}, eve::index<2>, T {1, 2, 3, 4}, eve::pattern<2, 3, 0, 1>);
  tst(T {0, 0, 1, 2}, eve::index<1>, T {1, 2, 3, 4}, eve::lane<2>, eve::pattern<eve::we_, 0>);
  tst(T {3, 4, 0, 0}, eve::index<2>, T {1, 2, 3, 4}, eve::lane<2>, eve::pattern<1, eve::na_>);

  // T05
  using T025 = eve::wide<int, eve::fixed<1>>;
  using T05  = eve::wide<int, eve::fixed<2>>;
  using T2   = eve::wide<int, eve::fixed<8>>;

  tst(T05 {4, 2}, eve::index<2>, T {1, 2, 3, 4}, eve::pattern<3, 1>);
  tst((T {7, 5, 3, 1}), eve::index<4>, T {1, 2, 3, 4}, T {5, 6, 7, 8}, eve::pattern<6, 4, 2, 0>);
  tst((T {7, 5, 3, 1}), eve::index<4>, T2 {1, 2, 3, 4, 5, 6, 7, 8}, eve::pattern<6, 4, 2, 0>);
  tst(T05 {3, 4}, eve::index<1>, T {1, 2, 3, 4}, eve::lane<2>, eve::pattern<1>);
  tst(T {7, 8, 3, 4},
      eve::index<2>,
      T {1, 2, 3, 4},
      T {5, 6, 7, 8},
      eve::lane<2>,
      eve::pattern<3, 1>);
  tst(T {7, 8, 3, 4}, eve::index<2>, T2 {1, 2, 3, 4, 5, 6, 7, 8}, eve::lane<2>, eve::pattern<3, 1>);

  // Common l0, l1
  tst(T025 {1}, eve::index<0>, T05 {1, 2}, eve::pattern<0>);
  tst(T025 {eve::supports_simd ? 1 : 0}, eve::index<0>, T05 {1, 2}, eve::pattern<eve::we_>);
  tst(T025 {0}, eve::index<1>, T05 {1, 2}, eve::pattern<eve::na_>);
  tst(T025 {0}, eve::index<1>, T2 {1, 2, 3, 4, 5, 6, 7, 8}, eve::pattern<eve::na_>);
  tst(T {0, 0, 0, 0},
      eve::index<1>,
      T {1, 2, 3, 4},
      eve::lane<2>,
      eve::pattern<eve::we_, eve::na_>);

  // L
  using L = eve::logical<T>;
  tst(L {true, false, true, true},
      eve::index<4>,
      L {true, true, false, true},
      eve::pattern<3, 2, 1, 0>);

  // To bigger size
  using TxT = eve::wide<kumi::tuple<int, int>, T::cardinal_type>;
  tst(TxT {T {3, 4, 1, 2}, T {1, 2, 1, 2}},
      eve::index<2>,
      T {1, 2, 3, 4},
      eve::lane<2>,
      eve::pattern<1, 0, 0, 0>);

  tst(TxT {T {5, 6, 1, 2}, T {5, 6, 7, 8}},
      eve::index<2>,
      T {1, 2, 3, 4},
      T {5, 6, 7, 8},
      eve::lane<2>,
      eve::pattern<2, 0, 2, 3>);

  tst(T2 {5, 6, 1, 2, 5, 6, 7, 8},
      eve::index < eve::has_aggregated_abi_v<T2> ? 2 : 4 >,
      T2 {1, 2, 3, 4, 5, 6, 7, 8},
      eve::lane<2>,
      eve::pattern<2, 0, 2, 3>);

  // Bundle
  {
    using ETxL     = kumi::tuple<int, eve::logical<int>>;
    using TxL      = eve::wide<ETxL, T::cardinal_type>;
    using TLxTL    = eve::wide<kumi::tuple<ETxL, ETxL>, T::cardinal_type>;
    using TLxTLxTL = eve::wide<kumi::tuple<ETxL, ETxL, ETxL>, T::cardinal_type>;

    TxL in {T {1, 2, 3, 4}, L {false, true, true, false}};
    TxL out {T {3, 4, 1, 2}, L {true, false, false, true}};

    tst(out, eve::index<2>, in, eve::lane<2>, eve::pattern<1, 0>);
    tst(in.slice(eve::upper_), eve::index<1>, in, eve::lane<2>, eve::pattern<1>);
    tst(TLxTL {out, out}, eve::index<2>, in, eve::lane<2>, eve::pattern<1, 0, 1, 0>);
    tst(TLxTLxTL {out, out, out}, eve::index<2>, in, eve::lane<2>, eve::pattern<1, 0, 1, 0, 1, 0>);
  }
};

TTS_CASE("identites and 0s masking integration tests")
{
  using T      = eve::wide<int, eve::fixed<4>>;
  using half_T = eve::wide<int, eve::fixed<2>>;

  // Identities
  {
    auto tst = tst_for_shuffler(never_native_shuffler);
    tst(T {1, 2, 3, 4}, eve::index<0>, T {1, 2, 3, 4}, eve::lane<1>, eve::pattern<0, 1, 2, 3>);

    tst(eve::supports_simd  ? T {1, 2, 3, 4} : T{1, 0, 3, 4},
        eve::index<0>,
        T {1, 2, 3, 4},
        eve::lane<1>,
        eve::pattern<0, eve::we_, 2, 3>);
  }

  // Full zero
  {
    auto tst = tst_for_shuffler(never_native_shuffler);
    tst(T {0, 0, 0, 0},
        eve::index<1>,
        T {1, 2, 3, 4},
        eve::lane<1>,
        eve::pattern<eve::na_, eve::na_, eve::na_, eve::na_>);
    tst(half_T {0, 0},
        eve::index<1>,
        T {1, 2, 3, 4},
        eve::lane<1>,
        eve::pattern<eve::na_, eve::na_>);
  }

  constexpr bool free_masking = eve::current_api >= eve::avx512 || eve::current_api >= eve::sve
                                || eve::current_api >= eve::rvv;

  if( !free_masking )
  {
    TTS_PASS();
    return;
  }

  // Masked Identities
  {
    auto tst = tst_for_shuffler(never_native_shuffler);
    tst(T {1, 0, 3, 0},
        eve::index<2>,
        T {1, 2, 3, 4},
        eve::lane<1>,
        eve::pattern<0, eve::na_, 2, eve::na_>);
    tst(T {1, 2, 0, 0},
        eve::index<2>,
        T {1, 2, 3, 4},
        eve::lane<1>,
        eve::pattern<0, eve::we_, eve::na_, eve::na_>);
  }

  // Normal masking
  {
    auto tst = tst_for_shuffler(perfect_shuffler);
    tst(T {0, 1, 3, 4},
        eve::index<3>,
        T {1, 2, 3, 4},
        eve::lane<1>,
        eve::pattern<eve::na_, 0, 2, 3>);
    tst(T {0, 1, 0, 0},
        eve::index<2>,
        T {1, 2, 3, 4},
        eve::lane<1>,
        eve::pattern<eve::na_, 0, eve::we_, eve::na_>);
  }
};

TTS_CASE_TPL("G >= T::size()", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  auto tst = tst_for_shuffler(never_native_shuffler);

  // normal
  {
    using e_t     = eve::element_type_t<T>;
    using TxT     = eve::wide<kumi::tuple<e_t, e_t>, typename T::cardinal_type>;
    using TxTxTxT = eve::wide<kumi::tuple<e_t, e_t, e_t, e_t>, typename T::cardinal_type>;

    tst(TxT {T {0}, T {0}}, 0, T {0}, eve::lane<T::size()>, eve::pattern<0, 0>);
    tst(TxTxTxT {T {0}, T {1}, T {0}, T {1}},
        0,
        T {0},
        T {1},
        eve::lane<T::size() * 2>,
        eve::pattern<0, 0>);
    tst(TxTxTxT {T {1}, T {2}, T {0}, T {0}},
        eve::has_emulated_abi_v<T> ? 0 : 1,
        T {1},
        T {2},
        eve::lane<T::size() * 2>,
        eve::pattern<0, eve::na_>);

    auto [shuffled, l] =
        never_native_shuffler(T {1}, T {2}, eve::lane<T::size() * 2>, eve::pattern<0, eve::we_>);
    auto [x0, x1, _0, _1] = shuffled;
    TTS_EQUAL(x0, T {1});
    TTS_EQUAL(x1, T {2});
    TTS_EQUAL(l(), 0);
  }

  // bundle
  {
    using e_t     = kumi::tuple<eve::element_type_t<T>, eve::logical<std::int8_t>>;
    using U       = eve::wide<e_t, typename T::cardinal_type>;
    using UxU     = eve::wide<kumi::tuple<e_t, e_t>, typename T::cardinal_type>;
    using UxUxUxU = eve::wide<kumi::tuple<e_t, e_t, e_t, e_t>, typename T::cardinal_type>;

    tst(UxU {U {0, false}, U {0, false}},
        0,
        U {0, false},
        eve::lane<T::size()>,
        eve::pattern<0, 0>);
    tst(UxUxUxU {U {0, false}, U {1, true}, U {0, false}, U {1, true}},
        0,
        U {0, false},
        U {1, true},
        eve::lane<T::size() * 2>,
        eve::pattern<0, 0>);
    tst(UxUxUxU {U {1, false}, U {2, true}, U {0, false}, U {0, false}},
        eve::has_emulated_abi_v<T> && eve::has_emulated_abi_v<eve::wide<std::uint8_t>> ? 0 : 1,
        U {1, false},
        U {2, true},
        eve::lane<T::size() * 2>,
        eve::pattern<0, eve::na_>);

    auto [shuffled, l] = never_native_shuffler(
        U {1, false}, U {2, true}, eve::lane<T::size() * 2>, eve::pattern<0, eve::we_>);
    auto [x0, x1, _0, _1] = shuffled;
    TTS_EQUAL(x0, (U {1, false}));
    TTS_EQUAL(x1, (U {2, true}));
    TTS_EQUAL(l(), 0);
  }
};
}
