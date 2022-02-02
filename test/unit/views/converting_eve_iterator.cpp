#include "unit/algo/algo_test.hpp"
#include "unit/algo/iterator_concept_test.hpp"

#include <eve/views/convert.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include <array>
#include <numeric>

EVE_TEST_TYPES("Check converting_iterator", algo_test::selected_types)
<typename T>(eve::as<T>)
{
  alignas(sizeof(T)) std::array<eve::element_type_t<T>, T::size()> data;
  std::iota(data.begin(), data.end(), 0);

  eve::wide<char,          eve::fixed<T::size()>> char_values ([](int i, int) { return i; });
  eve::wide<std::uint64_t, eve::fixed<T::size()>> int64_values([](int i, int) { return i; });
  auto replace = [&](auto v, auto ignore) { return eve::replace_ignored(v, ignore, decltype(v){0}); };

  auto run_test_one_pair = [&](auto f, auto l) {
    algo_test::iterator_sentinel_test(eve::views::convert(f, eve::as<char>{}),
                                      eve::views::convert(l, eve::as<char>{}),
                                      char_values, replace);
    algo_test::iterator_sentinel_test(eve::views::convert(f, eve::as<std::uint64_t>{}),
                                      eve::views::convert(l, eve::as<std::uint64_t>{}),
                                      int64_values, replace);
  };

  auto run_test_writeable = [&](auto f) {
    algo_test::writeable_readable_iterator(
      eve::views::convert(f, eve::as<char>{}), char_values, replace);
    algo_test::iterator_supports_compress(
      eve::views::convert(f, eve::as<char>{}), char_values, replace);
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
      run_test_writeable(a_f);
      run_test_writeable(u_f);
    }
  };

  run_test(data.begin(), data.end());
  run_test(data.cbegin(), data.cend());
};
