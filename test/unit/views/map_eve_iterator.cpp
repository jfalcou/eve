#include "unit/algo/algo_test.hpp"
#include "unit/algo/iterator_concept_test.hpp"

#include <eve/views/map.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include <array>
#include <numeric>

struct load_op
{
  load_op() = delete;
  load_op(int) {}

  auto operator()(auto x) const
  {
    return eve::convert(x, eve::as<double>{}) * 2.0;
  }
};

struct store_op
{
  store_op() = delete;
  store_op(int) {}

  auto operator()(auto x, auto tgt) const
  {
    return eve::convert(x / 2.0, tgt);
  }
};

EVE_TEST_TYPES("Check ptr_iterator", algo_test::selected_types)
<typename T>(eve::as<T>)
{
  alignas(sizeof(T)) std::array<eve::element_type_t<T>, T::size()> data;
  std::iota(data.begin(), data.end(), 0);

  auto values = load_op{0}(T{[](int i, int) { return i; }});
  auto replace = [&](auto v, auto ignore) { return eve::replace_ignored(v, ignore, decltype(v){0}); };

  auto run_test_one_pair = [&](auto f_, auto l_) {
    auto map_r = eve::views::map_convert(eve::algo::as_range(f_, l_), load_op{0}, store_op{0});
    algo_test::iterator_sentinel_test(map_r.begin(), map_r.end(), values, replace);

    auto map_read_only = eve::views::map(eve::algo::as_range(f_, l_), load_op{0});
    algo_test::iterator_sentinel_test(map_read_only.begin(), map_read_only.end(), values, replace);
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
      auto map_a_f = eve::views::map_convert(a_f, load_op{0}, store_op{0});
      auto map_u_f = eve::views::map_convert(u_f, load_op{0}, store_op{0});

      algo_test::writeable_readable_iterator(map_a_f, values, replace);
      algo_test::writeable_readable_iterator(map_u_f, values, replace);
      algo_test::iterator_supports_compress(map_a_f, values, replace);
      algo_test::iterator_supports_compress(map_u_f, values, replace);
    }
  };

  run_test(data.begin(), data.end());
  run_test(data.cbegin(), data.cend());
};

TTS_CASE("eve.algo map iterator non const to const")
{
  using N = eve::fixed<4>;
  using aligned_p  = eve::aligned_ptr<int      , N>;
  using aligned_cp = eve::aligned_ptr<int const, N>;

  using u_it  = eve::views::map_iterator<eve::algo::ptr_iterator<int*      , N>, load_op, store_op>;
  using uc_it = eve::views::map_iterator<eve::algo::ptr_iterator<int const*, N>, load_op, store_op>;
  using a_it  = eve::views::map_iterator<eve::algo::ptr_iterator<aligned_p , N>, load_op, store_op>;
  using ac_it = eve::views::map_iterator<eve::algo::ptr_iterator<aligned_cp, N>, load_op, store_op>;

  TTS_CONSTEXPR_EXPECT( (std::convertible_to<u_it, uc_it>) );
  TTS_CONSTEXPR_EXPECT( (std::convertible_to<a_it, ac_it>) );
  TTS_CONSTEXPR_EXPECT( (std::convertible_to<a_it, u_it> ) );
  TTS_CONSTEXPR_EXPECT( (std::convertible_to<a_it, uc_it>) );
};
