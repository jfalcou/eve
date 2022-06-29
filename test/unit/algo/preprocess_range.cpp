//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/module/core.hpp>
#include "unit/algo/algo_test.hpp"

#include <eve/algo/preprocess_range.hpp>

#include <eve/algo/views/convert.hpp>
#include <eve/algo/ptr_iterator.hpp>


#include <array>
#include <vector>

TTS_CASE_TPL("Check preprocess_range for contiguous iterators", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<eve::expected_cardinal_v<e_t>>;

  using u_it  = eve::algo::ptr_iterator<e_t*, N>;
  using uc_it = eve::algo::ptr_iterator<e_t const*, N>;

  alignas(sizeof(eve::wide<e_t, N>) * 2) std::array<e_t, N{}()> arr{};

  std::vector<e_t> vec(100u, 0);

  auto common_test = [](auto f, auto l, auto expected_f_type, auto expected_l_type) {
    auto processed = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), f, l);
    TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<decltype(processed.traits())>() == 2);
    TTS_TYPE_IS(decltype(processed.begin()), decltype(expected_f_type));
    TTS_TYPE_IS(decltype(processed.end()), decltype(expected_l_type));

    TTS_EQUAL((processed.end() - processed.begin()), (eve::unalign(l) - eve::unalign(f)));

    auto processed_empty = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), f, f);
    TTS_EQUAL(processed_empty.begin(), processed_empty.end());

    return processed;
  };

  // pointers
  common_test(
    arr.begin(), arr.end(),
    u_it{}, u_it{});

  // const pointers
  common_test(
    arr.cbegin(), arr.cend(),
    uc_it{},
    uc_it{}
  );

  // aligned_pointer
  {
    using ap = eve::aligned_ptr<e_t, N>;

    auto processed = common_test(
      ap{arr.begin()}, arr.end(),
      eve::algo::ptr_iterator<ap, N>{},
      u_it{}
    );
    TTS_CONSTEXPR_EXPECT(decltype(processed.traits())::contains(eve::algo::no_aligning));
  }

  // const aligned_pointer
  {
    using ap = eve::aligned_ptr<e_t const, N>;

    auto processed = common_test(
      ap{arr.cbegin()}, arr.cend(),
      eve::algo::ptr_iterator<ap, N>{},
      uc_it{}
    );
    TTS_CONSTEXPR_EXPECT(decltype(processed.traits())::contains(eve::algo::no_aligning));
  }

  // two aligned_pointers
  {
    using ap = eve::aligned_ptr<e_t, N>;

    auto processed = common_test(
      ap{arr.begin()}, ap{arr.end()},
      eve::algo::ptr_iterator<ap, N>{},
      eve::algo::ptr_iterator<ap, N>{}
    );
    TTS_CONSTEXPR_EXPECT(decltype(processed.traits())::contains(eve::algo::no_aligning));
    TTS_CONSTEXPR_EXPECT(decltype(processed.traits())::contains(eve::algo::divisible_by_cardinal));
  }

  // two const aligned_pointers
  {
    using ap = eve::aligned_ptr<e_t const, N>;

    auto processed = common_test(
      ap{arr.cbegin()}, ap{arr.cend()},
      eve::algo::ptr_iterator<ap, N>{},
      eve::algo::ptr_iterator<ap, N>{}
    );
    TTS_CONSTEXPR_EXPECT(decltype(processed.traits())::contains(eve::algo::no_aligning));
    TTS_CONSTEXPR_EXPECT(decltype(processed.traits())::contains(eve::algo::divisible_by_cardinal));
  }

  // unaligned/aligned
  {
    using ap = eve::aligned_ptr<e_t, N>;
    using acp = eve::aligned_ptr<e_t const, N>;

    common_test(
      arr.begin(), ap{arr.end()},
      u_it{},
      eve::algo::ptr_iterator<ap, N>{}
    );
    common_test(
      arr.cbegin(), acp{arr.cend()},
      uc_it{},
      eve::algo::ptr_iterator<acp, N>{}
    );
  }

  // Not aligned enough
  if constexpr (N{}() > 1) {
    common_test(
      arr.begin(), eve::aligned_ptr<e_t, eve::fixed<1>>{arr.end()},
      u_it{},
      u_it{}
    );
    common_test(
      eve::aligned_ptr<e_t, eve::fixed<1>>{arr.begin()}, eve::aligned_ptr<e_t, eve::fixed<1>>{arr.end()},
      u_it{},
      u_it{}
    );
  }

  // over aligned
  {
    common_test(
      eve::aligned_ptr<e_t, eve::fixed<N{}() * 2>>{arr.begin()}, eve::aligned_ptr<e_t>{arr.end()},
      eve::algo::ptr_iterator<eve::aligned_ptr<e_t, N>, N>{},
      eve::algo::ptr_iterator<eve::aligned_ptr<e_t, N>, N>{}
    );
  }

  // vector::iterator
  common_test(
    vec.begin(), vec.end(),
    u_it{}, u_it{});

  // vector::const_iterator
  common_test(
    vec.cbegin(), vec.cend(),
    uc_it{}, uc_it{});
};

TTS_CASE_TPL("Check preprocess_range for eve ptr iterators", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<T::size()>;
  using expected_N = eve::fixed<eve::expected_cardinal_v<e_t>>;

  alignas(sizeof(T)) std::array<e_t, T::size()> arr;

  auto run_one_test = [&]<typename I, typename S, typename ExpectedTraits>(I f, S l, ExpectedTraits)
  {
    auto f_ = f.cardinal_cast(expected_N{});
    auto l_ = l.cardinal_cast(expected_N{});

    auto processed = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), f, l);
    TTS_TYPE_IS(decltype(processed.traits()), ExpectedTraits);
    TTS_TYPE_IS(decltype(processed.begin()), decltype(f_));
    TTS_TYPE_IS(decltype(processed.end()), decltype(l_));
    TTS_EQUAL(processed.begin(), f_);
    TTS_EQUAL(processed.end(), l_);

    auto processed_empty = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), f, f);
    TTS_EQUAL(processed_empty.begin(), processed_empty.end());
  };

  auto run_test = [&] <typename U>(U* f, U* l) {
    using aligned_p = eve::aligned_ptr<U, N>;

    eve::algo::ptr_iterator<U*, N>         u_f(f);
    eve::algo::ptr_iterator<U*, N>         u_l(l);
    eve::algo::ptr_iterator<aligned_p, N>  a_f(aligned_p{f});
    eve::algo::ptr_iterator<aligned_p, N>  a_l(aligned_p{l});

    run_one_test(u_f, u_l, eve::algo::traits(eve::algo::unroll<2>));
    run_one_test(u_f, a_l, eve::algo::traits(eve::algo::unroll<2>));
    if constexpr ( N{}() >= expected_N{}())
    {
      run_one_test(a_f, a_l, eve::algo::traits(eve::algo::unroll<2>, eve::algo::no_aligning, eve::algo::divisible_by_cardinal));
      run_one_test(a_f, u_l, eve::algo::traits(eve::algo::unroll<2>, eve::algo::no_aligning));
    }
    else
    {
      run_one_test(a_f, a_l, eve::algo::traits(eve::algo::unroll<2>));
      run_one_test(a_f, u_l, eve::algo::traits(eve::algo::unroll<2>));
    }
  };

  run_test(arr.begin(), arr.end());
  run_test(arr.cbegin(), arr.cend());
};

TTS_CASE_TPL("contiguous ranges", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<eve::expected_cardinal_v<e_t>>;

  // empty vector
  {
    std::vector<e_t> v;
    using u_it = eve::algo::ptr_iterator<e_t*, N>;

    auto processed = eve::algo::preprocess_range(eve::algo::traits(), v);
    TTS_TYPE_IS(decltype(processed.traits()), decltype(eve::algo::traits()));
    TTS_TYPE_IS(decltype(processed.begin()), u_it);
    TTS_TYPE_IS(decltype(processed.end()), u_it);
    TTS_EQUAL(processed.begin(), processed.end());
  }

  auto non_empty_range_test = [](auto&& rng) {
    auto processed = eve::algo::preprocess_range(eve::algo::traits(), rng);

    using u_it = eve::algo::ptr_iterator<
      std::remove_reference_t<decltype(*std::begin(rng))>*, N>;

    TTS_TYPE_IS(decltype(processed.traits()), decltype(eve::algo::traits()));
    TTS_TYPE_IS(decltype(processed.begin()), u_it);
    TTS_TYPE_IS(decltype(processed.end()), u_it);
  };

  {
    std::vector<e_t> v(10, 1);
    non_empty_range_test(v);
  }

  {
    const std::vector<e_t> v(10, 1);
    non_empty_range_test(v);
  }

// We need better ranges support for it.
#if 0
  {
    e_t v[10] = {};
    non_empty_range_test(v);
  }

  {
    e_t const v[10] = {};
    non_empty_range_test(v);
  }
#endif

  {
    std::array<e_t, 10> v = {};
    non_empty_range_test(v);
  }

  {
    const std::array<e_t, 10> v = {};
    non_empty_range_test(v);
  }
};

TTS_CASE_TPL("cardinal/type manipulation", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;

  std::vector<e_t> v;
  std::vector<double> v_d;
  {
    auto processed = eve::algo::preprocess_range(
    eve::algo::traits(eve::algo::force_cardinal<T::size()>), v);

    using I = decltype(processed.begin());
    TTS_TYPE_IS(eve::wide_value_type_t<I>, T);
  }

  {
    using cardinal_n = eve::detail::cache_line_cardinal<e_t>;
    auto processed = eve::algo::preprocess_range(
    eve::algo::traits(eve::algo::force_cardinal<cardinal_n{}()>), v);

    using I = decltype(processed.begin());
    TTS_TYPE_IS(eve::iterator_cardinal_t<I>, cardinal_n);
  }

  {
    auto processed = eve::algo::preprocess_range(
      eve::algo::traits(),
      eve::algo::views::convert(v, eve::as<eve::common_type_t<double, std::int8_t>>{}));

    using I = decltype(processed.begin());
    TTS_TYPE_IS(typename I::value_type, double);
    TTS_TYPE_IS(eve::wide_value_type_t<I>, eve::wide<double>);
  }

  {
    auto processed = eve::algo::preprocess_range(
      eve::algo::traits(eve::algo::force_cardinal<T::size()>),
      eve::algo::views::convert(v, eve::as<double>{}));

    using I = decltype(processed.begin());
    TTS_TYPE_IS(eve::wide_value_type_t<I>,
                (eve::wide<double, eve::fixed<T::size()>>));
  }

  {
    auto processed = eve::algo::preprocess_range(
      eve::algo::traits(eve::algo::consider_types<double>), v);

    using I = decltype(processed.begin());
    TTS_TYPE_IS(eve::wide_value_type_t<I>,
                (eve::wide<e_t, eve::fixed<eve::expected_cardinal_v<double>>>));
  }

  {
    auto processed = eve::algo::preprocess_range(
      eve::algo::traits{}, eve::algo::views::convert(v_d, eve::as<e_t>{}));

    using I = decltype(processed.begin());
    TTS_TYPE_IS(eve::wide_value_type_t<I>,
                (eve::wide<e_t, eve::fixed<eve::expected_cardinal_v<double>>>));
  }
};
