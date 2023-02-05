//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#pragma once
#include "test.hpp"

#include <eve/memory/aligned_allocator.hpp>
#include <eve/module/algo.hpp>

#include <vector>

namespace algo_test
{
  using selected_types = tts::types<
      eve::wide<std::int8_t, eve::fixed<1>>
    , eve::nofs_wide<std::uint8_t>
    , eve::wide<std::int16_t>
    , eve::wide<std::uint16_t, eve::fixed<4>>
    , eve::wide<int>
    , eve::nofs_wide<float>
    , eve::wide<double>
    , eve::wide<std::uint64_t>
    , eve::wide < std::uint32_t
                , eve::fixed<eve::nofs_cardinal_v<std::uint32_t> * 2>
                >
  >;

  using selected_pairs_types = tts::types<
      eve::wide<kumi::tuple<std::int8_t, std::int16_t>, eve::fixed<1>>
    , eve::nofs_wide<kumi::tuple<std::uint8_t, std::uint8_t>>
    , eve::wide<kumi::tuple<std::int32_t, std::int32_t>>
    , eve::nofs_wide<kumi::tuple<std::int32_t, std::uint16_t>>
    , eve::wide<kumi::tuple<float, double>, eve::fixed<2>>
    , eve::wide<kumi::tuple<float, double>>
    , eve::wide<kumi::tuple<std::uint32_t, std::int64_t>,
                eve::fixed<eve::expected_cardinal_v<std::uint32_t> * 2>
                >
    > ;


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

  template <typename T>
  auto allocate_page()
  {
    using ts_in_page  = eve::fixed<4096/ sizeof(T)>;
    using alloc       = eve::aligned_allocator<T, ts_in_page>;
    return std::vector<T, alloc>(ts_in_page::value, 0);
  }

  template <typename N, typename T>
  auto optional_aligned_ptr(T* ptr) {
    static constexpr std::ptrdiff_t alignment = sizeof(T) * N{}();
    if (eve::is_aligned<alignment>(ptr)) return eve::aligned_ptr<T, N>{ptr};
    else                                 return eve::aligned_ptr<T, N>{};
  }

  template <typename T, typename Test>
  void page_ends_test_special_cases(eve::as<T> tgt,
                                    eve::element_type_t<T>* f,
                                    eve::element_type_t<T>* l,
                                    Test test)
  {
    if ((l - f) >= T::size())
    {
      ptr_range_test(tgt, f, f + T::size(), test);
    }
    if ((l - f) >= T::size() * 3)
    {
      ptr_range_test(tgt, f, f + 3 * T::size(), test);
    }
  }

  template <typename T, typename Test>
  void page_ends_test(eve::as<T> tgt, Test test)
  {
    auto page = allocate_page<eve::element_type_t<T>>();

    constexpr int elements_to_test  = std::min( int(T::size() * 10), 300);

    auto* page_begin = page.data();
    auto* f          = page.data();
    auto* l          = f + elements_to_test;
    auto* page_end   = page_begin + page.size();

    auto run_f_l = [&] () mutable {
      test.init(page_begin, f, l, page_end);

      page_ends_test_special_cases(tgt, f, l, test);

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

  template <typename N>
  auto select_offsets() {
    if constexpr ( N{}() <= 7 )
    {
      std::array<int, N{}()> res;
      std::iota(res.begin(), res.end(), 0);
      return res;
    }
    else
    {
      std::array<int, 7> res;
      std::iota(res.begin(), res.end(), 0);
      res.back() = N{}();
      return res;
    }
  }

  template <typename WideTU, typename Test>
  void two_ranges_test(eve::as<WideTU>, Test& test)
  {
    using TU = eve::element_type_t<WideTU>;
    using T  = std::tuple_element_t<0, TU>;
    using U  = std::tuple_element_t<1, TU>;
    using N  = eve::fixed<WideTU::size()>;

    auto page_1 = allocate_page<T>();
    auto page_2 = allocate_page<U>();

    test.init(page_1, page_2);

    constexpr int elements_to_test  = std::min( int(N{}() * 10), 300 );

    auto* f1_base = page_1.data();
    auto* f2_base = page_2.data();

    for (int offset_1 : select_offsets<N>()) {
      for (int offset_2 : select_offsets<N>()) {
        auto* f1 = f1_base + offset_1;
        auto* f2 = f2_base + offset_2;

        for (int size = 0; size < elements_to_test; size += 3) {
          auto* l1 = f1 + size;
          auto* l2 = f2 + size;

          test.generate_answer(f1, l1, f2, l2);

          auto one_test = [&test](auto f1_, auto l1_, auto f2_, auto l2_) {
            test.run(eve::algo::as_range(f1_, l1_), f2_                         );
            test.run(f1_,                           eve::algo::as_range(f2_, l2_));
            test.run(eve::algo::as_range(f1_, l1_), eve::algo::as_range(f2_, l2_));
          };

          auto generate_aligning_tests =
            [one_test]<std::ptrdiff_t i, typename F1, typename L1, typename F2, typename L2>
            (auto self, eve::index_t<i>, F1 f1_, L1 l1_, F2 f2_, L2 l2_)
          {
            if (!f1_ || !l1_ || !f2_ || !l2_) return;

            auto next = eve::index<i + 1>;

            one_test(f1_, l1_, f2_, l2_);

            if constexpr ( i == 4 ) return;
            else
            {
              self(self, next, f1_, l1_, f2_, l2_);

                   if constexpr ( i == 0 ) self(self, next, optional_aligned_ptr<N>(f1_), l1_, f2_, l2_);
              else if constexpr ( i == 1 ) self(self, next, f1_, optional_aligned_ptr<N>(l1_), f2_, l2_);
              else if constexpr ( i == 2 ) self(self, next, f1_, l1_, optional_aligned_ptr<N>(f2_), l2_);
              else if constexpr ( i == 3 ) self(self, next, f1_, l1_, f2_, optional_aligned_ptr<N>(l2_));
            }
          };
          generate_aligning_tests(generate_aligning_tests, eve::index<0>, f1, l1, f2, l2);
        }
      }
    }
  }
}
