//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/one_range_algorithm_adapter.hpp>

#include <utility>

namespace
{

template <typename Traits, typename Impl>
struct fake_algorithm :
  eve::algo::one_range_algorithm_adapter<fake_algorithm<Traits, Impl>>
{
  Traits traits_;
  Impl   impl_;

  fake_algorithm(Traits traits, Impl impl) :
    traits_(traits), impl_(impl) {}

  Traits default_traits() const
  {
    return traits_;
  }

  template <typename ...Args>
  auto impl(auto processed, Args&&... args) const
  {
    return impl_(processed.traits(), processed.begin(), processed.end(), std::forward<Args>(args)...);
  }
};

}

EVE_TEST_TYPES("Vector/const vector", algo_test::selected_types)
<typename T>(eve::as_<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<eve::expected_cardinal_v<e_t>>;

  std::vector<e_t> v(3, 0);

  auto const non_const_aglorithm =
      fake_algorithm(eve::algo::traits(eve::algo::unroll<4>), [&](auto traits, auto f, auto l) {
        TTS_CONSTEXPR_EQUAL(eve::algo::get_unrolling<decltype(traits)>(), 4);
        TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<e_t, N>));
        TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<e_t, N>));
        TTS_EQUAL(f.ptr, v.data());
        TTS_EQUAL(l.ptr, v.data() + v.size());
      });

  non_const_aglorithm(v);
  non_const_aglorithm(v.begin(), v.end());
  non_const_aglorithm(v.data(), v.data() + v.size());

  auto const const_algorithm =
      fake_algorithm(eve::algo::traits(eve::algo::unroll<4>), [&](auto traits, auto f, auto l) {
        TTS_CONSTEXPR_EQUAL(eve::algo::get_unrolling<decltype(traits)>(), 2);
        TTS_TYPE_IS(decltype(f), (eve::algo::unaligned_ptr_iterator<e_t const, N>));
        TTS_TYPE_IS(decltype(l), (eve::algo::unaligned_ptr_iterator<e_t const, N>));
        TTS_EQUAL(f.ptr, v.data());
        TTS_EQUAL(l.ptr, v.data() + v.size());
      });

  const_algorithm(eve::algo::traits(eve::algo::unroll<2>), std::as_const(v));
  const_algorithm(eve::algo::traits(eve::algo::unroll<2>), v.cbegin(), v.cend());

  e_t const* const_data = v.data();
  const_algorithm(eve::algo::traits(eve::algo::unroll<2>), const_data, const_data + v.size());
};

EVE_TEST_TYPES("aligned_ptr, empty range", algo_test::selected_types)
<typename T>(eve::as_<T>)
{
  using e_t = eve::element_type_t<T>;
  using N = eve::fixed<eve::expected_cardinal_v<e_t>>;

  fake_algorithm(eve::algo::traits(), [](auto traits, auto f, auto l) {
    auto expected_traits = eve::algo::traits(eve::algo::divisible_by_cardinal, eve::algo::no_aligning);
    TTS_TYPE_IS(decltype(traits),decltype(expected_traits));
    TTS_TYPE_IS(decltype(f), (eve::algo::aligned_ptr_iterator<e_t, N>));
    TTS_TYPE_IS(decltype(l), (eve::algo::aligned_ptr_iterator<e_t, N>));
    TTS_EQUAL(f, l);
  })(eve::aligned_ptr<e_t>(), eve::aligned_ptr<e_t>());
};
