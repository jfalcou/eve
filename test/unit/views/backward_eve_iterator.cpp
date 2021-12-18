//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"
#include "unit/algo/iterator_concept_test.hpp"

#include <eve/views/backward.hpp>

#include <eve/algo/ptr_iterator.hpp>

#include <array>
#include <numeric>

namespace algo_test {

template <eve::algo::relaxed_iterator I>
struct read_to_load_match<eve::views::backward_iterator<I>>
{
  static constexpr std::ptrdiff_t value = eve::algo::iterator_cardinal_v<I> - 1;
};

}

EVE_TEST_TYPES("Check backward_iterator", algo_test::selected_types)
<typename T>(eve::as<T>)
{
  alignas(sizeof(T)) std::array<eve::element_type_t<T>, T::size()> data;
  std::iota(data.begin(), data.end(), 0);

  T values([](int i, int) { return i; });
  auto replace = [&](auto v, auto ignore) {
    return eve::replace_ignored(v,
                                eve::reverse_conditional(ignore, eve::as(v)),
                                T{0});
  };

  auto run_test_one_pair = [&](auto f, auto l) {
    auto back = eve::views::backward(eve::algo::as_range(f, l));
    algo_test::iterator_sentinel_test(back.begin(), back.end(), values, replace);
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
      algo_test::writeable_readable_iterator(eve::views::backward(a_l), values, replace);
      algo_test::writeable_readable_iterator(eve::views::backward(u_l), values, replace);
    }
  };

  run_test(data.begin(), data.end());
  run_test(data.cbegin(), data.cend());
};
