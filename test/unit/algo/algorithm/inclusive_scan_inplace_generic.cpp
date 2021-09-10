//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/inclusive_scan.hpp>
#include <eve/algo/as_range.hpp>

#include <algorithm>
#include <functional>
#include <vector>

template <typename T, typename Init, typename Algo>
void specific_tests(eve::as<T>, Init init, Algo alg)
{
  using e_t = eve::element_type_t<T>;

  std::vector<e_t> v        { 0, 1, 2, 3, 4 };

  std::vector<e_t> expected(v.size());
  std::inclusive_scan(v.begin(), v.end(), expected.begin(), std::plus<>{}, init);

  alg(v, init);
  TTS_EQUAL(expected, v);
}

template <typename Algo, typename Init>
struct inclusive_scan_inplace_ptr_test
{
  Init ini;
  Algo alg;

  inclusive_scan_inplace_ptr_test(Init ini, Algo alg):
    ini(ini), alg(alg)
  {}


  void init(auto* pg_b, auto*, auto*, auto* pg_e)
  {
    std::iota(pg_b, pg_e, 0);
  }

  void run(auto rng) const
  {
    auto f = eve::algo::unalign(rng.begin());
    auto l = eve::algo::unalign(rng.end());

    using T = eve::algo::value_type_t<decltype(rng)>;

    std::vector<T> expected(l - f, 0);
    std::inclusive_scan(f, l, expected.begin(), std::plus<>{}, ini);

    alg(rng, ini);
    std::vector<T> actual(f, l);

    if constexpr (std::floating_point<T> ) {
      for (int i = 0; i != (l - f); ++i)
      {
        TTS_RELATIVE_EQUAL(expected[i], actual[i], 0.0001);
      }
    }
    else {
      TTS_EQUAL(expected, actual);
    }
  }

  void adjust(auto*, auto* f, auto* l, auto* page_end) const
  {
    *f = 1;
    if (l != page_end) *l = 1;
  }
};

template <typename T, typename Init,  typename Algo>
void inclusive_scan_inplace_generic_test(eve::as<T> tgt, Init init, Algo alg)
{
  specific_tests(tgt, init, alg);

  algo_test::page_ends_test(tgt, inclusive_scan_inplace_ptr_test{init, alg});
}

template <typename T, typename Alg>
void all_test_cases(eve::as<T> tgt, Alg alg)
{
  using e_t = eve::element_type_t<T>;
  auto native_tgt = eve::as<eve::wide<e_t>>{};

  // The very basic one
  inclusive_scan_inplace_generic_test(native_tgt, e_t{0}, alg);

  inclusive_scan_inplace_generic_test(tgt, e_t{10}, alg[eve::algo::unroll<1>][eve::algo::force_cardinal<T::size()>]);
  inclusive_scan_inplace_generic_test(tgt, e_t{10}, alg[eve::algo::unroll<3>][eve::algo::force_cardinal<T::size()>]);
  inclusive_scan_inplace_generic_test(tgt, e_t{10}, alg[eve::algo::unroll<4>][eve::algo::force_cardinal<T::size()>]);
}

EVE_TEST_TYPES("Check inlclusive_scan_inplace", algo_test::selected_types)
<typename T>(eve::as<T> tgt)
{
  all_test_cases(tgt, eve::algo::inclusive_scan_inplace);
};
