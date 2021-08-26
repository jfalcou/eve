//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================

#pragma once
#include "test.hpp"

#include <eve/memory/aligned_allocator.hpp>

#include <eve/algo/as_range.hpp>

#include <vector>

namespace algo_test
{
  inline constexpr eve::detail::types<
      eve::wide<std::int8_t, eve::fixed<1>>
    , eve::wide<std::uint8_t>
    , eve::wide<std::int16_t>
    , eve::wide<std::uint16_t, eve::fixed<4>>
    , eve::wide<int>
    , eve::wide<float>
    , eve::wide<double>
    , eve::wide<std::uint64_t>
#if !defined(SPY_SIMD_IS_X86_AVX512)
    , eve::wide < std::uint32_t
                , eve::fixed<eve::expected_cardinal_v<std::uint32_t> * 2>
                >
#endif
  > selected_types;

  template <typename T, typename Test>
  void ptr_range_test(eve::as<T>,
                      eve::element_type_t<T>* f,
                      eve::element_type_t<T>* l,
                      Test test)
  {
    using e_t = eve::element_type_t<T>;

    // unaligned
    test.run(eve::algo::as_range(f, l));

    static constexpr std::ptrdiff_t alignment = sizeof(e_t) * T::size();
    using a_p = eve::aligned_ptr<e_t, eve::fixed<T::size()>>;

    if (eve::is_aligned<alignment>(f))
    {
      auto f_ = a_p(f);
      test.run(eve::algo::as_range(f_, l));

      if (eve::is_aligned<alignment>(l))
      {
        auto l_ = a_p(l);
        test.run(eve::algo::as_range(f_, l_));
      }
    }
  }

  template <typename T, typename Test>
  void page_ends_test(eve::as<T> tgt, Test test)
  {
    using e_t     = eve::element_type_t<T>;
    using e_ts_in_page  = eve::fixed<4096/ sizeof(e_t)>;
    std::vector<e_t, eve::aligned_allocator<e_t, e_ts_in_page>> page(e_ts_in_page::value, e_t{0});

    constexpr int elements_to_test  = std::min( int(T::size() * 10), 300);

    auto* page_begin = page.data();
    auto* f          = page.data();
    auto* l          = f + elements_to_test;
    auto* page_end   = page_begin + page.size();

    auto run_f_l = [&] () mutable {
      test.init(page_begin, f, l, page_end);

      while( f < l ) {
        ptr_range_test(tgt, f, l, test);
        test.adjust(page_begin, f, l, page_end);
        --l;
        ++f;
      }
    };

    run_f_l();

    l = page_end;
    f = l - elements_to_test;

    run_f_l();
  }
}
