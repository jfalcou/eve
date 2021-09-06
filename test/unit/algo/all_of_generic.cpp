//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/all_of.hpp>

#include "find_generic_test.hpp"

template <typename TraitsSupport>
struct any_with_all_ : TraitsSupport
{
  template <typename Rng, typename P>
  EVE_FORCEINLINE bool operator()(Rng&& rng, P p) const
  {
    return !eve::algo::all_of[TraitsSupport::get_traits()](std::forward<Rng>(rng),
      [p](auto x) { return !p(x); });
  }
};

inline constexpr auto any_with_all = eve::algo::function_with_traits<any_with_all_>;

EVE_TEST_TYPES("eve.algo.all_of generic", algo_test::selected_types)
<typename T>(eve::as<T> as_t)
{
  algo_test::find_generic_test(as_t, any_with_all,
  [](auto, auto l, auto expected, bool actual) {
    TTS_EQUAL(actual, (expected != l));
  });
};
