//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/preprocess_range.hpp>

#include <eve/algo/ptr_iterator.hpp>

#include <array>
#include <vector>


EVE_TEST_TYPES("Check preprocess_range for contiguous iterators", algo_test::selected_types)
<typename T>(eve::as_<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<eve::expected_cardinal_v<e_t>>;

  alignas(sizeof(eve::wide<e_t, N>)) std::array<e_t, N{}()> arr{};

  std::vector<e_t> vec(100u, 0);

  // pointers
  {

    auto [traits, f, l] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), arr.begin(), arr.end());
    TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<decltype(traits)>() == 2);
    TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<e_t, N>));
    TTS_EQUAL((void*)f.ptr, (void*)arr.begin());
    TTS_EQUAL((void*)l.ptr, (void*)arr.end());

    auto [traits1, f1, l1] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), arr.begin(), arr.begin());
    TTS_EQUAL(f1, l1);
  }

  // const pointers
  {
    auto [traits, f, l] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), arr.cbegin(), arr.cend());
    TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<decltype(traits)>() == 2);
    TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<const e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<const e_t, N>));
    TTS_EQUAL((void*)f.ptr, (void*)arr.cbegin());
    TTS_EQUAL((void*)l.ptr, (void*)arr.cend());

    auto [traits1, f1, l1] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), arr.cbegin(), arr.cbegin());
    TTS_EQUAL(f1, l1);
  }

  // aligned_pointer
  {
    auto [traits, f, l] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), eve::aligned_ptr<e_t>{arr.begin()}, arr.end());
    TTS_TYPE_IS(decltype(traits), decltype(eve::algo::traits(eve::algo::unroll<2>, eve::algo::no_aligning)));
    TTS_TYPE_IS(decltype(f), (eve::algo::aligned_ptr_iterator<e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<e_t, N>));
    TTS_EQUAL((void*)f.ptr.get(), (void*)arr.begin());
    TTS_EQUAL((void*)l.ptr, (void*)arr.end());

    auto [traits1, f1, l1] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), eve::aligned_ptr<e_t>{arr.begin()}, arr.begin());
    TTS_EQUAL(f1, l1);
  }

  // const aligned_pointer
  {
    auto [traits, f, l] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), eve::aligned_ptr<const e_t>{arr.cbegin()}, arr.cend());
    TTS_TYPE_IS(decltype(traits), decltype(eve::algo::traits(eve::algo::unroll<2>, eve::algo::no_aligning)));
    TTS_TYPE_IS(decltype(f), (eve::algo::aligned_ptr_iterator<const e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<const e_t, N>));
    TTS_EQUAL((void*)f.ptr.get(), (void*)arr.begin());
    TTS_EQUAL((void*)l.ptr, (void*)arr.end());

    auto [traits1, f1, l1] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), eve::aligned_ptr<const e_t>{arr.cbegin()}, arr.cbegin());
    TTS_EQUAL(f1, l1);
  }

  // two aligned_pointers
  {
    auto [traits, f, l] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), eve::aligned_ptr<e_t>{arr.begin()}, eve::aligned_ptr<e_t>{arr.end()});
    TTS_TYPE_IS(decltype(traits), decltype(eve::algo::traits(eve::algo::unroll<2>, eve::algo::divisible_by_cardinal, eve::algo::no_aligning)));
    TTS_TYPE_IS(decltype(f), (eve::algo::aligned_ptr_iterator<e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::aligned_ptr_iterator<e_t, N>));
    TTS_EQUAL((void*)f.ptr.get(), (void*)arr.begin());
    TTS_EQUAL((void*)l.ptr.get(), (void*)arr.end());

    auto [traits1, f1, l1] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), eve::aligned_ptr<e_t>{arr.begin()}, eve::aligned_ptr<e_t>{arr.begin()});
    TTS_EQUAL(f1, l1);
  }

  // two const aligned_pointer
  {
    auto [traits, f, l] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), eve::aligned_ptr<const e_t>{arr.cbegin()}, eve::aligned_ptr<const e_t>{arr.cend()});
    TTS_TYPE_IS(decltype(traits), decltype(eve::algo::traits(eve::algo::unroll<2>, eve::algo::divisible_by_cardinal, eve::algo::no_aligning)));
    TTS_TYPE_IS(decltype(f), (eve::algo::aligned_ptr_iterator<const e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::aligned_ptr_iterator<const e_t, N>));
    TTS_EQUAL((void*)f.ptr.get(), (void*)arr.begin());
    TTS_EQUAL((void*)l.ptr.get(), (void*)arr.end());

    auto [traits1, f1, l1] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), eve::aligned_ptr<const e_t>{arr.cbegin()}, eve::aligned_ptr<const e_t>{arr.cbegin()});
    TTS_EQUAL(f1, l1);
  }

  // vector::iterator
  {
    auto [traits, f, l] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), vec.begin(), vec.end());
    TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<decltype(traits)>() == 2);
    TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<e_t, N>));
    TTS_EQUAL((void*)f.ptr, (void*)vec.data());
    TTS_EQUAL((void*)l.ptr, (void*)(vec.data() + static_cast<std::ptrdiff_t>(vec.size())));

    auto [traits1, f1, l1] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), vec.begin(), vec.begin());
    TTS_EQUAL(f1, l1);
  }

  // vector::const_iterator
  {
    auto [traits, f, l] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), vec.cbegin(), vec.cend());
    TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<decltype(traits)>() == 2);
    TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<const e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<const e_t, N>));
    TTS_EQUAL((void*)f.ptr, (void*)vec.data());
    TTS_EQUAL((void*)l.ptr, (void*)(vec.data() + static_cast<std::ptrdiff_t>(vec.size())));

    auto [traits1, f1, l1] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), vec.cbegin(), vec.cbegin());
    TTS_EQUAL(f1, l1);
  }
};

EVE_TEST_TYPES("Check preprocess_range for eve ptr iterators", algo_test::selected_types)
<typename T>(eve::as_<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<T::size()>;

  alignas(sizeof(T)) std::array<e_t, T::size()> arr;

  auto run_one_test = [&]<typename I, typename S, typename ExpectedTraits>(I _f, S _l, ExpectedTraits)
  {
    auto [traits, f, l] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), _f, _l);
    TTS_TYPE_IS(decltype(traits), ExpectedTraits);
    TTS_TYPE_IS(decltype(f), I);
    TTS_TYPE_IS(decltype(l), S);
    TTS_EQUAL(f, _f);
    TTS_EQUAL(l, _l);

    auto [traits1, f1, l1] = eve::algo::preprocess_range(eve::algo::traits(eve::algo::unroll<2>), _f, _f);
    TTS_EQUAL(f1, l1);
  };

  auto run_test = [&] <typename U>(U* f, U* l) {
    using aligned_it = eve::algo::aligned_ptr_iterator<U, N>;
    using aligned_p = typename aligned_it::aligned_ptr_type;

    eve::algo::unaligned_ptr_iterator<U, N> u_f(f);
    eve::algo::unaligned_ptr_iterator<U, N> u_l(l);
    eve::algo::aligned_ptr_iterator<U, N>   a_f(aligned_p{f});
    eve::algo::aligned_ptr_iterator<U, N>   a_l(aligned_p{l});

    run_one_test(u_f, u_l, eve::algo::traits(eve::algo::unroll<2>));
    run_one_test(u_f, a_l, eve::algo::traits(eve::algo::unroll<2>));
    run_one_test(a_f, a_l, eve::algo::traits(eve::algo::unroll<2>, eve::algo::divisible_by_cardinal, eve::algo::no_aligning));
    run_one_test(a_f, u_l, eve::algo::traits(eve::algo::unroll<2>, eve::algo::no_aligning));
  };

  run_test(arr.begin(), arr.end());
  run_test(arr.cbegin(), arr.cend());
};

EVE_TEST_TYPES("contigious ranges", algo_test::selected_types)
<typename T>(eve::as_<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<eve::expected_cardinal_v<e_t>>;

  // empty vector
  {
    std::vector<e_t> v;
    using u_it = eve::algo::unaligned_ptr_iterator<e_t, N>;

    auto [tr, f, l] = eve::algo::preprocess_range(eve::algo::traits(), v);
    TTS_TYPE_IS(decltype(tr), decltype(eve::algo::traits()));
    TTS_TYPE_IS(decltype(f), u_it);
    TTS_TYPE_IS(decltype(l), u_it);
    TTS_EQUAL(f, l);
  }

  auto non_empty_range_test = [](auto&& rng) {
    auto [tr, f, l] = eve::algo::preprocess_range(eve::algo::traits(), rng);

    using u_it = eve::algo::unaligned_ptr_iterator<
      std::remove_reference_t<decltype(*std::begin(rng))>, N>;

    TTS_TYPE_IS(decltype(tr), decltype(eve::algo::traits()));
    TTS_TYPE_IS(decltype(f), u_it);
    TTS_TYPE_IS(decltype(l), u_it);

    auto* f_ = &*std::begin(rng);
    auto* l_ = f_ + (std::end(rng) - std::begin(rng));

    TTS_EQUAL((l - f), (l_ - f_));
    TTS_EQUAL(f.ptr, f_);
    TTS_EQUAL(l.ptr, l_);
  };

  {
    std::vector<e_t> v(10, 1);
    non_empty_range_test(v);
  }

  {
    const std::vector<e_t> v(10, 1);
    non_empty_range_test(v);
  }

  {
    e_t v[10] = {};
    non_empty_range_test(v);
  }

  {
    e_t const v[10] = {};
    non_empty_range_test(v);
  }

  {
    std::array<e_t, 10> v = {};
    non_empty_range_test(v);
  }

  {
    const std::array<e_t, 10> v = {};
    non_empty_range_test(v);
  }
};
