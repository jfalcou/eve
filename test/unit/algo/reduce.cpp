//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/reduce.hpp>

#include <eve/algo/as_range.hpp>
#include <eve/memory/aligned_allocator.hpp>

#include <vector>

template <typename T, typename Algo>
void specific_tests(eve::as<T>, Algo alg)
{
  using e_t = eve::element_type_t<T>;

  // const T*
  {
    std::vector<e_t> v(13u, e_t(1));

    const e_t* f = v.data();
    const e_t* l = f + v.size();

    TTS_EQUAL(alg(eve::algo::as_range(f, l), 0), 13);
  }

  // const iterator
  {
    const std::vector<e_t> v(27u, e_t(1));
    TTS_EQUAL(alg(v, 1), 28);
  }
}

template <typename T, typename U, typename Init, typename Expected, typename Algo>
void reduce_one_ptr_test(eve::as<T>, U* f, U* l, Init init, Expected expected, Algo alg)
{
  // unaligned
  {
    auto res = alg(eve::algo::as_range(f, l), init);
    TTS_EQUAL(res, expected);
    TTS_TYPE_IS(decltype(res), Expected);
  }

  static constexpr std::ptrdiff_t alignment = T::size() * sizeof(U);
  using a_p = eve::aligned_ptr<U, eve::fixed<T::size()>>;

  if (eve::is_aligned<alignment>(f))
  {
    auto f_ = a_p(f);
    auto res = alg(eve::algo::as_range(f_, l), init);
    TTS_EQUAL(res, expected);
    if (res != expected) std::terminate();
    TTS_TYPE_IS(decltype(res), Expected);

    if (eve::is_aligned<alignment>(l))
    {
      auto l_ = a_p(l);
      auto res = alg(eve::algo::as_range(f_, l_), init);
      TTS_EQUAL(res, expected);
    }
  }
}

template <typename T, typename Init,  typename Algo>
void reduce_generic_test_page_ends(eve::as<T> tgt, Init init, Algo alg)
{
  specific_tests(tgt, alg);

  using e_t     = eve::element_type_t<T>;
  using card_t  = eve::fixed<4096/ sizeof(e_t)>;
  std::vector<e_t, eve::aligned_allocator<e_t, card_t>> page(card_t::value, e_t{0});

  constexpr int elements_to_test  = std::min(T::size() * 10, 300l);

  auto f = page.data();
  auto l = f + elements_to_test;

  auto run = [&] {
    // iota from f to l
    for (auto* it = f; it < l; ++it) {
      reduce_one_ptr_test(tgt, it, l, init, std::reduce(it, l, init), alg);
    }
  };


  std::iota(f, l, 0);
  // from the beginning
  while (f < l) {
    run();
    if (l != (page.data() + page.size())) { *l = 1; }
    --l;
    *f = 1;
    ++f;
  }

  l = page.data() + page.size();
  f = l - elements_to_test;

  std::iota(f, l, 0);

  // from the end
  while (f < l) {
    run();
    if (l != (page.data() + page.size())) { *l = 1; }
    --l;
    *f = 1;
    ++f;
  }
}

template <typename T, typename Alg>
void all_test_cases(eve::as<T> tgt, Alg basic_reduce)
{
  // all should be good to double
  reduce_generic_test_page_ends(tgt, double(1), basic_reduce);

  // we can init everything with char
  reduce_generic_test_page_ends(tgt, char(4), basic_reduce);
}

EVE_TEST_TYPES("Check reduce", algo_test::selected_types)
<typename T>(eve::as<T> tgt)
{
  (void)tgt;
  all_test_cases(eve::as<eve::wide<char>>{}, eve::algo::reduce);
};
