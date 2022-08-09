//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/all_of.hpp>

#include "find_generic_test.hpp"

template <typename TraitsSupport>
struct any_with_all_ : TraitsSupport
{
  template <typename Rng, typename P>
  EVE_FORCEINLINE bool operator()(Rng&& rng, P p) const
  {
    return !eve::algo::all_of[TraitsSupport::get_traits()](EVE_FWD(rng),
      [p](auto x) { return !p(x); });
  }
};

inline constexpr auto any_with_all = eve::algo::function_with_traits<any_with_all_>[eve::algo::all_of.get_traits()];

TTS_CASE_TPL("eve.algo.all_of generic", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::find_generic_test(eve::as<T>{}, any_with_all,
  [](auto, auto l, auto expected, bool actual) {
    TTS_EQUAL(actual, (expected != l));
  });
};
