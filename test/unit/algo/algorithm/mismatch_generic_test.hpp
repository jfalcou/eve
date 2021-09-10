//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include "unit/algo/algo_test.hpp"

#include <eve/algo/unalign.hpp>
#include <eve/algo/zip.hpp>

#include <algorithm>
#include <random>
#include <set>

namespace algo_test
{
  template <typename Algo, typename Check>
  struct mismatch_ptr_test
  {
    std::mt19937& gen;
    Algo alg;
    Check check;

    std::set<int> all_distances;

    mismatch_ptr_test(std::mt19937& gen, Algo alg, Check check) : gen(gen), alg(alg), check(check) {}

    void init(auto& page_1, auto& /*page_2*/) const
    {
      std::fill(page_1.begin(), page_1.end(), 1);
    }

    void run(auto range1, auto range2)
    {
      auto zipped_range = eve::algo::zip(range1, range2);
      auto zip_f = eve::algo::unalign(zipped_range.begin());
      auto zip_l = eve::algo::unalign(zipped_range.end());

      std::uniform_int_distribution<> dis{0, static_cast<int>(zip_l - zip_f)};

      int distance = dis(gen);
      all_distances.insert(distance);

      auto zip_m = zip_f + distance;

      std::fill(get<0>(zip_f), get<0>(zip_m), 0);

      check(zip_f, zip_l, zip_m, alg(range1, range2));

      std::fill(get<0>(zip_f), get<0>(zip_m), 1);
    }
  };

  template <typename T, typename Algo, typename Check>
  void mismatch_one_algo_test(eve::as<T> tgt, Algo alg, Check check, std::mt19937& gen)
  {
    mismatch_ptr_test delegate{gen, alg, check};
    two_ranges_test(tgt, delegate);
    std::cout << "Distances tested: " << delegate.all_distances.size() << std::endl;
  }

  template <typename T, typename Algo, typename Check>
  void mismatch_generic_test(eve::as<T> tgt, Algo alg, Check check)
  {
    std::mt19937 gen;

    mismatch_one_algo_test(eve::as<eve::wide<typename T::value_type>>{}, alg, check, gen);

    mismatch_one_algo_test(tgt, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<2>], check, gen);
    mismatch_one_algo_test(tgt, alg[eve::algo::force_cardinal<T::size()>][eve::algo::unroll<3>], check, gen);
  }
}
