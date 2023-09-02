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
constexpr auto input = []
{
  std::array<eve::element_type_t<T>, T::size()> res = {};
  res.fill(eve::element_type_t<T> {0});

  if constexpr( eve::logical_value<T> )
  {
    for( int i = 0; auto& x : res ) { x = std::countl_zero((unsigned)i) & 1; }
  }
  else
  {
    for( int i = 0; auto& x : res ) { x = i; }
  }
  return res;
}();

template<typename T>
auto
compress_copy_expected(eve::as<T>                          tgt,
                       eve::logical_simd_value auto        m,
                       eve::relative_conditional_expr auto i0,
                       eve::relative_conditional_expr auto i1)
{
  std::array<eve::element_type_t<T>, T::size()> r;
  r.fill(eve::zero(eve::as<eve::element_type_t<T>> {}));

  auto *o = r.data();
  for( int i = i0.offset(tgt); i != i0.offset(tgt) + i0.count(tgt); ++i )
  {
    if( m.get(i) ) *o++ = input<T>[i];
  }

  for( int i = 0; i != i1.offset(tgt); ++i )
  {
    r[i] = eve::zero(eve::as<eve::element_type_t<T>> {});
  }

  for( int i = i1.offset(tgt) + i1.count(tgt); i != T::size(); ++i )
  {
    r[i] = eve::zero(eve::as<eve::element_type_t<T>> {});
  }

  return r;
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
  auto                                          expected = compress_copy_expected(tgt, m, i0, i1);
  std::array<eve::element_type_t<T>, T::size()> actual;
  actual.fill(eve::zero(eve::as<eve::element_type_t<T>> {}));

  auto check = [&]
  {
    if( !is_safe )
    {
      for( int i = i1.offset(tgt) + i1.count(tgt); i != T::size(); ++i )
      {
        actual[i] = eve::zero(eve::as<eve::element_type_t<T>> {});
      }
    }

    TTS_EQUAL(expected, actual) << "is_safe: " << is_safe << " m: " << m << " i0: " << i0
                                << " i1: " << i1;
  };

  algo[i0][i1](input<T>.data(), m, actual.data());
  check();

  T preloaded {input<T>.data()};

  actual.fill(eve::zero(eve::as<eve::element_type_t<T>> {}));
  algo[i0][i1](input<T>.data(), preloaded, m, actual.data());
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
  compress_copy_tst_all_versions(tgt, m, eve::ignore_none, eve::ignore_all, algo);
  compress_copy_tst_all_versions(tgt, m, eve::ignore_all, eve::ignore_none, algo);

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
  else
  {
    for( int i = 0; i <= T::size(); i += 9 )
    {
      for( int j = 0; j <= T::size() - i; j += 7 ) { for_ignore_tests(eve::ignore_extrema(i, j)); }
    }
  }
}

template<typename T, typename L>
void
compress_copy_tst_l_type(eve::as<T> tgt, eve::as<L>, auto algo)
{
  compress_copy_tst_mask(tgt, L {true}, algo);
  compress_copy_tst_mask(tgt, L {false}, algo);

  constexpr auto seed = sizeof(eve::element_type_t<L>) + sizeof(eve::element_type_t<T>) + T::size();
  std::mt19937   g(seed);
  std::uniform_int_distribution<short> d(0, 1);

  auto random_l = [&]() mutable
  {
    L m {false};
    for( int i = 0; i != L::size(); ++i ) { m.set(i, d(g) == 1); }
    return m;
  };

  for( int i = 0; i < 20; ++i ) compress_copy_tst_mask(tgt, random_l(), algo);
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
