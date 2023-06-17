//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <numeric>

namespace shuffle_test
{

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
    if (G * sizeof...(I) != U::value) return true;

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

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G, std::ptrdiff_t... I>
void
run(auto shuffle, eve::pattern_t<I...> = {})
{
  using Wide = eve::wide<T, eve::fixed<N>>;

  if constexpr( eve::current_api < api )
  {
    TTS_PASS();
    return;
  }
  else
  {
    Wide input {[](int i, int) { return i + 1; }};
    Wide actual = shuffle(input, eve::lane<G>, eve::pattern<I...>);
    verify(input, eve::lane<G>, eve::pattern<I...>, actual);
  }
}

template<auto arr>
auto
pattern_from_array()
{
  return []<std::size_t... i>(std::index_sequence<i...>)
  { return eve::pattern<arr[i]...>; }(std::make_index_sequence<arr.size()> {});
}

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G, auto tests>
void
run_all(auto shuffle)
{
  [&]<std::size_t... i>(std::index_sequence<i...>) {
    (run<api, T, N, G>(shuffle, pattern_from_array<tests[i]>()), ...);
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
[[maybe_unused]]

constexpr std::array kLen4No0Tests_Scrambled = {
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

}
