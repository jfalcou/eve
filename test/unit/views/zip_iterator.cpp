//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"
#include "unit/algo/iterator_concept_test.hpp"

#include <eve/views/zip.hpp>

#include <eve/views/convert.hpp>
#include <eve/views/iota.hpp>

#include <eve/algo/ptr_iterator.hpp>

#include <algorithm>

TTS_CASE("zip_iterator for not eve iterators")
{
  std::vector<std::uint8_t> c {1, 2, 3, 4};
  std::vector<int> v{1, 2, 3};
  std::array<float, 4> f { 1, 2, 3, 4};
  using u_f = eve::algo::ptr_iterator<float*, eve::fixed<4>>;

  eve::views::zip_iterator zf{ c.begin(), v.begin(), u_f{f.begin()} };
  eve::views::zip_iterator zl{ c.end(), v.end(), u_f{f.end()} };

  kumi::tuple twos{std::uint8_t{2}, int{2}, float{2.0}};

  // comparisons

  TTS_LESS      (zf, zl);
  TTS_LESS_EQUAL(zf, zl);

  // std::fill won't work
  for (auto i = zf; i != zf; ++i) {
    eve::write(twos,i);
  }

  for (auto i = zf; i != zf; ++i) {
    TTS_EQUAL(eve::read(i), twos);
  }

  // ++/-- etc
  {
    auto i = zf;
    ++i;
    TTS_EQUAL((i - zf), 1);
    --i;
    TTS_EQUAL(i, zf);

    TTS_EQUAL(i++, zf);
    TTS_EQUAL((i - zf), 1);
    TTS_EQUAL((i-- - zf), 1);
    TTS_EQUAL(i, zf);
  }
};

TTS_CASE("zip_iterator for not eve iterators, unaligned")
{
  using a_p = eve::aligned_ptr<int>;
  using u_p = int*;

  using expected = eve::views::zip_iterator<u_p, u_p>;
  using actual   = eve::unaligned_t<eve::views::zip_iterator<a_p, u_p>>;
  TTS_TYPE_IS(expected, actual);
};

TTS_CASE("zip_iterator, sanity check, types test")
{
  using uf = float*;
  using af = eve::aligned_ptr<float, eve::fixed<8>>;
  using us = short*;
  using as = eve::aligned_ptr<short, eve::fixed<8>>;

  using unaligned_float = eve::algo::ptr_iterator<uf, eve::fixed<8>>;
  using aligned_float   = eve::algo::ptr_iterator<af, eve::fixed<8>>;
  using unaligned_short = eve::algo::ptr_iterator<us, eve::fixed<8>>;
  using aligned_short   = eve::algo::ptr_iterator<as, eve::fixed<8>>;

  using zip_a_a = eve::views::zip_iterator<aligned_float,   aligned_short>;
  using zip_u_a = eve::views::zip_iterator<unaligned_float, aligned_short>;
  using zip_a_u = eve::views::zip_iterator<aligned_float,   unaligned_short>;
  using zip_u_u = eve::views::zip_iterator<unaligned_float, unaligned_short>;

  using aligned_float_4   = eve::algo::ptr_iterator<eve::aligned_ptr<float, eve::fixed<4>>, eve::fixed<4>>;
  using unaligned_short_4 = eve::algo::ptr_iterator<short*, eve::fixed<4>>;

  using zip_a_u_4 = eve::views::zip_iterator<aligned_float_4, unaligned_short_4>;

  using wv_type = eve::wide<kumi::tuple<float, short>, eve::fixed<8>>;

  // CTAD
  eve::views::zip_iterator zi {unaligned_float{}, aligned_short{}};
  TTS_TYPE_IS(decltype(zi), zip_u_a);

  // Unaligned
  TTS_TYPE_IS(eve::unaligned_t<zip_a_a>, zip_u_u);
  TTS_TYPE_IS(eve::unaligned_t<zip_a_u>, zip_u_u);
  TTS_TYPE_IS(eve::unaligned_t<zip_u_a>, zip_u_u);
  TTS_TYPE_IS(eve::unaligned_t<zip_u_u>, zip_u_u);

  // Partially aligned
  TTS_TYPE_IS(eve::algo::partially_aligned_t<zip_a_a>, zip_a_a);
  TTS_TYPE_IS(eve::algo::partially_aligned_t<zip_a_u>, zip_a_u);
  TTS_TYPE_IS(eve::algo::partially_aligned_t<zip_u_a>, zip_u_a);
  TTS_TYPE_IS(eve::algo::partially_aligned_t<zip_u_u>, zip_a_u);

  // Cardinal cast
  TTS_TYPE_IS(decltype(zip_a_u{}.cardinal_cast(eve::lane<4>)), zip_a_u_4);

  // Equality
  TTS_TYPE_IS(decltype(zip_a_u{} == zip_a_u{}), bool);
  TTS_TYPE_IS(decltype(zip_a_u{} == zip_u_u{}), bool);
  TTS_TYPE_IS(decltype(zip_a_a{} != zip_u_a{}), bool);

  TTS_TYPE_IS(decltype(zip_a_u{} < zip_u_u{}), bool);
  TTS_TYPE_IS(decltype(zip_a_u{} - zip_u_u{}), std::ptrdiff_t);

  // Load
  TTS_TYPE_IS(decltype(eve::load(zip_a_u{})), wv_type);
  TTS_TYPE_IS(decltype(eve::load[eve::ignore_first(2)](zip_a_u{})), wv_type);
  TTS_TYPE_IS(decltype(eve::load[eve::ignore_first(2).else_(wv_type{})](zip_a_u{})), wv_type);

  // Store
  TTS_TYPE_IS(decltype(eve::store(wv_type{}, zip_a_u{})), void);
  TTS_TYPE_IS(decltype(eve::store[eve::ignore_first(2)](wv_type{}, zip_a_u{})), void);
  TTS_TYPE_IS(decltype(eve::store[eve::ignore_first(2).else_(wv_type{})](wv_type{}, zip_a_u{})), void);

  // Is readable iterator
  {
    eve::algo::readable_iterator auto u_u_test = zip_u_u{};
    (void) u_u_test;
    eve::algo::readable_iterator auto a_u_test = zip_a_u{};
    (void) a_u_test;
  }

  // sentinel for mismatching
  TTS_CONSTEXPR_EXPECT((eve::algo::sentinel_for<zip_a_u, zip_u_a>));
  TTS_CONSTEXPR_EXPECT((eve::algo::sentinel_for<zip_u_a, zip_a_u>));
};

TTS_CASE("zip_iterator, main iterator")
{
  using uf = float*;
  using af = eve::aligned_ptr<float, eve::fixed<8>>;
  using us = short*;
  using as = eve::aligned_ptr<short, eve::fixed<8>>;

  using unaligned_float = eve::algo::ptr_iterator<uf, eve::fixed<8>>;
  using aligned_float   = eve::algo::ptr_iterator<af, eve::fixed<8>>;
  using unaligned_short = eve::algo::ptr_iterator<us, eve::fixed<8>>;
  using aligned_short   = eve::algo::ptr_iterator<as, eve::fixed<8>>;

  using iota            = decltype(eve::views::iota(0).cardinal_cast(eve::lane<8>));

  using zip_a_a = eve::views::zip_iterator<aligned_float,   aligned_short>;
  TTS_CONSTEXPR_EQUAL(zip_a_a::main_iterator_idx, 0u);

  using zip_u_a = eve::views::zip_iterator<unaligned_float, aligned_short>;
  TTS_CONSTEXPR_EQUAL(zip_u_a::main_iterator_idx, 1u);

  using zip_a_u = eve::views::zip_iterator<aligned_float,   unaligned_short>;
  TTS_CONSTEXPR_EQUAL(zip_a_u::main_iterator_idx, 0u);

  using zip_u_u = eve::views::zip_iterator<unaligned_float, unaligned_short>;
  TTS_CONSTEXPR_EQUAL(zip_u_u::main_iterator_idx, 0u);

  using zip_u_i = eve::views::zip_iterator<unaligned_float, iota>;
  TTS_CONSTEXPR_EQUAL(zip_u_i::main_iterator_idx, 0u);

  using zip_i_u = eve::views::zip_iterator<iota, unaligned_float>;
  TTS_CONSTEXPR_EQUAL(zip_i_u::main_iterator_idx, 1u);

  using zip_i_a = eve::views::zip_iterator<iota, aligned_float>;
  TTS_CONSTEXPR_EQUAL(zip_i_a::main_iterator_idx, 1u);

  TTS_TYPE_IS(eve::algo::partially_aligned_t<zip_i_u>, zip_i_a);

  using zip_i_i = eve::views::zip_iterator<iota, iota>;
  TTS_CONSTEXPR_EQUAL(zip_i_i::main_iterator_idx, 0u);
};

TTS_CASE_TPL("Check zip_iterator", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  using t1 = std::int8_t;
  using t2 = eve::element_type_t<T>;
  using t3 = std::uint64_t;
  using N  = eve::fixed<T::size()>;

  using tuple_t = kumi::tuple<t1, t2, t3>;

  alignas(sizeof(t1) * N{}()) std::array<t1, N{}()> data_1;
  alignas(sizeof(t2) * N{}()) std::array<t2, N{}()> data_2;
  alignas(sizeof(t3) * N{}()) std::array<t3, N{}()> data_3;

  std::iota(data_1.begin(), data_1.end(), 0);
  std::iota(data_2.begin(), data_2.end(), 0);
  std::iota(data_3.begin(), data_3.end(), 0);

  eve::wide<tuple_t, N> values { [](int i, int) { return tuple_t{(t1)i, (t2)i, (t3)i}; }};
  eve::wide<tuple_t, N> zeroes { tuple_t{t1{}, t2{}, t3{}} };

  auto replace = [&](auto v, auto ignore) { return eve::replace_ignored(v, ignore, zeroes); };

  auto run_test_one_pair = [&](auto f1, auto f2, auto f3, auto l1) {
    eve::views::zip_iterator f {f1, f2, f3};
    eve::views::zip_iterator l = f + (l1 - f1);
    algo_test::iterator_sentinel_test(f, l, values, replace);
    algo_test::writeable_readable_iterator(f, values, replace);
    algo_test::iterator_supports_compress(f, values, replace);
  };

  eve::algo::ptr_iterator<t1*, N> u_f_1{data_1.begin()};
  eve::algo::ptr_iterator<t2*, N> u_f_2{data_2.begin()};
  eve::algo::ptr_iterator<t3*, N> u_f_3{data_3.begin()};

  auto u_l_1 = u_f_1 + T::size();

  auto a_f_1 = u_f_1.previous_partially_aligned();
  auto a_f_2 = u_f_2.previous_partially_aligned();
  auto a_f_3 = u_f_3.previous_partially_aligned();

  run_test_one_pair(u_f_1, u_f_2, u_f_3, u_l_1);
  run_test_one_pair(a_f_1, a_f_2, a_f_3, u_l_1);
  run_test_one_pair(u_f_1, a_f_2, u_f_3, u_l_1);
};

TTS_CASE("zip iterators const/non-const")
{
  using cvt       = eve::views::converting_iterator<std::int8_t*      , int>;
  using cvt_const = eve::views::converting_iterator<std::int8_t const*, int>;

  using from      = eve::views::zip_iterator<int*      , cvt>;
  using to        = eve::views::zip_iterator<int const*, cvt_const>;

  TTS_CONSTEXPR_EXPECT( (std::convertible_to<from, to>) );
};
