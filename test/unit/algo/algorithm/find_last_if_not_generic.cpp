//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "find_last_generic_test.hpp"

#include <eve/algo.hpp>

#include <algorithm>

template<typename TraitsSupport> struct not_not_find_if_backward_ : TraitsSupport
{
  template<typename Rng, typename P> EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
  {
    return eve::algo::find_last_if_not[TraitsSupport::get_traits()](
        std::forward<Rng>(rng), [p](auto x) { return !p(x); });
  }
};

inline constexpr auto not_not_find_if_backward =
    eve::algo::function_with_traits<not_not_find_if_backward_>[eve::algo::find_if_not.get_traits()];

TTS_CASE_TPL("Check find_if_backward", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::find_generic_backward_test(eve::as<T> {},
                                        not_not_find_if_backward,
                                        [](auto f, auto l, auto expected, auto actual)
                                        {
                                          TTS_EQUAL(actual - f, expected - f);
                                          if( actual != expected )
                                          {
                                            std::cout << tts::as_string(std::vector(f, l))
                                                      << std::endl;
                                            std::terminate();
                                          }
                                        });
};
