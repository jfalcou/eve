//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include "find_generic_test.hpp"

template <typename TraitsSupport>
struct find_if_with_find_if_not_ : TraitsSupport
{
  template <typename Rng, typename P>
  EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
  {
    return eve::algo::find_if_not[TraitsSupport::get_traits()](std::forward<Rng>(rng),
      [p](auto x) { return !p(x); });
  }
};

inline constexpr auto find_if_with_find_if_not =
  eve::algo::function_with_traits<find_if_with_find_if_not_>[eve::algo::find_if_not.get_traits()];

TTS_CASE_TPL("eve.algo.find_if generic", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::find_generic_test(eve::as<T>{}, find_if_with_find_if_not,
  [](auto, auto, auto expected, auto actual) {
    TTS_EQUAL(actual, expected);
  });
};
