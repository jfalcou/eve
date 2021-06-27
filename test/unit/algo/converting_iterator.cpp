//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/converting_iterator.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include "iterator_concept_test.hpp"

#include <array>
#include <numeric>

eve::detail::types<eve::wide<int>> constexpr small_types;

EVE_TEST_TYPES("Check converting_iterator", small_types)
<typename T>(eve::as_<T>)
{
  alignas(sizeof(T)) std::array<eve::element_type_t<T>, T::size()> data;
  std::iota(data.begin(), data.end(), 0);

  eve::wide<char,          eve::fixed<T::size()>> char_values ([](int i, int) { return i; });
  eve::wide<std::uint64_t, eve::fixed<T::size()>> int64_values([](int i, int) { return i; });
  auto replace = [&](auto v, auto ignore) { return eve::replace_ignored(v, ignore, decltype(v){0}); };

  auto run_test_one_pair = [&](auto f, auto l) {
    algo_test::iterator_sentinel_test(eve::algo::convert(f, eve::as_<char>{}),
                                      eve::algo::convert(l, eve::as_<char>{}),
                                      char_values, replace);
    algo_test::iterator_sentinel_test(eve::algo::convert(f, eve::as_<std::uint64_t>{}),
                                      eve::algo::convert(l, eve::as_<std::uint64_t>{}),
                                      int64_values, replace);
  };

  auto run_test_writeable = [&](auto f) {
    algo_test::writeable_readable_iterator(
      eve::algo::convert(f, eve::as_<char>{}), char_values, replace);
  };

  auto run_test = [&] <typename U>(U* f, U* l) {
    using N = eve::fixed<T::size()>;

    using aligned_it = eve::algo::aligned_ptr_iterator<U, N>;
    using aligned_p = typename aligned_it::aligned_ptr_type;

    eve::algo::unaligned_ptr_iterator<U, N> u_f(f);
    eve::algo::unaligned_ptr_iterator<U, N> u_l(l);
    eve::algo::aligned_ptr_iterator<U, N>   a_f(aligned_p{f});
    eve::algo::aligned_ptr_iterator<U, N>   a_l(aligned_p{l});

    run_test_one_pair(u_f, u_l);
    run_test_one_pair(u_f, a_l);
    run_test_one_pair(a_f, a_l);
    run_test_one_pair(a_f, u_l);

    if constexpr (!std::is_const_v<U>)
    {
      run_test_writeable(a_f);
      run_test_writeable(u_f);
    }
  };

  run_test(data.begin(), data.end());
  run_test(data.cbegin(), data.cend());
};
