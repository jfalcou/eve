//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

namespace shuffle_test
{

namespace idxm = eve::detail::idxm;

template<typename T, typename N, typename U, std::ptrdiff_t G, std::ptrdiff_t... I>
void
verify(eve::wide<T, N> x, eve::fixed<G>, eve::pattern_t<I...> p, eve::wide<T, U> shuffled)
{
  std::array<T, N::value> x_a;
  eve::store(x, x_a.data());

  std::array<T, U::value> shuffled_a;
  eve::store(shuffled, shuffled_a.data());

  bool has_failures = [&]
  {
    if( G * sizeof...(I) != U::value ) return true;

    int out_i = 0;
    for( auto group_i : {I...} )
    {
      for( int within_i = 0; within_i != G; ++within_i )
      {
        T actual = shuffled_a[out_i++];
        T expected;

        if( group_i == eve::na_ ) expected = 0;
        else if( group_i == eve::we_ ) continue;
        else expected = x_a[group_i * G + within_i];

        if( expected != actual ) { return true; }
      }
    }
    return false;
  }();

  TTS_EXPECT(!has_failures) << "G: " << G << "\npattern: " << p << "\nactual:  " << shuffled;
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G, std::ptrdiff_t... I>
void
run(auto expected_level, eve::pattern_t<I...> p = {})
{
  using Wide = eve::wide<T, eve::fixed<N>>;

  Wide input {[](int i, int) { return i + 1; }};
  if constexpr (requires { eve::shuffle_v2_core(input, eve::lane<G>, p); })
  {
    auto [shuffled, l] = eve::shuffle_v2_core(input, eve::lane<G>, p);
    verify(input, eve::lane<G>, p, shuffled);
    if constexpr ( eve::supports_simd )
    {
      TTS_EQUAL(expected_level(std::array{I...}), l()) << "G: " << G << "\npattern: " << p;
    }
    else
    {
      TTS_EQUAL(0, l()) << "G: " << G << "\npattern: " << p;
    }
  }
  else
  {
    TTS_FAIL("Failed to shuffle, G: " << G << "\npattern: " << p);
  }
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G, std::ptrdiff_t... I>
void
run2(auto expected_level, eve::pattern_t<I...> p = {})
{
  using Wide = eve::wide<T, eve::fixed<N * 2>>;

  Wide input {[](int i, int) { return i + 1; }};
  auto xy = input.slice();
  auto x = get<0>(xy);
  auto y = get<1>(xy);

  if constexpr (requires { eve::shuffle_v2_core(x, y, eve::lane<G>, p); })
  {
    auto [shuffled, l] = eve::shuffle_v2_core(x, y, eve::lane<G>, p);
    verify(input, eve::lane<G>, p, shuffled);
    TTS_EQUAL(expected_level(std::array{I...}), l()) << "G: " << G << "\npattern: " << p;
  }
  else
  {
    TTS_FAIL("Failed to shuffle, G: " << G << "\npattern: " << p);
  }
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G, auto tests>
void
run_all(auto expected_level)
{
  [&]<std::size_t... i>(std::index_sequence<i...>) {
    (run<T, N, G>(expected_level, idxm::to_pattern<tests[i]>()), ...);
  }(std::make_index_sequence<tests.size()> {});
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G, auto tests>
void
run2_all(auto expected_level)
{
  [&]<std::size_t... i>(std::index_sequence<i...>) {
    (run2<T, N, G>(expected_level, idxm::to_pattern<tests[i]>()), ...);
  }(std::make_index_sequence<tests.size()> {});
}


template<std::size_t N> using arr = std::array<std::ptrdiff_t, N>;

template<typename T, std::size_t N> struct concat_op
{
  std::array<T, N> self;

  template<std::size_t N1> constexpr auto operator+(const std::array<T, N1>& x) const
  {
    concat_op<T, N + N1> res = {};
    auto                 it  = res.self.begin();
    it                       = std::copy(self.begin(), self.end(), it);
    std::copy(x.begin(), x.end(), it);
    return res;
  }
};

template<typename T, std::size_t N> concat_op(std::array<T, N>) -> concat_op<T, N>;

template<typename A0, typename... As>
constexpr auto
concat(const A0& a0, const As&...as)
{
  return (concat_op {a0} + ... + as).self;
}

template<std::size_t Len>
constexpr arr<Len>
toRightHalf(arr<Len> in)
{
  for( auto& x : in )
  {
    if( x < 0 ) continue;
    x += (std::ptrdiff_t)Len;
  }
  return in;
}

template<std::size_t N, std::size_t Len>
constexpr std::array<arr<Len * 2>, N>
matchRightLane(const std::array<arr<Len>, N>& in)
{
  std::array<arr<Len * 2>, N> res = {};
  for( std::size_t i = 0; i != N; ++i ) { res[i] = concat(in[i], toRightHalf(in[i])); }
  return res;
}

// Do not repeat patterns that occur when doubling up
// We also don't test all we_ because there is a lot of them
[[maybe_unused]] constexpr std::array kLen1Tests = {
    arr<1> {0},        //
    arr<1> {eve::we_}, //
    arr<1> {eve::na_}, //
};

[[maybe_unused]] constexpr std::array kLen2No0sTests = {
    arr<2> {0, 0},        //
    arr<2> {1, 0},        //
    arr<2> {1, 1},        //
    arr<2> {1, eve::we_}, //
    arr<2> {eve::we_, 0}, //
};

[[maybe_unused]] constexpr std::array kLen20sTests = {
    arr<2> {0, eve::na_}, //
    arr<2> {eve::na_, 0}, //
    arr<2> {1, eve::na_}, //
};

[[maybe_unused]] constexpr std::array kLen2Tests = concat(kLen2No0sTests, kLen20sTests);

[[maybe_unused]] constexpr std::array kLen4No0sTests_OnlyLhs = {
    arr<4> {0, 0, 2, 3}, //
    arr<4> {1, 0, 2, 3}, //
    arr<4> {1, 1, 2, 3}, //
    // ---
    arr<4> {1, eve::we_, 2, 3}, //
    arr<4> {eve::we_, 0, 2, 3}, //
    arr<4> {1, 0, eve::we_, 3}, //
    arr<4> {1, 0, 2, eve::we_}, //
    //--
    arr<4> {eve::we_, 0, eve::we_, 3}, //
    arr<4> {1, eve::we_, 2, eve::we_}, //
};

[[maybe_unused]] constexpr std::array kLen4No0sTests_OnlyRhs = {
    arr<4> {0, 1, 2, 2}, //
    arr<4> {0, 1, 3, 2}, //
    arr<4> {0, 1, 3, 3}, //
    // ---
    arr<4> {0, eve::we_, 2, 2},        //
    arr<4> {0, eve::we_, 3, 2},        //
    arr<4> {0, eve::we_, 3, eve::we_}, //
    arr<4> {eve::we_, 1, 3, 3},        //
    arr<4> {eve::we_, 1, 3, eve::we_}, //
};

[[maybe_unused]] constexpr std::array kLen4No0sTests_Repeat = {
    arr<4> {0, 0, 2, 2}, //
    arr<4> {1, 0, 3, 2}, //
    arr<4> {1, 1, 3, 3}, //
    // ---
    arr<4> {0, eve::we_, 2, 2},        //
    arr<4> {eve::we_, 1, 3, eve::we_}, //
    arr<4> {eve::we_, 0, eve::we_, 2}, //
};

[[maybe_unused]] constexpr std::array kLen4No0Tests_IndependentHalves_Both = {
    arr<4> {1, 0, 2, 2}, //
    arr<4> {1, 1, 2, 2}, //
    // ----
    arr<4> {0, 0, 3, 2}, //
    arr<4> {1, 1, 3, 2}, //
    // ----
    arr<4> {0, 0, 3, 3}, //
    arr<4> {1, 0, 3, 3}, //
    // ----
    arr<4> {1, eve::we_, 2, 2},        //
    arr<4> {1, 1, 2, eve::we_},        //
    arr<4> {eve::we_, 0, 3, eve::we_}, //
    arr<4> {0, 0, 3, eve::we_},        //
};

[[maybe_unused]] constexpr std::array kLen4No0Tests_IndependentHalves =
    concat(kLen4No0sTests_OnlyLhs,
           kLen4No0sTests_OnlyRhs,
           kLen4No0sTests_Repeat,
           kLen4No0Tests_IndependentHalves_Both);

[[maybe_unused]] constexpr std::array kLen4No0Tests_IndependentHalves_Reversed = []
{
  auto res = kLen4No0Tests_IndependentHalves;

  for( auto& x : res )
  {
    std::swap(x[0], x[2]);
    std::swap(x[1], x[3]);
  }

  return res;
}();

// Too many to do all
[[maybe_unused]] constexpr std::array kLen4No0Tests_Scrambled = {
    arr<4> {0, 1, 0, 0}, //
    arr<4> {1, 0, 1, 1}, //
    // ---
    arr<4> {2, 3, 3, 2}, //
    arr<4> {3, 2, 3, 2}, //
    // ---
    arr<4> {3, 0, 0, 1}, //
    arr<4> {1, 2, 3, 2}, //
    arr<4> {0, 1, 3, 1}, //
    // ---
    arr<4> {3, eve::we_, 0, 1},        //
    arr<4> {3, eve::we_, eve::we_, 0}, //
};

[[maybe_unused]] constexpr std::array kLen4N0Tests_CrossLane =
    concat(kLen4No0Tests_IndependentHalves_Reversed, kLen4No0Tests_Scrambled);

// Do not repeat shuffle 4
[[maybe_unused]]
constexpr std::array kRotate8 = {
    arr<8> {1, 2, 3, 4, 5, 6, 7, 0},               //
    arr<8> {3, 4, 5, 6, 7, 0, 1, 2},               //
    arr<8> {5, 6, 7, 0, 1, 2, 3, 4},               //
    arr<8> {7, 0, 1, 2, 3, 4, 5, 6},               //
    arr<8> {1, eve::we_, 3, 4, 5, eve::we_, 7, 0}, //
};

[[maybe_unused]]
constexpr std::array kRotate16 = {
    arr<16> {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0}, //
    arr<16> {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2}, //
};

// -----------------------------------------------------------------------------
// 2 register tests

[[maybe_unused]] constexpr std::array kLen1x2Tests = {
    arr<1> {0},        //
    arr<1> {1},        //
    arr<1> {eve::we_}, //
    arr<1> {eve::na_}, //
};

[[maybe_unused]] constexpr std::array kLen2x2_No0sTests = {
    arr<2> {0, 0},        //
    arr<2> {1, 0},        //
    arr<2> {1, 1},        //
    arr<2> {1, eve::we_}, //
    arr<2> {eve::we_, 0}, //
    //---------------------
    arr<2> {2, 2},        //
    arr<2> {3, 2},        //
    arr<2> {3, 3},        //
    arr<2> {3, eve::we_}, //
    arr<2> {eve::we_, 2}, //
    //---------------------
    arr<2> {0, 2}, //
    arr<2> {0, 3}, //
    arr<2> {1, 2}, //
    arr<2> {1, 3}, //
    arr<2> {2, 0}, //
    arr<2> {2, 1}, //
    arr<2> {3, 0}, //
    arr<2> {3, 1}, //
};


[[maybe_unused]] constexpr std::array kLen4x2_No0sBlendTests = {
    arr<4> {0, 1, 6, 3}, //
    arr<4> {0, 1, 2, 7}, //
    arr<4> {0, 1, 6, 7}, //
    // --------------------
    arr<4> {4, 1, 2, 3}, //
    arr<4> {4, 1, 6, 3}, //
    arr<4> {4, 1, 2, 7}, //
    arr<4> {4, 1, 6, 7}, //
    // --------------------
    arr<4> {0, 5, 2, 3}, //
    arr<4> {0, 5, 6, 3}, //
    arr<4> {0, 5, 2, 7}, //
    arr<4> {0, 5, 6, 7}, //
    // --------------------
    arr<4> {4, 5, 6, 3}, //
    arr<4> {4, 5, 2, 7}, //
};

// Not doing all
[[maybe_unused]] constexpr std::array kLen2x8x2_No0sBlendTests = {
    // -------------------------------
    arr<8> {8, 1, 2, 3, 4, 5, 6, 7},  //
    arr<8> {0, 9, 2, 3, 4, 5, 6, 7},  //
    arr<8> {0, 1, 2, 3, 12, 5, 6, 7}, //
    arr<8> {0, 1, 2, 3, 4, 5, 6, 15}, //
    // -------------------------------
    arr<8> {0, 9, 2, 11, 4, 13, 6, 15}, //
    arr<8> {8, 1, 2, 11, 12, 5, 6, 15}, //
};

}
