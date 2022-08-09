//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/ptr_iterator.hpp>

#include "iterator_concept_test.hpp"

#include <array>
#include <numeric>

TTS_CASE_TPL("Check ptr_iterator", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  alignas(sizeof(T)) std::array<eve::element_type_t<T>, T::size()> data;
  std::iota(data.begin(), data.end(), 0);

  T values([](int i, int) { return i; });
  auto replace = [&](auto v, auto ignore) { return eve::replace_ignored(v, ignore, T{0}); };


  auto run_test_one_pair = [&](auto f, auto l) {
    algo_test::iterator_sentinel_test(f, l, values, replace);
  };

  auto run_test = [&] <typename U>(U* f, U* l) {
    using N = eve::fixed<T::size()>;
    using aligned_p = eve::aligned_ptr<U, N>;

    using u_it = eve::algo::ptr_iterator<U*, N>;
    using a_it = eve::algo::ptr_iterator<aligned_p, N>;

    u_it u_f(f);
    u_it u_l(l);
    a_it a_f(aligned_p{f});
    a_it a_l(aligned_p{l});

    run_test_one_pair(u_f, u_l);
    run_test_one_pair(u_f, a_l);
    run_test_one_pair(a_f, a_l);
    run_test_one_pair(a_f, u_l);

    if constexpr (!std::is_const_v<U>)
    {
      algo_test::writeable_readable_iterator(a_f, values, replace);
      algo_test::writeable_readable_iterator(u_f, values, replace);
      algo_test::iterator_supports_compress(a_f, values, replace);
      algo_test::iterator_supports_compress(u_f, values, replace);
    }
  };

  run_test(data.begin(), data.end());
  run_test(data.cbegin(), data.cend());
};


TTS_CASE("eve.algo non const to const")
{
  using N = eve::fixed<4>;
  using aligned_p  = eve::aligned_ptr<int, N>;
  using aligned_cp = eve::aligned_ptr<int const, N>;

  using u_it  = eve::algo::ptr_iterator <int*      , N>;
  using uc_it = eve::algo::ptr_iterator<int const*, N>;
  using a_it  = eve::algo::ptr_iterator<aligned_p, N>;
  using ac_it = eve::algo::ptr_iterator<aligned_cp, N>;

  TTS_CONSTEXPR_EXPECT( (std::convertible_to<u_it, uc_it>) );
  TTS_CONSTEXPR_EXPECT( (std::convertible_to<a_it, ac_it>) );
};
