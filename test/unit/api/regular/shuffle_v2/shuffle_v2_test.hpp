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

template<typename T, typename U, std::ptrdiff_t G, std::ptrdiff_t... I>
void
verify(T x, eve::fixed<G>, eve::pattern_t<I...> p, U shuffled)
{
  using e_t = eve::element_type_t<T>;
  std::array<e_t, (std::size_t)T::size()> x_a;
  eve::store(x, x_a.data());

  std::array<e_t, (std::size_t)U::size()> shuffled_a;
  eve::store(shuffled, shuffled_a.data());

  bool has_failures = [&]
  {
    if( G * sizeof...(I) != U::size() ) return true;

    int out_i = 0;
    for( auto group_i : {I...} )
    {
      for( int within_i = 0; within_i != G; ++within_i )
      {
        eve::element_type_t<T> actual = shuffled_a[out_i++];
        eve::element_type_t<T> expected;

        if( group_i == eve::na_ ) expected = 0;
        else if( group_i == eve::we_ ) continue;
        else expected = x_a[group_i * G + within_i];

        if( expected != actual ) { return true; }
      }
    }
    return false;
  }();

  TTS_EXPECT(!has_failures) << "sizeof(T): " << sizeof(T) << " G: " << G << "\npattern: " << p
                            << "\nactual:  " << shuffled;
}

template<typename T, std::ptrdiff_t... I>
void
run_one_case(std::ptrdiff_t expected_level, T input, auto g, eve::pattern_t<I...> p)
{
  using e_t = eve::element_type_t<T>;
  if constexpr( requires { eve::shuffle_v2_core(input, g, p); } )
  {
    auto [shuffled, l] = eve::shuffle_v2_core(input, g, p);
    verify(input, g, p, shuffled);

    std::array idxs {I...};

    if( g() >= T::size() || g() >= eve::expected_cardinal_v<e_t> || idxs.size() == 1 )
    {
      expected_level = eve::detail::idxm::has_zeroes(idxs);
    }
    if( eve::has_emulated_abi_v<T> ) expected_level = 0;
    TTS_EQUAL(expected_level, l())
        << "G: " << g() << "\npattern: " << p << "\nT type: " << tts::typename_<T>;
  }
  else { TTS_FAIL("Failed to shuffle, G: " << g() << "\npattern: " << p); }
}

template<typename T, std::ptrdiff_t... I>
void
run2_one_case(std::ptrdiff_t expected_level, T x, T y, auto g, eve::pattern_t<I...> p)
{
  using e_t = eve::element_type_t<T>;
  if constexpr( requires { eve::shuffle_v2_core(x, y, g, p); } )
  {
    auto [shuffled, l] = eve::shuffle_v2_core(x, y, g, p);
    verify(eve::combine(x, y), g, p, shuffled);

    std::array idxs {I...};

    if( g() >= T::size() || g() >= eve::expected_cardinal_v<e_t> || idxs.size() == 1 )
    {
      expected_level = eve::detail::idxm::has_zeroes(idxs);
    }
    if( eve::has_emulated_abi_v<T> ) expected_level = 0;
    TTS_EQUAL(expected_level, l()) << "G: " << g() << "\npattern: " << p;
  }
  else { TTS_FAIL("Failed to shuffle, G: " << g() << "\npattern: " << p); }
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G, std::ptrdiff_t... I>
void
run(auto expected_level, eve::pattern_t<I...> p = {})
{
  using Wide = eve::wide<T, eve::fixed<N>>;

  Wide input {[](int i, int) { return i + 1; }};
  run_one_case(expected_level(std::array {I...}), input, eve::lane<G>, p);
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G, std::ptrdiff_t... I>
void
run2(auto expected_level, eve::pattern_t<I...> p = {})
{
  using Wide = eve::wide<T, eve::fixed<N * 2>>;

  Wide input {[](int i, int) { return i + 1; }};
  auto xy = input.slice();
  auto x  = get<0>(xy);
  auto y  = get<1>(xy);
  run2_one_case(expected_level(std::array {I...}), x, y, eve::lane<G>, p);
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

template<int i, typename T, std::ptrdiff_t N, std::ptrdiff_t G>
void
run_all_4_element_test(auto expected_l)
{
  constexpr int i0 = (i / 1 % 6) - 2;
  constexpr int i1 = (i / 6 % 6) - 2;
  constexpr int i2 = (i / 36 % 6) - 2;
  constexpr int i3 = (i / 216 % 6) - 2;
  run<T, N, G, i0, i1, i2, i3>(expected_l);
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G>
void
run_all_4_element_tests(auto expected_l)
{
  auto r =
      [&]<std::ptrdiff_t start, std::size_t... i>(eve::index_t<start>, std::index_sequence<i...>)
  { (run_all_4_element_test<start + (int)i, T, N, G>(expected_l), ...); };

  // total cases 6^4.
  // limit of 256 per expansion
  constexpr int step = 6 * 6 * 6 * 6 / 8;

  r(eve::index<step * 0>, std::make_index_sequence<step> {});
  r(eve::index<step * 1>, std::make_index_sequence<step> {});
  r(eve::index<step * 2>, std::make_index_sequence<step> {});
  r(eve::index<step * 3>, std::make_index_sequence<step> {});
  r(eve::index<step * 4>, std::make_index_sequence<step> {});
  r(eve::index<step * 5>, std::make_index_sequence<step> {});
  r(eve::index<step * 6>, std::make_index_sequence<step> {});
  r(eve::index<step * 7>, std::make_index_sequence<step> {});
}

template<typename T>
void
for_each_group_size(eve::as<T>, auto op)
{
  constexpr auto ssz = std::bit_width(std::size_t(T::size()));
  [&]<std::size_t... I>(std::index_sequence<I...>)
  { (op(eve::lane<1 << (int)I>), ...); }(std::make_index_sequence<ssz> {});
}

template<typename T>
void
for_each_group_with_params(eve::as<T> tgt, auto op)
{
  for_each_group_size(tgt, op);
}

template<typename T>
void
for_each_group_with_params(eve::as<T> tgt, auto extra_param_gen, auto op)
{
  for_each_group_size(tgt,
                      [&](auto g)
                      {
                        kumi::for_each(
                            [&](auto extra)
                            {
                              auto params = kumi::cat(kumi::tuple {g}, extra);
                              kumi::apply(op, params);
                            },
                            extra_param_gen(g));
                      });
}

template<bool supports_G_eq_T_Size, typename T, typename NamedShuffle>
void
named_shuffle1_test_one_input(T input, NamedShuffle named_shuffle, auto... extra_args_gen)
{
  auto tgt = eve::as<T> {};
  for_each_group_with_params(tgt,
                             extra_args_gen...,
                             [&]<std::ptrdiff_t G>(eve::fixed<G> g, auto... extra)
                             {
                               if constexpr( G != T::size() || supports_G_eq_T_Size )
                               {
                                 std::ptrdiff_t expected_level =
                                     named_shuffle.level(tgt, g, extra...);
                                 auto pattern = named_shuffle.pattern(tgt, g, extra...);
                                 run_one_case(expected_level, input, g, pattern);
                               }
                             });
}

template<bool supports_G_eq_T_Size, typename T, typename NamedShuffle>
void
named_shuffle2_test_one_input(T x, T y, NamedShuffle named_shuffle, auto extra_param_gen)
{
  auto tgt = eve::as<T> {};
  for_each_group_with_params(tgt,
                             extra_param_gen,
                             [&]<std::ptrdiff_t G>(eve::fixed<G> g, auto... extra)
                             {
                               if constexpr( G != T::size() || supports_G_eq_T_Size )
                               {
                                 std::ptrdiff_t expected_level =
                                     named_shuffle.level(tgt, tgt, g, extra...);
                                 auto pattern = named_shuffle.pattern(tgt, tgt, g, extra...);
                                 run2_one_case(expected_level, x, y, g, pattern);
                               }
                             });
}

template<bool supports_G_eq_T_Size, typename T, typename NamedShuffle>
void
named_shuffle1_test(eve::as<T>, NamedShuffle named_shuffle, auto... extra_args_gen)
{
  if( T::size() == 1 && !supports_G_eq_T_Size )
  {
    TTS_PASS();
    return;
  }

  T x {[](int i, int) { return i + 1; }};
  named_shuffle1_test_one_input<supports_G_eq_T_Size>(x, named_shuffle, extra_args_gen...);

  // false, true, false, false, true, true
  eve::logical<T> mask {[](int i, int) { return std::countl_zero((unsigned)i) & 1; }};
  named_shuffle1_test_one_input<supports_G_eq_T_Size>(mask, named_shuffle, extra_args_gen...);
}

template<bool supports_G_eq_T_Size, typename T, typename N, typename NamedShuffle>
void
named_shuffle2_test(eve::as<eve::wide<T, N>>, NamedShuffle named_shuffle, auto extra_args_gen)
{
  if( N::value == 1 && !supports_G_eq_T_Size )
  {
    TTS_PASS();
    return;
  }

  using wide2 = eve::wide<T, eve::fixed<N::value * 2>>;

  {
    wide2 xy {[](int i, int) { return i + 1; }};

    auto [x, y] = xy.slice();
    named_shuffle2_test_one_input<supports_G_eq_T_Size>(x, y, named_shuffle, extra_args_gen);
  }

  {
    eve::logical<wide2> xy {[](int i, int) { return std::countl_zero((unsigned)i) & 1; }};

    auto [x, y] = xy.slice();
    named_shuffle2_test_one_input<supports_G_eq_T_Size>(x, y, named_shuffle, extra_args_gen);
  }
}

#if !defined(EVE_NO_SIMD)
template<int l, typename T, std::ptrdiff_t N, std::ptrdiff_t G, std::ptrdiff_t... I>
void
debug_call_shuffle_l_directly()
{
  using w_t = eve::as_wide_t<T, eve::fixed<N>>;

  auto p = eve::detail::expanded_pattern<w_t, G, I...>;
  auto g = eve::lane<G>;

  w_t x {[](int i, int) { return i + 1; }};

// disabled since no shuffle_l2 for now and breaks compilation
#  if !defined(EVE_INCLUDE_ARM_SVE_HEADER) && !defined(EVE_INCLUDE_POWERPC_HEADER)
  if constexpr( l == 2 )
  {
    eve::detail::shuffle_l2_(eve::detail::delay_t {}, eve::current_api, p, g, x);
  }
  else
#  endif
      if constexpr( l == 99 )
  {
    eve::detail::shuffle_l_fallback_(eve::detail::delay_t {}, eve::current_api, p, g, x);
  }
  else { std::cout << __func__ << " you need to add l: " << l << std::endl; }
}
#endif

}
