//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "unit/algo/algo_test.hpp"

namespace algo_test {

  template<typename Tgt, typename Algo, typename Control, typename ...Args>
  struct transform_to_ptr_test
  {
    eve::as<Tgt> tgt;
    Algo alg;
    Control control;
    kumi::tuple<Args...> args;

    std::vector<std::tuple_element_t<1, eve::element_type_t<Tgt>>> ans;

    transform_to_ptr_test(eve::as<Tgt> tgt, Algo alg, Control control, Args... args) :
      tgt(tgt), alg(alg), control(control), args{args...} {}

    void init(auto& page_1, auto& /*page_2*/) const
    {
      std::iota(page_1.begin(), page_1.end(), 0);
    }

    void generate_answer(auto* f1, auto* l1, auto*, auto*)
    {
      ans.resize(l1 - f1);
      kumi::apply(control, kumi::cat(kumi::tuple{f1, l1, ans.begin()}, args));
    }

    template <typename R1, typename R2>
    void run(R1 range_or_it1, R2 range_or_it2)
    {
      auto zipped_range = eve::algo::views::zip(range_or_it1, range_or_it2);
      // To operate with both ends always
      auto r1 = get<0>(zipped_range);
      auto r2 = get<1>(zipped_range);

      auto r2f = eve::algo::unalign(r2.begin());
      auto r2l = eve::algo::unalign(r2.end());

      using U = eve::algo::value_type_t<R2>;

      // Here use what was passed
      kumi::apply(alg, kumi::cat(kumi::tuple{range_or_it1, range_or_it2}, args));

      std::vector<U> actual(r2f, r2l);

      if constexpr( std::floating_point<U> )
      {
        for( int i = 0; i != (r1.end() - r1.begin()); ++i ) {
          TTS_RELATIVE_EQUAL(ans[i], actual[i], 0.0001);
        }
      }
      else
      {
        if (ans != actual) {
          std::cout << tts::detail::typename_<decltype(r1.begin())>::value() << std::endl;
          std::cout << tts::detail::typename_<decltype(r1.end())>::value() << std::endl;
          std::cout << tts::detail::typename_<decltype(r2.begin())>::value() << std::endl;
          std::cout << tts::detail::typename_<decltype(r2.end())>::value() << std::endl;

          std::cout << std::hex << (std::int64_t)eve::algo::unalign(r1.begin()) << std::dec << std::endl;
          TTS_EQUAL(ans, actual);
          std::terminate();
        }

      }
    }
  };

  template <typename T, typename Algo, typename Control, typename ...Args>
  void transform_to_generic_test_page_ends(eve::as<T> tgt, Algo alg, Control control, Args... args)
  {
    transform_to_ptr_test test{tgt, alg, control, args...};
    two_ranges_test(tgt, test);
  }

  template <typename T, typename Algo, typename Control, typename ...Args>
  void transform_to_generic_test(eve::as<T> tgt, Algo alg, Control control, Args... args)
  {
    using e_t = eve::element_type_t<T>;
    auto native_tgt = eve::as<eve::wide<e_t>>{};

    transform_to_generic_test_page_ends(native_tgt, alg, control, args...);
    transform_to_generic_test_page_ends(tgt, alg[eve::algo::unroll<1>][eve::algo::force_cardinal<T::size()>],
                                             control, args...);
  }

}
