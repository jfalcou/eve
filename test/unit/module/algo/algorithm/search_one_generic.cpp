//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "find_generic_test.hpp"
#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

template<typename TraitsSupport> struct find_if_with_search_ : TraitsSupport
{
  template<typename Rng, typename P> EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
  {
    std::array<std::int8_t, 1> fake;
    return eve::algo::search[TraitsSupport::get_traits()](
        std::forward<Rng>(rng), fake, [p](auto x, auto) { return p(x); });
  }
};

inline constexpr auto find_if_with_search =
    eve::algo::function_with_traits<find_if_with_search_>[eve::algo::search.get_traits()];

TTS_CASE_TPL("eve.algo.find_if_with_search generic", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::find_generic_test(eve::as<T> {},
                               find_if_with_search,
                               [](auto f, auto l, auto expected, auto actual)
                               {
                                 TTS_EQUAL(actual, expected, REQUIRED)
                                     << "l - f: " << (l - f) << " expected: " << (expected - f);
                               });
};
