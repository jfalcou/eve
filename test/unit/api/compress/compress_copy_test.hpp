//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "test.hpp"

template<typename T>
T
input(eve::as<T>)
{
  if constexpr( eve::logical_value<T> )
  {
    return T {[](int i, int) { return bool(std::countl_zero((unsigned)i) & 1); }};
  }
  else if constexpr( eve::has_bundle_abi_v<T> )
  {
    return T {[](int i, int)
              {
                using m1 = std::tuple_element_t<1, eve::element_type_t<T>>;
                return eve::element_type_t<T> {
                    static_cast<std::int8_t>(i + 1),
                    static_cast<m1>(i + 2),
                    static_cast<double>(i + 3),
                };
              }};
  }
  else
  {
    return T {[](int i, int) { return i; }};
  }
}

template<typename T>
kumi::tuple<T, int>
compress_copy_expected(eve::as<T>                          tgt,
                       eve::logical_simd_value auto        m,
                       eve::relative_conditional_expr auto i0,
                       eve::relative_conditional_expr auto i1)
{
  auto in = input(tgt);
  auto r  = eve::zero(tgt);

  int o     = i1.offset(tgt);
  int limit = o + i1.count(tgt);
  for( int i = i0.offset(tgt); i != i0.offset(tgt) + i0.count(tgt); ++i )
  {
    if( m.get(i) )
    {
      if( o == limit ) break;
      r.set(o++, in.get(i));
    }
  }

  return {eve::replace_ignored(r, i1, eve::zero(eve::as(tgt))), o};
}

template<typename T>
void
compress_copy_tst_one_case(bool                                is_safe,
                           eve::as<T>                          tgt,
                           eve::logical_simd_value auto        m,
                           eve::relative_conditional_expr auto i0,
                           eve::relative_conditional_expr auto i1,
                           auto                                algo)
{
  auto expected_expected_offset = compress_copy_expected(tgt, m, i0, i1);
  auto expected                 = get<0>(expected_expected_offset);
  auto expected_offset          = get<1>(expected_expected_offset);

  eve::stack_buffer<T> actual_storage;
  eve::store(eve::zero(tgt), actual_storage.ptr());

  auto res = eve::unalign(actual_storage.ptr());

  auto check = [&]
  {
    if( !is_safe )
    {
      auto last_ok = eve::unalign(actual_storage.ptr()) + i1.offset(tgt) + i1.count(tgt);
      auto z       = eve::zero(eve::as<eve::element_type_t<T>> {});
      for( auto f = res; f != last_ok; ++f ) { eve::write(z, f); }
    }

    auto actual = eve::load(actual_storage.ptr(), tgt);

#if 0
    TTS_EQUAL(expected, actual) << "is_safe: " << is_safe << " m: " << m << " i0: " << i0
                                << " i1: " << i1;
    TTS_EQUAL(expected_offset, res - actual_storage.ptr())
        << "is_safe: " << is_safe << " m: " << m << " i0: " << i0 << " i1: " << i1;
#endif
    TTS_EXPECT(eve::all(expected == actual), REQUIRED);
    TTS_EXPECT(expected_offset == (res - actual_storage.ptr()), REQUIRED);
  };

  eve::stack_buffer<T> in;
  eve::store(input(tgt), in.ptr());

  res = algo[i0][i1](in.ptr(), m, actual_storage.ptr());
  check();

  T preloaded {in.ptr()};

  eve::store(eve::zero(tgt), actual_storage.ptr());
  res = algo[i0][i1](in.ptr(), preloaded, m, actual_storage.ptr());
  check();
}

template<typename T>
void
compress_copy_tst_all_versions(eve::as<T>                          tgt,
                               eve::logical_simd_value auto        m,
                               eve::relative_conditional_expr auto i0,
                               eve::relative_conditional_expr auto i1,
                               auto                                algo)
{
  compress_copy_tst_one_case(false, tgt, m, i0, i1, algo[eve::unsafe][eve::dense]);
  compress_copy_tst_one_case(false, tgt, m, i0, i1, algo[eve::unsafe][eve::sparse]);
  compress_copy_tst_one_case(true, tgt, m, i0, i1, algo[eve::safe][eve::dense]);
  compress_copy_tst_one_case(true, tgt, m, i0, i1, algo[eve::safe][eve::sparse]);
}

template<typename T, typename L>
void
compress_copy_tst_mask(eve::as<T> tgt, L m, auto algo)
{
  compress_copy_tst_all_versions(tgt, m, eve::ignore_none, eve::ignore_none, algo);

  if constexpr( std::same_as<typename L::mask_type, T> )
  {
    compress_copy_tst_all_versions(tgt, m, eve::ignore_none, eve::ignore_all, algo);
    compress_copy_tst_all_versions(tgt, m, eve::ignore_all, eve::ignore_none, algo);
  }

  auto for_ignore_tests = [&](auto ignore)
  {
    compress_copy_tst_all_versions(tgt, m, ignore, eve::ignore_none, algo);
    compress_copy_tst_all_versions(tgt, m, eve::ignore_none, ignore, algo);
    compress_copy_tst_all_versions(tgt, m, ignore, ignore, algo);
  };

  if( T::size() < 16 )
  {
    for( int i = 0; i != T::size(); ++i )
    {
      for( int j = 0; j != T::size() - i; ++j ) { for_ignore_tests(eve::ignore_extrema(i, j)); }
    }
  }
  else if constexpr( eve::has_bundle_abi_v<T> && eve::current_api >= eve::sve )
  {
    for_ignore_tests(eve::ignore_extrema(0, 0));
    for_ignore_tests(eve::ignore_extrema(5, 1));
    for_ignore_tests(eve::ignore_extrema(0, 9));
    for_ignore_tests(eve::ignore_extrema(4, 4));
    for_ignore_tests(eve::ignore_extrema(7, 9));
  }
  else
  {
    for( int i = 0; i <= T::size(); i += 9 )
    {
      for( int j = 0; j <= T::size() - i; j += 7 ) { for_ignore_tests(eve::ignore_extrema(i, j)); }
    }
  }
}

template<typename L>
const auto&
test_masks(eve::as<L>)
{
  static const auto r = []
  {
    static constexpr std::size_t N = (eve::current_api == eve::sve512) ? 10 : 40;

    std::array<L, N> res;
    res[0] = L {true};
    res[1] = L {false};

    constexpr auto seed =
        sizeof(eve::element_type_t<L>) + sizeof(eve::element_type_t<L>) + L::size();
    std::mt19937                         g(seed);
    std::uniform_int_distribution<short> d(0, 1);

    for( int i = 2; i < (int)N; ++i )
    {
      L m {false};
      for( int i = 0; i != L::size(); ++i ) { m.set(i, d(g) == 1); }
      res[i] = m;
    }

    return res;
  }();
  return r;
}

template<typename T, typename L>
void
compress_copy_tst_l_type(eve::as<T> tgt, eve::as<L> ltgt, auto algo)
{
  for( L m : test_masks(ltgt) ) { compress_copy_tst_mask(tgt, m, algo); }
}

template<typename T>
void
compress_copy_tst(eve::as<T> tgt, auto algo)
{
  using N = typename T::cardinal_type;

  if constexpr( eve::has_bundle_abi_v<T> )
  {
    using e_t = std::tuple_element_t<1, eve::element_type_t<T>>;
    using l_t = eve::logical<eve::wide<e_t, N>>;

    compress_copy_tst_l_type(tgt, eve::as<l_t> {}, algo);
  }
  else if constexpr( eve::logical_simd_value<T> )
  {
    compress_copy_tst_l_type(eve::as<T> {}, eve::as<T> {}, eve::compress_copy);

    // is just impossibly slow
    if constexpr( eve::current_api != eve::sve512 )
    {
      compress_copy_tst_l_type(
          eve::as<T> {}, eve::as<eve::logical<eve::wide<std::uint8_t, N>>> {}, eve::compress_copy);
    }
  }
  else
  {
    using e_t = eve::element_type_t<T>;

    compress_copy_tst_l_type(eve::as<T> {}, eve::as<eve::logical<T>> {}, eve::compress_copy);
    if constexpr( !std::same_as<e_t, std::uint8_t> )
    {
      compress_copy_tst_l_type(
          eve::as<T> {}, eve::as<eve::logical<eve::wide<std::uint8_t, N>>> {}, eve::compress_copy);
    }

    // is just impossibly slow
    if constexpr( eve::current_api != eve::sve512 )
    {
      if constexpr( !std::same_as<e_t, std::uint16_t> )
      {
        compress_copy_tst_l_type(eve::as<T> {},
                                 eve::as<eve::logical<eve::wide<std::uint16_t, N>>> {},
                                 eve::compress_copy);
      }
      if constexpr( !std::same_as<e_t, std::uint32_t> )
      {
        compress_copy_tst_l_type(eve::as<T> {},
                                 eve::as<eve::logical<eve::wide<std::uint32_t, N>>> {},
                                 eve::compress_copy);
      }

      if constexpr( !std::same_as<e_t, std::uint64_t> )
      {
        compress_copy_tst_l_type(eve::as<T> {},
                                 eve::as<eve::logical<eve::wide<std::uint64_t, N>>> {},
                                 eve::compress_copy);
      }
    }
  }
}
