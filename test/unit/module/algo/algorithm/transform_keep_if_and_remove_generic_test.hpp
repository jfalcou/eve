//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

// g++ 11 regression fires __builtin_memmove spurious warnings
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=100516

#include "eve/module/core/regular/is_not_equal.hpp"
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wstringop-overread"
#endif

#include <eve/module/algo.hpp>
#include <eve/memory/aligned_allocator.hpp>

#include <iterator>
#include <vector>

template <typename T, typename Algo, typename Op>
void transform_keep_if_generic_test_aligned_ptr(eve::as<T>, Algo alg, Op op)
{
  using e_t = eve::element_type_t<T>;
  alignas(128) std::array<e_t, 23> data;
  const e_t keep{5};
  const e_t drop{1};

  for (std::size_t i = 0; i != data.size(); ++i)
  {
    data[i] = (i % 3) ? keep : drop;
  }

  std::vector<e_t> expected;
  std::remove_copy(data.begin(), data.end(), std::back_inserter(expected), drop);
  std::transform(expected.begin(), expected.end(), expected.begin(), op);

  auto rng = eve::algo::as_range(eve::as_aligned(data.begin()), data.end());
  auto func = [drop, &op](auto x) {
    return kumi::make_tuple(op(x), eve::is_not_equal(drop, x));
  };
  std::vector<e_t> actual{data.begin(), alg(rng, func)};

  TTS_EQUAL(expected, actual);
};

template <typename T, typename Algo>
void remove_generic_test_page_ends(eve::as<T>, Algo alg)
{
  using e_t     = eve::element_type_t<T>;
  using card_t  = eve::fixed<4096/ sizeof(e_t)>;
  std::vector<e_t, eve::aligned_allocator<e_t, card_t>> page(card_t::value, e_t{0});

  constexpr int elements_to_test  = std::min( int(T::size() * 10), 300);

  auto f = page.data();
  auto l = f + elements_to_test;

  auto prepopulate = [&](auto it) {
    std::fill(it, l, 0);

    std::ptrdiff_t count = 0;

    while (it + 1 < l) {
      *it = 1;
      ++count;
      it += 2;
    }

    return count;
  };

  auto run = [&]() {
    for (auto* it = f; it < l; ++it) {
      std::ptrdiff_t count = prepopulate(it);
      e_t* end = alg(eve::algo::as_range(it, l), 0);
      TTS_EQUAL(count, (end - it));

      std::vector<e_t> expected_prefix(it - f, 0);
      TTS_EQUAL(expected_prefix, std::vector<e_t>(f, it));

      std::vector<e_t> expected_suffix(count, 1);
      TTS_EQUAL(expected_suffix, std::vector<e_t>(it, end));

      *it = 0;

      if (l - page.data() != static_cast<std::ptrdiff_t>(page.size())) {
        TTS_EQUAL(*l, e_t{0});
      }
    }
  };

  while (f < l) {
    run();
    *l = 0;
    --l;
    *f = 0;
    ++f;
  }

  l = page.data() + page.size();
  f = l - elements_to_test;

  // from the end
  while (f < l) {
    run();
    if (l != (page.data() + page.size())) { *l = 1; }
    --l;
    *f = 1;
    ++f;
  }
}
