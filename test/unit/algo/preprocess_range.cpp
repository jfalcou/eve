#include "algo_test.hpp"

#include <eve/algo/preprocess_range.hpp>

#include <eve/algo/ptr_iterator.hpp>

#include "iterator_conept_test.hpp"

#include <array>
#include <vector>

namespace
{
  struct no_traits {};
}

EVE_TEST_TYPES("Check preprocess_range for contiguous iterators", algo_test::selected_types)
<typename T>(eve::as_<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<eve::expected_cardinal_v<e_t>>;

  alignas(sizeof(T)) std::array<e_t, T::static_size> arr;

  std::vector<e_t> vec(100u, 0);

  // pointers
  {
    auto [traits, f, l] = eve::algo::preprocess_range(no_traits{}, arr.begin(), arr.end());
    TTS_TYPE_IS(decltype(traits), no_traits);
    TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<e_t, N>));
    TTS_EQUAL(f.ptr, arr.begin());
    TTS_EQUAL(l.ptr, arr.end());
  }

  // const pointers
  {
    auto [traits, f, l] = eve::algo::preprocess_range(no_traits{}, arr.cbegin(), arr.cend());
    TTS_TYPE_IS(decltype(traits), no_traits);
    TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<const e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<const e_t, N>));
    TTS_EQUAL(f.ptr, arr.cbegin());
    TTS_EQUAL(l.ptr, arr.cend());
  }

  // vector::iterator
  {
    auto [traits, f, l] = eve::algo::preprocess_range(no_traits{}, vec.begin(), vec.end());
    TTS_TYPE_IS(decltype(traits), no_traits);
    TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<e_t, N>));
    TTS_EQUAL(f.ptr, vec.data());
    TTS_EQUAL(l.ptr, vec.data() + static_cast<std::ptrdiff_t>(vec.size()));
  }

  // vector::const_iterator
  {
    auto [traits, f, l] = eve::algo::preprocess_range(no_traits{}, vec.cbegin(), vec.cend());
    TTS_TYPE_IS(decltype(traits), no_traits);
    TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<const e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<const e_t, N>));
    TTS_EQUAL(f.ptr, vec.data());
    TTS_EQUAL(l.ptr, vec.data() + static_cast<std::ptrdiff_t>(vec.size()));
  }
};

EVE_TEST_TYPES("Check preprocess_range for eve ptr iterators", algo_test::selected_types)
<typename T>(eve::as_<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<T::static_size>;

  alignas(sizeof(T)) std::array<e_t, T::static_size> arr;

  auto run_one_test = [&]<typename I, typename S>(I _f, S _l)
  {
    auto [traits, f, l] = eve::algo::preprocess_range(no_traits{}, _f, _l);
    TTS_TYPE_IS(decltype(traits), no_traits);
    TTS_TYPE_IS(decltype(f), I);
    TTS_TYPE_IS(decltype(l), S);
    TTS_EQUAL(f, _f);
    TTS_EQUAL(l, _l);
  };

  auto run_test = [&] <typename U>(U* f, U* l) {
    using aligned_it = eve::algo::aligned_ptr_iterator<U, N>;
    using aligned_p = typename aligned_it::aligned_ptr_type;

    eve::algo::unaligned_ptr_iterator<U, N> u_f(f);
    eve::algo::unaligned_ptr_iterator<U, N> u_l(l);
    eve::algo::aligned_ptr_iterator<U, N>   a_f(aligned_p{f});
    eve::algo::aligned_ptr_iterator<U, N>   a_l(aligned_p{l});

    run_one_test(u_f, u_l);
    run_one_test(u_f, a_l);
    run_one_test(a_f, a_l);
    run_one_test(a_f, u_l);
  };

  run_test(arr.begin(), arr.end());
  run_test(arr.cbegin(), arr.cend());
};
