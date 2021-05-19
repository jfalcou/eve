//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/ptr_iterator.hpp>

#include "iterator_concept_test.hpp"

#include <array>
#include <numeric>

namespace
{

struct basic_delegate
{
  auto replace(auto v, auto ignore) { return eve::replace_ignored(v, ignore, 0); }

  void assert_eq(auto x, auto y) { TTS_EQUAL(x, y); }
};

}

EVE_TEST_TYPES("Check ptr_iterator", algo_test::selected_types)
<typename T>(eve::as_<T>)
{
  alignas(sizeof(T)) std::array<eve::element_type_t<T>, T::static_size> data;
  std::iota(data.begin(), data.end(), 0);

  struct delegate_t : basic_delegate
  {
    T v() { return T([](int i, int) { return i; }); }
  } delegate;

  auto run_test_one_pair = [&](auto f, auto l) {
    algo_test::iterator_sentinel_test(f, l, delegate);
  };

  auto run_test = [&] <typename U>(U* f, U* l) {
    using N = eve::fixed<T::static_size>;

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
      algo_test::writeable_readable_iterator(a_f, delegate);
      algo_test::writeable_readable_iterator(u_f, delegate);
    }
  };

  run_test(data.begin(), data.end());
  run_test(data.cbegin(), data.cend());
};
