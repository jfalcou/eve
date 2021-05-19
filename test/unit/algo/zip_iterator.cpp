//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/zip_iterator.hpp>

#include "iterator_concept_test.hpp"

#include <eve/algo/ptr_iterator.hpp>

#include <eve/function/replace.hpp>

#include <array>

EVE_TEST_TYPES("Check zip_iterator", algo_test::selected_types)
<typename T>(eve::as_<T>)
{
  using N = eve::fixed<T::static_size>;

  alignas(sizeof(T)) std::array<eve::element_type_t<T>, T::static_size> a;
  std::iota(a.begin(), a.end(), 0);
  std::array<short, T::static_size> b;

  auto run_test = [&]<typename U, typename K, typename L>
  (U* uf, U* ul, K* kf, L* lf) {
    using aligned_it = eve::algo::aligned_ptr_iterator<U, N>;
    using aligned_p  = typename aligned_it::aligned_ptr_type;
    using unaligned_it_k = eve::algo::unaligned_ptr_iterator<K, N>;
    using unaligned_it_l = eve::algo::unaligned_ptr_iterator<L, N>;

    kumi::tuple values{
      typename aligned_it::wide_value_type([](int i, int) { return i; }),
      typename unaligned_it_k::wide_value_type([](int i, int) { return i; }),
      typename unaligned_it_l::wide_value_type([](int i, int) { return i; })
    };

    auto replace = [&](auto v, auto ignore) {
      return kumi::map([&](auto x) { return eve::replace_ignored(x, ignore, 0); }, v);
    };

    eve::algo::zip_iterator f(
      aligned_it{aligned_p{uf}},
      unaligned_it_k{kf},
      unaligned_it_l{lf}
    );

    eve::algo::zip_iterator l(
      aligned_it{aligned_p{ul}},
      unaligned_it_k{kf + (ul - uf)},
      unaligned_it_l{lf + (ul - uf)}
    );

    // (void)f;
    // (void)l;
    // (void)values;
    // (void)replace;

    algo_test::iterator_sentinel_test(f, l, values, replace);
  };

  run_test(a.begin(), a.end(), b.begin(), a.begin());
};
