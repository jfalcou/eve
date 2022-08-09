//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "unit/algo/algo_test.hpp"

namespace algo_test
{
  template<typename Algo, typename Control, typename ...Args>
  struct transform_inplace_ptr_test
  {
    Algo alg;
    Control control;
    kumi::tuple<Args...> args;

    transform_inplace_ptr_test(Algo alg, Control control, Args... args) :
      alg(alg), control(control), args{args...} {}

    void init(auto *pg_b, auto *, auto *, auto *pg_e) { std::iota(pg_b, pg_e, 0); }

    void run(auto rng) const
    {
      auto f = eve::unalign(rng.begin());
      auto l = eve::unalign(rng.end());

      using T = eve::value_type_t<decltype(rng)>;

      std::vector<T> expected(l - f, 0);

      kumi::apply(control, kumi::cat(kumi::tuple{f, l, expected.begin()}, args));

      kumi::apply(alg, kumi::cat(kumi::tuple{rng}, args));

      std::vector<T> actual(f, l);

      if constexpr( std::floating_point<T> )
      {
        for( int i = 0; i != (l - f); ++i ) {
          TTS_RELATIVE_EQUAL(expected[i], actual[i], 0.0005);
        }
      }
      else
      {
        TTS_EQUAL(expected, actual);
      }
    }

    void adjust(auto *, auto *f, auto *l, auto *page_end) const
    {
      *f = 1;
      if( l != page_end ) *l = 1;
    }
  };

  template <typename T, typename Algo, typename Control, typename ...Args>
  void transform_inplace_generic_test_page_ends(eve::as<T> tgt, Algo alg, Control control, Args... args)
  {
    transform_inplace_ptr_test test{alg, control, args...};
    algo_test::page_ends_test(tgt, test);
  }

  template <typename T, typename Algo, typename Control, typename ...Args>
  void transform_inplace_generic_test(eve::as<T> tgt, Algo alg, Control control, Args... args)
  {
    using e_t = eve::element_type_t<T>;
    auto native_tgt = eve::as<eve::wide<e_t>>{};

    transform_inplace_generic_test_page_ends(native_tgt, alg, control, args...);
    transform_inplace_generic_test_page_ends(tgt, alg[eve::algo::unroll<1>][eve::algo::force_cardinal<T::size()>],
                                             control, args...);
  }

}
