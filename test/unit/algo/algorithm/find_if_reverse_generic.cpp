//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "find_last_generic_test.hpp"
#include "unit/algo/algo_test.hpp"

#include <eve/algo/find.hpp>
#include <eve/views/reverse.hpp>

#include <algorithm>

template<typename TraitsSupport> struct find_reverse_ : TraitsSupport
{
  template<typename Rng, typename P> EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
  {
    return eve::algo::find_if(eve::views::reverse(rng), p).base - 1;
  }
};

inline constexpr auto find_reverse =
    eve::algo::function_with_traits<find_reverse_>[eve::algo::find_if.get_traits()];

TTS_CASE_TPL("Check find_if(reverse)", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::find_generic_backward_test(eve::as<T> {},
                                        find_reverse,
                                        [](auto f, auto, auto expected, auto actual)
                                        {
                                          TTS_EQUAL(actual - f, expected - f);
                                          if( actual != expected ) { std::terminate(); }
                                        });
};
