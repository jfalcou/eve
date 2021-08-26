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

    TTS_EQUAL(alg(eve::algo::as_range(f, l), e_t{0}), e_t{13});
  }

  // const iterator
  {
    const std::vector<e_t> v(27u, e_t(1));
    TTS_EQUAL(alg(v, e_t{1}), e_t{28});
  }
}

template <typename Algo, typename Init>
struct reduce_ptr_test
{
  Init ini;
  Algo alg;

  reduce_ptr_test(Init ini, Algo alg) : ini(ini), alg(alg) {}

  void init(auto*, auto* f, auto* l, auto*) const
  {
    std::iota(f, l, 0);
  }

  auto run(auto rng) const
  {
    auto f = eve::algo::unalign(rng.begin());
    auto l = eve::algo::unalign(rng.end());
    auto expected = std::reduce(f, l, ini);
    auto res = alg(rng, ini);

    TTS_EQUAL(res, expected);
    TTS_TYPE_IS(decltype(res), decltype(expected));
    if (res != expected) std::terminate();
  }

  void adjust(auto*, auto* f, auto* l, auto* page_end) const
  {
    *f = 1;
    if (l != page_end) *l = 1;
  }
};

template <typename T, typename Init,  typename Algo>
void reduce_generic_test_page_ends(eve::as<T> tgt, Init init, Algo alg)
{
  specific_tests(tgt, alg);

  algo_test::page_ends_test(tgt, reduce_ptr_test{init, alg});
}

template <typename T, typename Alg>
void all_test_cases(eve::as<T> tgt, Alg basic_reduce)
{
  using e_t = eve::element_type_t<T>;
  auto native_tgt = eve::as<eve::wide<e_t>>{};

  // The very basic one
  reduce_generic_test_page_ends(native_tgt, e_t{0}, basic_reduce);

  // all should be good to double
  reduce_generic_test_page_ends(native_tgt, double(1), basic_reduce);

  // Reduce to a smaller type.
  // For floats no smaller type is avaliable, since float -> int conversion can be ub.
  if constexpr (std::same_as<e_t, double>)
  {
    reduce_generic_test_page_ends(native_tgt, float(4), basic_reduce);
  }
  else if constexpr (std::signed_integral<e_t> && !std::same_as<e_t, std::int8_t>)
  {
    reduce_generic_test_page_ends(native_tgt, std::int8_t(4), basic_reduce);
  }
  else if constexpr (std::unsigned_integral<e_t> && !std::same_as<e_t, std::uint8_t> )
  {
    reduce_generic_test_page_ends(native_tgt, std::uint8_t(4), basic_reduce);
  }

  // no unroll, precise tgt
  {
    auto alg = basic_reduce[eve::algo::unroll<1>][eve::algo::force_cardinal<T::size()>];
    reduce_generic_test_page_ends(tgt, e_t{10}, alg);
  }

  // unroll 3
  {
    reduce_generic_test_page_ends(native_tgt, e_t{10}, basic_reduce[eve::algo::unroll<3>]);
  }
}

EVE_TEST_TYPES("Check reduce", algo_test::selected_types)
<typename T>(eve::as<T> tgt)
{
  all_test_cases(tgt, eve::algo::reduce);
};
